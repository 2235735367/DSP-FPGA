module   Encoder  #
(
	parameter	signed ENCO_NUM = 32'd4000	//编码器4倍频			
)
(	
	input	wire				clk		,//时钟信号		
	input	wire				rst_n	,//复位信号
    
	input	wire				Enco_A	,//编码器A信号
	input	wire				Enco_B	,//编码器B信号	
	input	wire				Enco_Z	,//编码器Z信号
    
	output	reg		[1:0]		motor_dir,//电机转向  
	output	reg	signed 	[15:0]	motor_cnt,//电机计数
	output	reg	signed	[15:0]	motor_cir //电机圈数		
);

/*定义两个寄存器，将编码器信号延后1拍、2拍.对信号的上升沿、下降沿进行判断*/
	wire				Enco_A_r ;
	reg					Enco_A_r1;
	reg					Enco_A_r2;
	reg					Enco_A_r3;
		
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			Enco_A_r1 <= 1'b0;
			Enco_A_r2 <= 1'b0;
			Enco_A_r3 <= 1'b0;
		end
		else begin
			Enco_A_r1 <= Enco_A;
			Enco_A_r2 <= Enco_A_r1;
			Enco_A_r3 <= Enco_A_r2;
		end
	end
	
	assign  Enco_A_r = Enco_A_r3;
    
    reg					Enco_A_pos;//位置
	reg					Enco_A_neg;//角度
	reg					Enco_A_temp;
	
	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			Enco_A_temp <= 1'b0;
		end
		else begin
			Enco_A_temp <= Enco_A_r;
		end
	end
	
	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			Enco_A_pos <= 1'b0;
		end
		else begin
		if((Enco_A_temp == 1'b0)&&(Enco_A_r == 1'b1))begin//下降沿?为什么还要加上A_temp延后三拍,此处应该是上升沿？
				Enco_A_pos <= 1'b1;
			end
			else begin
				Enco_A_pos <= 1'b0;
			end
		end
	end
	
	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			Enco_A_neg <= 1'b0;
		end
		else begin
		if((Enco_A_temp == 1'b1)&&(Enco_A_r == 1'b0))begin//上升沿
				Enco_A_neg <= 1'b1;
			end
			else begin
				Enco_A_neg <= 1'b0;
			end
		end
	end
	
	
	wire				Enco_B_r ;
	reg					Enco_B_r1;
	reg					Enco_B_r2;
	reg					Enco_B_r3;	

	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			Enco_B_r1 <= 1'b0;
			Enco_B_r2 <= 1'b0;
			Enco_B_r3 <= 1'b0;
		end
		else begin
			Enco_B_r1 <= Enco_B;
			Enco_B_r2 <= Enco_B_r1;
			Enco_B_r3 <= Enco_B_r2;
		end
	end
	
	assign  Enco_B_r = Enco_B_r3;

	
	wire				Enco_Z_r ;
	reg					Enco_Z_r1;
	reg					Enco_Z_r2;
	reg					Enco_Z_r3;
	
	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			Enco_Z_r1 <= 1'b0;
			Enco_Z_r2 <= 1'b0;
			Enco_Z_r3 <= 1'b0;
		end
		else begin
			Enco_Z_r1 <= Enco_Z;
			Enco_Z_r2 <= Enco_Z_r1;
			Enco_Z_r3 <= Enco_Z_r2;
		end
	end
	
	assign  Enco_Z_r = Enco_Z_r3;


	
	reg					Enco_B_pos;
	reg					Enco_B_neg;
	reg					Enco_B_temp;
	
	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			Enco_B_temp <= 1'b0;
		end
		else begin
			Enco_B_temp <= Enco_B_r;
		end
	end

	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			Enco_B_pos <= 1'b0;
		end
		else begin
			if((Enco_B_temp == 1'b0)&&(Enco_B_r == 1'b1))begin
				Enco_B_pos <= 1'b1;
			end
			else begin
				Enco_B_pos <= 1'b0;
			end
		end
	end

	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			Enco_B_neg <= 1'b0;
		end
		else begin
			if((Enco_B_temp == 1'b1)&&(Enco_B_r == 1'b0))begin
				Enco_B_neg <= 1'b1;
			end
			else begin
				Enco_B_neg <= 1'b0;
			end
		end
	end

	
	reg					Enco_Z_pos;
	reg					Enco_Z_temp;
	

	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			Enco_Z_temp <= 1'b0;
		end
		else begin
			Enco_Z_temp <= Enco_Z_r;
		end
	end

	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			Enco_Z_pos <= 1'b0;
		end
		else begin
			if((Enco_Z_temp == 1'b0)&&(Enco_Z_r == 1'b1))begin
				Enco_Z_pos <= 1'b1;
			end
			else begin
				Enco_Z_pos <= 1'b0;
			end
		end
	end

	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
		motor_dir <= 2'b00;
		end
		else begin
			if((Enco_A_r == 1'b1)&&(Enco_B_r == 1'b0)&&(Enco_A_pos == 1'b1))begin
				motor_dir <= 2'b01;				//direction positive
			end
			else if((Enco_A_r == 1'b1)&&(Enco_B_r == 1'b1)&&(Enco_A_pos == 1'b1)) begin
				motor_dir <= 2'b10;				// direction negative
			end
			else begin
				motor_dir <= motor_dir;	
			end
		end
	end

	

	reg				Enco_flag;
	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			Enco_flag <= 1'b0;
		end
		else begin
			if(Enco_A_pos == 1'b1)begin
				Enco_flag <= 1'b1;
			end
			else if(Enco_B_pos == 1'b1) begin
				Enco_flag <= 1'b1;
			end
			else if(Enco_A_neg == 1'b1) begin
				Enco_flag <= 1'b1;
			end
			else if(Enco_B_neg == 1'b1) begin
				Enco_flag <= 1'b1;
			end
			else begin
				Enco_flag <= 1'b0;
			end
		end
	end
	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			motor_cnt <= 16'd0;
		end
		else begin
			if(Enco_flag == 1'b1) begin
				if( motor_cnt <= -(ENCO_NUM-1) | motor_cnt >= (ENCO_NUM-1)) begin
					motor_cnt <= 16'd0;
				end
				else if(motor_dir==2'b01)begin
					motor_cnt <= motor_cnt - 1'd1;
				end
				else if(motor_dir==2'b10)begin
					motor_cnt <= motor_cnt +1'd1;
				end
			end
			else begin
				motor_cnt <= motor_cnt;
			end
		end
	end

	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			motor_cir <= 1'd0;
		end
		else  begin
		if(Enco_flag == 1'b1) begin
			if((motor_dir == 2'b01)&&(motor_cnt <= -(ENCO_NUM-1)))begin
				motor_cir <= motor_cir - 1'd1;
			end
			else if((motor_dir == 2'b10)&&(motor_cnt >= (ENCO_NUM-1))) begin
				motor_cir <= motor_cir + 1'd1;
			end
		end
		else begin
			motor_cir <= motor_cir;
		end
		end
	end



endmodule


















