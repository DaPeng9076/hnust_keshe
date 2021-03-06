library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;


entity showsmg is
	port(
		 clk: in std_logic;
		 nin0,nin1,nin2,nin3,nin4,nin5,nin6,nin7: in std_logic_vector(3 downto 0);
		 smg: out std_logic_vector(7 downto 0);
		 smgnum: out std_logic_vector(7 downto 0));
end showsmg;

architecture one of showsmg is
	
	signal temp: integer range 0 to 7 :=0;
	signal num: std_logic_vector(3 downto 0);
	signal daout0,daout1,daout2,daout3,daout4,daout5,daout6,daout7: std_logic_vector(3 downto 0);
    signal sel:std_logic_vector(2 downto 0);

begin
	process(clk)
	begin
		if clk'event and clk='1' then
			if temp=7 then temp<=0;
			else temp<=temp+1;
		end if;
			case temp is
				when 0=>sel<="000";num<=nin0;
				when 1=>sel<="001";num<=nin1;
				when 2=>sel<="010";num<=nin2;
				when 3=>sel<="011";num<=nin3;
				when 4=>sel<="100";num<=nin4;
				when 5=>sel<="101";num<=nin5;
				when 6=>sel<="110";num<=nin6;
				when 7=>sel<="111";num<=nin7;
			end case;
		end if;
	end process;
	
	process(num)
	begin 
		case num is
			when "0000"=>smg<="00111111";
			when "0001"=>smg<="00000110";
			when "0010"=>smg<="01011011";
			when "0011"=>smg<="01001111";
			when "0100"=>smg<="01100110";
			when "0101"=>smg<="01101101";
			when "0110"=>smg<="01111101";
			when "0111"=>smg<="00100111";
			when "1000"=>smg<="01111111";
			when "1001"=>smg<="01101111";
			when others=>smg<="00000000";
			
		end case;
	end process;
	
	smgnum<="11111110" when sel=0 else
	"11111101" when sel=1 else
	"11111011" when sel=2 else
	"11110111" when sel=3 else
	"11101111" when sel=4 else
	"11011111" when sel=5 else
	"10111111" when sel=6 else
	"01111111" when sel=7 else
	"11111111";

end one;
