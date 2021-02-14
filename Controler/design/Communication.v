module  Communication
(
	input		wire				clk,
	input		wire				rst_n,
	
	input		wire				Enco_A	,//编码器A线	
	input		wire				Enco_B	,//编码器B线
	input		wire				Enco_Z	,//编码器Z线	
	
	input		wire				rd_n,
	input		wire				wr_n,
	
	input		wire	[17:0]		addr,//xintf的外部地址
	inout		wire signed	[15:0]	data,//xintf数据总线
	
	output		wire				dac_re_wr	,//dac的写使能信号	
	output		wire				dac_cs_n	,//dac读使能信号
	output		wire	[4:0]		dac_add		,//dac的地址	
	output		wire  [15:0]		dac_data	,//给DAC的数据

    output      wire                led1         //led输出

);
 
	reg						rd_n_r;
	reg						rd_n_r1;
	
	reg						wr_n_r;
	reg						wr_n_r1;
	
	reg		[17:0]			addr_r;
	reg		[17:0]			addr_r1;

	reg	signed	[15:0]			data_r;
	reg	signed	[15:0]			data_r1;
	
	reg		[10:0]			current_state;
	reg		[10:0]			next_state;
	
	localparam			IDLE = 11'b00_000_000_001;//状态空间
	localparam			S1   = 11'b00_000_000_010;
	localparam			S2   = 11'b00_000_000_100;
	localparam			S3   = 11'b00_000_001_000;
	localparam			S4   = 11'b00_000_010_000;
	localparam			S5   = 11'b00_000_100_000;
	localparam			S6   = 11'b00_001_000_000;
	localparam			S7   = 11'b00_010_000_000;
	
	localparam			DAC1_ADDR  = 18'h010;
	localparam			E1_CN_ADD  = 18'h100;
	localparam			E1_DI_ADD  = 18'h200;
	localparam			E1_RO_ADD  = 18'h300;
	
	localparam			RDACTIVE  = 5'd6;
	localparam			RDTRAIL   = 5'd4;
	
	localparam			WRACTIVE  = 5'd6;
	localparam			WRTRAIL   = 5'd4;	

	
	reg		[31:0]			cnt_keep;
	reg		[31:0]			cnt_trail;
	
	reg						    flag;
	reg	signed	[15:0]			data_reg;
	
	reg	signed 	[15:0]			encoder_1_cnt;
	reg		[15:0]			    encoder_1_dir;
	reg	signed	[15:0]			encoder_1_cir;
	
	wire	[1:0]			        motor_dir;
	wire	signed [15:0]			motor_cnt;                       
	wire	signed [15:0]			motor_cir;                       
		
	reg	signed	[15:0]			    dac_1_data;
	
	wire 					clk_150;
	wire 					clk_50;
	wire					locked_pll;
	
	reg		[4:0]			add_in_dac;	
	reg	signed	[15:0]		data_in_dac; 	
	wire					done_dac;	

	always @ (posedge clk_150 or negedge locked_pll) begin//
		if(!locked_pll) begin
			add_in_dac <= 5'b00111;
			data_in_dac <= 16'h7fff;
		end
		else begin
			if(done_dac) begin
				add_in_dac <= 4'b01000;//给DAC地址信号
				data_in_dac <= dac_1_data;//向DAC更新数据
			end
			else begin
				add_in_dac <= add_in_dac;
				data_in_dac <= data_in_dac;
			end
		end
	end
	
	

	always @ (posedge clk_150 or negedge locked_pll) begin
		if(!locked_pll) begin
			encoder_1_cnt <= 16'h0;
			encoder_1_dir <= 16'h0;
			encoder_1_cir <= 16'h0;
		end
		else begin
			encoder_1_cnt <= motor_cnt;//电机脉冲数
			encoder_1_dir <= {14'b00,motor_dir};//方向
			encoder_1_cir <= motor_cir;//圈数，将电机驱动信息保存到寄存器中，由编码器得到
		end
	end

	
	always @ (posedge clk_150 or negedge locked_pll) begin//保存读信号
		if(!locked_pll) begin
		    rd_n_r1 <= 1'b1;
			rd_n_r  <= 1'b1;
		end
		else begin 
			rd_n_r1 <= rd_n;//xintf读信号，低电平有效，当前信号
			rd_n_r  <= rd_n_r1;//上一次信号，为什么要用上一次的信号？？？延时一个周期，防止异步通信出现亚稳态！
		end
	end
	
	always @ (posedge clk_150 or negedge locked_pll) begin//写信号
		if(!locked_pll) begin
			wr_n_r1 <= 1'b1;
			wr_n_r  <= 1'b1;
		end
		else begin 
			wr_n_r1 <= wr_n;//xintf写信号，当前信号
			wr_n_r  <= wr_n_r1;//上一次写信号状态，异步信号同步化处理，防止信号出现亚稳态
		end
	end
	
	always @ (posedge clk_150 or negedge locked_pll) begin//地址信号
		if(!locked_pll) begin
			addr_r1 <= 18'h0000;
			addr_r  <= 18'h0000;
		end
		else begin 
			addr_r1 <= addr;//当前地址
			addr_r  <= addr_r1;//上一次地址
		end
	end
	
	always @ (posedge clk_150 or negedge locked_pll) begin//数据信号
		if(!locked_pll) begin
			data_r <= 16'h0000;
			data_r1  <= 16'h0000;
		end
		else begin 
			data_r1 <= data;//当前数据
			data_r  <= data_r1;//上一次数据
		end
	end
	
	always @ (posedge clk_150 or negedge locked_pll) begin//状态机，与DSP数据交换
		if(!locked_pll) begin
			current_state <= IDLE;
		end
		else begin
			current_state <= next_state;
		end
	end 
	
	always @ (*) begin
		if(!locked_pll) begin
			next_state <= IDLE;
		end
		else begin
			case (current_state)
				IDLE : begin
					if(!wr_n_r)begin
						next_state = S1;//判断是写信号，进入S1，写信号低电平
					end
					else if(!rd_n_r)begin
						next_state = S2;
					end
					else begin
						next_state = IDLE;
					end
				end
				
				S1   : begin
					if(cnt_keep >= (WRACTIVE - 1'b1))begin//写数据
						next_state = S6;
					end
					else begin
						next_state = S1;
					end
				end
				
				S2   : begin	
					if(addr_r == E1_CN_ADD)begin//脉冲地址
						next_state = S3;
					end
					else if(addr_r == E1_DI_ADD)begin//方向地址
						next_state = S4;
					end
					else if(addr_r == E1_RO_ADD)begin//圈数地址
						next_state = S5;
					end
					else begin
						next_state = IDLE;
					end
				end
				
				S3   : begin
				if(cnt_keep >= (RDACTIVE - 1'b1))begin//不同地址的保持时间
						next_state = S7;
					end
					else begin
						next_state = S3;
					end
				end
				
				S4   : begin
					if(cnt_keep >= (RDACTIVE - 1'b1))begin
						next_state = S7;
					end
					else begin
						next_state = S4;
					end
				end
				
				S5   : begin
					if(cnt_keep >= (RDACTIVE - 1'b1))begin
						next_state = S7;
					end
					else begin
						next_state = S5;
					end
				end
				
				S6   : begin
					if(cnt_trail >= (WRTRAIL - 1'b1))begin
						next_state = IDLE;
					end
					else begin
						next_state = S6;
					end
				end
				
				S7   : begin
					if(cnt_trail >= (RDTRAIL - 1'b1))begin//跟踪时间
						next_state = IDLE;
					end
					else begin
						next_state = S7;//阻塞型赋值
					end
				end
				
				default: begin
					next_state = IDLE;
				end
			endcase
		end
	end
	
	always @ (posedge clk_150 or negedge locked_pll) begin
		if(!locked_pll) begin
			flag <= 1'b0;
		end
		else begin
			case (current_state) 
				IDLE : begin
					flag <= 1'b0;
				end
				
				S1   : begin
					flag <= 1'b0;
				end
				
				S2   : begin
					flag <= 1'b0;
				end
				
				S3   : begin
					flag <= 1'b1;
				end
				
				S4   : begin
					flag <= 1'b1;
				end
				
				S5   : begin
					flag <= 1'b1;
				end
				
				S6   : begin
					flag <= 1'b0;
				end
				
				S7   : begin
					flag <= 1'b0;
				end
			
				default : begin
					flag <= 1'b0;
				end
			endcase
		end
	end
	
		assign  data = (flag)?data_reg:16'hzzzz;//flag数据总线写使能标志
	
	always @ (posedge clk_150 or negedge locked_pll) begin//数据更新
		if(!locked_pll) begin
			data_reg <= 16'h0000;
		end
		else begin
			case (current_state) 
				IDLE : begin
					data_reg <= data_reg;
				end
				
				S1   : begin
					data_reg <= data_reg;
				end
				
				S2   : begin
					data_reg <= data_reg;
				end
				
				S3   : begin
					data_reg <= encoder_1_cnt;
				end
				
				S4   : begin
					data_reg <= encoder_1_dir;
				end
				
				S5   : begin
					data_reg <= encoder_1_cir;//圈数信息
				end
				
				S6   : begin
					data_reg <= data_reg;
				end
				
				S7   : begin
					data_reg <= data_reg;
				end
			
				default : begin
					data_reg <= 16'h0000;
				end
			endcase
		end
	end

	always @ (posedge clk_150 or negedge locked_pll) begin//DAC数据读取
		if(!locked_pll) begin
			dac_1_data <= 16'h7fff;
		end
		else begin
			case (current_state) 
				IDLE : begin
					dac_1_data <= dac_1_data;
				end
				
				S1   : begin
				dac_1_data <= data_r;//从xintf读取数据，此时DSP往数据线上写数据，为什么是上一次的数据？
				end
				
				S2   : begin
					dac_1_data <= dac_1_data;
				end
				
				S3   : begin
					dac_1_data <= dac_1_data;
				end
				
				S4   : begin
					dac_1_data <= dac_1_data;
				end
				
				S5   : begin
					dac_1_data <= dac_1_data;
				end
				
				S6   : begin
					dac_1_data <= dac_1_data;
				end
				
				S7   : begin
					dac_1_data <= dac_1_data;
				end
			
				default : begin
					dac_1_data <= 16'h7fff;
				end
			endcase
		end
	end
	
	always @ (posedge clk_150 or negedge locked_pll) begin//延时计数器，每个状态保持一定的时间
		if(!locked_pll) begin
			cnt_keep <= 32'd0;
		end
		else begin
			case (next_state) 
				IDLE : begin
					cnt_keep <= 32'd0;
				end
				
				S1   : begin
					cnt_keep <= cnt_keep + 1'd1;
				end
				
				S2   : begin
					cnt_keep <= 32'd0;
				end
				
				S3   : begin
					cnt_keep <= cnt_keep + 1'd1;
				end
				
				S4   : begin
					cnt_keep <= cnt_keep + 1'd1;
				end
				
				S5   : begin
					cnt_keep <= cnt_keep + 1'd1;
				end
				
				S6   : begin
					cnt_keep <= 32'd0;
				end
				
				S7   : begin
					cnt_keep <= 32'd0;
				end
			
				default : begin
					cnt_keep <= 32'd0;
				end
			endcase
		end
	end	
	
	always @ (posedge clk_150 or negedge locked_pll) begin//跟踪时间计数器
		if(!locked_pll) begin
			cnt_trail <= 32'd0;
		end
		else begin
			case (next_state) 
				IDLE : begin
					cnt_trail <= 32'd0;
				end
				
				S1   : begin
					cnt_trail <= 32'd0;
				end
				
				S2   : begin
					cnt_trail <= 32'd0;
				end
				
				S3   : begin
					cnt_trail <= 32'd0;
				end
				
				S4   : begin
					cnt_trail <= 32'd0;
				end
				
				S5   : begin
					cnt_trail <= 32'd0;
				end
				
				S6   : begin
					cnt_trail <= cnt_trail + 1'd1;
				end
				
				S7   : begin
					cnt_trail <= cnt_trail + 1'd1;
				end
			
				default : begin
					cnt_trail <= 32'd0;
				end
			endcase
		end
	end//还有一个建立时间呢？
	
PLL	PLL_inst 
	(
		.areset 				( !rst_n	 ),
		.inclk0 				( clk		 ),
		.c0 					( clk_150	 ),
		.c1 					( clk_50	 ),
		.locked 				( locked_pll )
	);
	
DAC8728 #
	(
		.DELAY 					( 32'd100 	 )
	)
	DAC8728_inst
	(
		.clk					( clk_50	 ),	
		.rst_n					( locked_pll ),	
		.add_in					( add_in_dac ),	
		.data_in				( data_in_dac), 
		.done_dac				( done_dac   ),	
		.dac_re_wr				( dac_re_wr	 ),	
		.dac_cs_n				( dac_cs_n   ),	
		.dac_add				( dac_add	 ),	
		.dac_data				( dac_data	 ) 	
	);

	//assign	dac_data=0;
    
/*编码器模块*/
Encoder  #
	(
		. ENCO_NUM 				(32'd4000	)	
	)
	Encoder_inst
	(	
		.clk					( clk_50	 ),	//编码器时钟	
		.rst_n					( locked_pll ),		
		.Enco_A					( Enco_A	 ),		
		.Enco_B					( Enco_B	 ),		
		.Enco_Z					( Enco_Z	 ),		
		.motor_dir				( motor_dir	 ),		
		.motor_cnt				( motor_cnt	 ),		
		.motor_cir				( motor_cir	 )		
	);
    
/*led闪烁模块*/    
led_twink   u_led_twink(
    .sys_clk    (clk),
    .rst_n      (rst_n),
    
    .led        (led1)
);
	
endmodule

