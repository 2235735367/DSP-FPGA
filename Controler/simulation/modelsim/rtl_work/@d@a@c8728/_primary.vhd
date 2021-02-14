library verilog;
use verilog.vl_types.all;
entity DAC8728 is
    generic(
        DELAY           : integer := 100
    );
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        add_in          : in     vl_logic_vector(4 downto 0);
        data_in         : in     vl_logic_vector(15 downto 0);
        done_dac        : out    vl_logic;
        dac_re_wr       : out    vl_logic;
        dac_cs_n        : out    vl_logic;
        dac_add         : out    vl_logic_vector(4 downto 0);
        dac_data        : out    vl_logic_vector(15 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DELAY : constant is 1;
end DAC8728;
