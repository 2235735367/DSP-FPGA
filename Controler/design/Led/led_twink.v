//led闪烁//
module led_twink(
    input   sys_clk,
    input   rst_n,
    
    output reg led
);
reg [23:0]  cnt;//计数器

always @(posedge sys_clk or negedge rst_n)
begin
    if(!rst_n)
        cnt <= 1'b0;
    else
        if(cnt < 24'd10000000)
            cnt <= cnt + 1'b1;//自加
        else
            cnt <= 24'd0;
end

always @(posedge sys_clk or negedge rst_n)
begin
    if(!rst_n)
        led <= 1'b0;
    else
        if(cnt == 24'd10000000)
            led <= ~led;
        else
            led <= led;
end

endmodule