`timescale  1ns/10ps

module TB();


	reg 						clk;			
	reg 						rst_n;			
	
	reg							rd_n;
	reg							wr_n;
	
	reg		[17:0]				addr;
	wire	[15:0]				data;
	reg		[15:0]				data_in;
	reg		[15:0]				data_old;
	reg		[15:0]				data_get;
	
	
	wire						dac_re_wr;
	wire						dac_cs_n;
	wire	[4:0]				dac_add	;
	wire	[15:0]				dac_data;
						
	
	
	initial 
		begin
			clk = 1'b0;
			rst_n = 1'b0;
			#25;
			rst_n = 1'b1;
		end

	always   #50 clk = ~clk;
	
	initial 
		begin
			wr_n = 1'b1;
			rd_n = 1'b1;	
			addr = 18'b000;
			data_old = 16'h000;
			data_in = 16'hzzzz;
			data_get = 16'hzzzz;
		end
	
	always #2100
		begin
			wr_n = 1'b1;		// 空闲时间
			rd_n = 1'b1;
			addr = 18'hffff;
			data_in = 16'hzzzz;
			data_old = data_old + 16'h10;
			data_get = 16'hzzzz;
			#40;
			
			wr_n = 1'b1;		// 写数据建立时间
			rd_n = 1'b1;
			addr = 18'h0000;
			data_in = 16'hzzzz;
			data_get = 16'hzzzz;
			#40;
			
			wr_n = 1'b0;		// 写数据保持时间
			rd_n = 1'b1;
			addr = 18'h0000;
			data_in = data_old;
			data_get = 16'hzzzz;
			#160;
			
			wr_n = 1'b1;		// 写数据跟踪时间
			rd_n = 1'b1;
			addr = 18'h0000;
			data_in = 16'hzzzz;
			data_get = 16'hzzzz;
			#80;
			
			
			wr_n = 1'b1;		// 空闲时间
			rd_n = 1'b1;
			addr = 18'hffff;
			data_in = 16'hzzzz;
			data_get = 16'hzzzz;
			#1;   			 
			
			
			
			wr_n = 1'b1;		// 读数据建立
			rd_n = 1'b1;
			addr = 18'h0100;
			data_get = 16'hzzzz;
			#40;
			
			wr_n = 1'b1;		// 读数据1的保持时间
			rd_n = 1'b0;
			addr = 18'h0100;
			data_get = 16'hzzzz;
			#160;
			
			data_get = data;
			#40;
			
			wr_n = 1'b1;		// 读数据1的跟踪时间
			rd_n = 1'b1;
			addr = 18'h0100;
			data_get = 16'hzzzz;
			#80;
			
			
			wr_n = 1'b1;		// 空闲时间
			rd_n = 1'b1;
			addr = 18'hffff;
			data_get = 16'hzzzz;
			#6;   			 
			
			
			
			wr_n = 1'b1;		// 读数2据建立
			rd_n = 1'b1;
			addr = 18'h0200;
			data_get = 16'hzzzz;
			#40;
			
			wr_n = 1'b1;		// 读数据2的保持时间
			rd_n = 1'b0;
			addr = 18'h0200;
			data_get = 16'hzzzz;
			#160;
			
			data_get = data;
			#40;
			
			wr_n = 1'b1;		// 读数据2的跟踪时间
			rd_n = 1'b1;
			addr = 18'h0200;
			data_get = 16'hzzzz;
			#80;
			
			
			wr_n = 1'b1;		// 空闲时间
			rd_n = 1'b1;
			addr = 18'hffff;
			#3;   		 
			
			
			
			wr_n = 1'b1;		// 读数据3建立
			rd_n = 1'b1;
			addr = 18'h0300;
			data_get = 16'hzzzz;
			#40;
			
			wr_n = 1'b1;		// 读数据3的保持时间
			rd_n = 1'b0;
			addr = 18'h0300;
			data_get = 16'hzzzz;
			#160;
			
			data_get = data;
			#40;
			
			wr_n = 1'b1;		// 读数据3的跟踪时间
			rd_n = 1'b1;
			addr = 18'h0300;
			data_get = 16'hzzzz;
			#80;
			
		end
	 
	assign data = data_in;
		
		
 Communication  Communication_inst
(
	.clk					( clk		),
	.rst_n					( rst_n		),
	
	
	//DSP input signal
	.rd_n					( rd_n		),
	.wr_n					( wr_n		),
	
	.addr					( addr		),
	.data					( data		),
	
	// DAC signal
	.dac_re_wr				( dac_re_wr	),
	.dac_cs_n				( dac_cs_n	),
	.dac_add				( dac_add	),
	.dac_data				( dac_data	) 
);

endmodule