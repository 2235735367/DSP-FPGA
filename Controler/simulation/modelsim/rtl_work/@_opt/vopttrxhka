library verilog;
use verilog.vl_types.all;
entity DAC8728_Drivers is
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        add_in          : in     vl_logic_vector(4 downto 0);
        data_in         : in     vl_logic_vector(15 downto 0);
        send            : in     vl_logic;
        done            : out    vl_logic;
        dac_re_wr       : out    vl_logic;
        dac_cs_n        : out    vl_logic;
        dac_add         : out    vl_logic_vector(4 downto 0);
        dac_data        : out    vl_logic_vector(15 downto 0)
    );
end DAC8728_Drivers;
