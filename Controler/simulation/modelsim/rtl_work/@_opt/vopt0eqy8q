library verilog;
use verilog.vl_types.all;
entity Communication is
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        rd_n            : in     vl_logic;
        wr_n            : in     vl_logic;
        addr            : in     vl_logic_vector(17 downto 0);
        data            : inout  vl_logic_vector(15 downto 0);
        dac_re_wr       : out    vl_logic;
        dac_cs_n        : out    vl_logic;
        dac_add         : out    vl_logic_vector(4 downto 0);
        dac_data        : out    vl_logic_vector(15 downto 0)
    );
end Communication;
