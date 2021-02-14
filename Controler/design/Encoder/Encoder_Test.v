module Encoder_Test  #
(
	parameter		WIDTH = 32			,
	parameter		DUTY  = 32'd5000		,
	parameter		CYCLE = 32'd10000	
)
(
	input		wire				clk			,
	input		wire				rst_n		,
	output		reg					pwm_out1	,				
	output		reg					pwm_out2					
);


	reg		[WIDTH-1:0]			cnt_pwm;
	reg							pwm_clk;
	
	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			cnt_pwm <= 1'b0;
		end
		else begin
			if(cnt_pwm >= (CYCLE - 1'b1))begin
				cnt_pwm <= 1'b0;
			end
			else begin
				cnt_pwm <= cnt_pwm + 1'b1;
			end
		end
	end

	always @ (posedge clk  or  negedge rst_n) begin
		if(!rst_n) begin
			pwm_clk <= 1'b1;
		end
		else begin
			if(cnt_pwm >= DUTY) begin
				pwm_clk <= 1'b0;
			end 
			else begin
				pwm_clk <= 1'b1;
			end
		end
	end
	
	always @ (posedge pwm_clk  or  negedge rst_n) begin
		if(!rst_n) begin
			pwm_out1 <= 1'b0;
		end
		else begin
			pwm_out1 <= ~pwm_out1;
		end
	end
	
	always @ (negedge pwm_clk  or  negedge rst_n) begin
		if(!rst_n) begin
			pwm_out2 <= 1'b0;
		end
		else begin
			pwm_out2 <= ~pwm_out2;
		end
	end

endmodule