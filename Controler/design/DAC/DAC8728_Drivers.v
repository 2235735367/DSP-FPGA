
module   DAC8728_Drivers 
(
	input		wire				clk			,	// drivers work clock 10MHz
	input		wire				rst_n		,	// drivers reset signal
	input		wire	[4:0]		add_in		,	// address signal	
	input		wire	signed  [15:0]		data_in		, 	// data signal
	input		wire				send		, 	// data send signal

	output		reg					done		,	// transfer done signal 0:working... 1: worked
	
	output		reg					dac_re_wr	,	// DAC write and read signal
	output		reg					dac_cs_n	,	// DAC select chip signal
	
	output		reg		[4:0]		dac_add		,	// DAC registers address
	output		reg	signed 	[15:0]		dac_data	 	// DAC registers data
);


// FSM state registers
	reg		[15:0]			current_state;
	reg		[15:0]			next_state;
	
// FSM state parameter		
	localparam			IDLE = 16'b0_000_000_000_000_001;
	localparam			S1   = 16'b0_000_000_000_000_010;
	localparam			S2   = 16'b0_000_000_000_000_100;
	localparam			S3   = 16'b0_000_000_000_001_000;
	localparam			S4   = 16'b0_000_000_000_010_000;
	localparam			S5   = 16'b0_000_000_000_100_000;
	localparam			S6   = 16'b0_000_000_001_000_000;
	localparam			S7   = 16'b0_000_000_010_000_000;
	localparam			S8   = 16'b0_000_000_100_000_000;
	localparam			S9   = 16'b0_000_001_000_000_000;
	localparam			S10  = 16'b0_000_010_000_000_000;
	localparam			S11  = 16'b0_000_100_000_000_000;
	localparam			S12  = 16'b0_001_000_000_000_000;
	localparam			S13  = 16'b0_010_000_000_000_000;
	localparam			S14  = 16'b0_100_000_000_000_000;
	localparam			S15  = 16'b1_000_000_000_000_000;
	
// FSM-1
	always @ (posedge clk or negedge rst_n) begin
		if(!rst_n) begin
			current_state <= IDLE;
		end
		else begin
			current_state <= next_state;
		end
	end
	
// FSM-2
	always @ (*) begin
		if(!rst_n) begin
			next_state = IDLE;
		end
		else begin
			case (current_state)
			IDLE  : begin 
				if(send)begin
					next_state = S1;  
				end
				else begin
					next_state = IDLE;  
				end
			end
			
			S1    : begin 
				next_state = S2;  
			end
			
			S2    : begin 
				next_state = S3;  
			end
			
			S3    : begin 
				next_state = S4;  
			end
			
			S4    : begin 
				next_state = S5;  
			end
			
			S5    : begin 
				next_state = S6;  
			end
			
			S6    : begin 
				next_state = S7;  
			end
			
			S7    : begin 
				next_state = S8;  
			end
			
			S8    : begin 
				next_state = S9;  
			end
			
			S9    : begin 
				next_state = S10;  
			end
			
			S10   : begin 
				next_state = S11;  
			end
			
			S11   : begin 
				next_state = IDLE;  
			end	

			default : begin 
				next_state = IDLE; 
			end
			endcase
		end
	end

// FSM-3
	// dac_cs_n signal
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			dac_cs_n <= 1'b1;
		end
		else begin
			case (current_state)
				IDLE : begin
					dac_cs_n <= 1'b1;
				end
				
				S1   : begin
					dac_cs_n <= 1'b1;
				end
				
				S2   : begin
					dac_cs_n <= 1'b1;
				end
				
				S3   : begin
					dac_cs_n <= 1'b1;
				end
				
				S4   : begin
					dac_cs_n <= 1'b0;
				end
				
				S5   : begin
					dac_cs_n <= 1'b0;
				end
				
				S6   : begin
					dac_cs_n <= 1'b0;
				end
				
				S7   : begin
					dac_cs_n <= 1'b1;
				end
				
				S8   : begin
					dac_cs_n <= 1'b1;
				end
				
				S9   : begin
					dac_cs_n <= 1'b1;
				end
				
				S10  : begin
					dac_cs_n <= 1'b1;
				end
				
				S11  : begin
					dac_cs_n <= 1'b1;
				end
				
				default: begin
					dac_cs_n <= 1'b1;
				end
			endcase
		end
	end	
	
	// dac_re_wr signal
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			dac_re_wr <= 1'b1;
		end
		else begin
			case (current_state)
				IDLE : begin
					dac_re_wr <= 1'b1;
				end
				
				S1   : begin
					dac_re_wr <= 1'b1;
				end
				
				S2   : begin
					dac_re_wr <= 1'b1;
				end
				
				S3   : begin
					dac_re_wr <= 1'b0;
				end
				
				S4   : begin
					dac_re_wr <= 1'b0;
				end
				
				S5   : begin
					dac_re_wr <= 1'b0;
				end
				
				S6   : begin
					dac_re_wr <= 1'b0;
				end
				
				S7   : begin
					dac_re_wr <= 1'b0;
				end
				
				S8   : begin
					dac_re_wr <= 1'b1;
				end
				
				S9   : begin
					dac_re_wr <= 1'b1;
				end
				
				S10  : begin
					dac_re_wr <= 1'b1;
				end
				
				S11  : begin
					dac_re_wr <= 1'b1;
				end
				
				default: begin
					dac_re_wr <= 1'b1;
				end
			endcase
		end
	end	
	
	// dac_add signal
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			dac_add <= 5'b00_111;
		end
		else begin
			case (current_state)
				IDLE : begin
					dac_add <= 5'b00_111;
				end
				
				S1   : begin
					dac_add <= add_in;
				end
				
				S2   : begin
					dac_add <= add_in;
				end
				
				S3   : begin
					dac_add <= add_in;
				end
				
				S4   : begin
					dac_add <= add_in;
				end
				
				S5   : begin
					dac_add <= add_in;
				end
				
				S6   : begin
					dac_add <= add_in;
				end
				
				S7   : begin
					dac_add <= add_in;
				end
				
				S8   : begin
					dac_add <= add_in;
				end
				
				S9   : begin
					dac_add <= add_in;
				end
				
				S10  : begin
					dac_add <= 5'b00_111;
				end
				
				S11  : begin
					dac_add <= 5'b00_111;
				end
				
				default: begin
					dac_add <= 5'b00_111;
				end
			endcase
		end
	end
	
	// dac_data signal
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			dac_data <= 16'h80e8;
		end
		else begin
			case (current_state)
				IDLE : begin
					dac_data <= 16'h80e8;
				end
				
				S1   : begin
					dac_data <= 16'h80e8;
				end
				
				S2   : begin
					dac_data <= data_in;
				end
				
				S3   : begin
					dac_data <= data_in;
				end
				
				S4   : begin
					dac_data <= data_in;
				end
				
				S5   : begin
					dac_data <= data_in;
				end
				
				S6   : begin
					dac_data <= data_in;
				end
				
				S7   : begin
					dac_data <= data_in;
				end
				
				S8   : begin
					dac_data <= data_in;
				end
				
				S9   : begin
					dac_data <= data_in;
				end
				
				S10  : begin
					dac_data <= 16'h80e8;
				end
				
				S11  : begin
					dac_data <= 16'h80e8;
				end
				
				default: begin
					dac_data <= 16'h80e8;
				end
			endcase
		end
	end
	
	// done signal
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			done <= 1'b1;
		end
		else begin
			case (current_state)
				IDLE : begin
					done <= 1'b1;
				end
				
				S1   : begin
					done <= 1'b0;
				end
				
				S2   : begin
					done <= 1'b0;
				end
				
				S3   : begin
					done <= 1'b0;
				end
				
				S4   : begin
					done <= 1'b0;
				end
				
				S5   : begin
					done <= 1'b0;
				end
				
				S6   : begin
					done <= 1'b0;
				end
				
				S7   : begin
					done <= 1'b0;
				end
				
				S8   : begin
					done <= 1'b0;
				end
				
				S9   : begin
					done <= 1'b0;
				end
				
				S10  : begin
					done <= 1'b0;
				end
				
				S11  : begin
					done <= 1'b1;
				end
				
				default: begin
					done <= 1'b1;
				end
			endcase
		end
	end	
	
endmodule
// --------------------------------------------------------------------
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// --------------------------------------------------------------------












