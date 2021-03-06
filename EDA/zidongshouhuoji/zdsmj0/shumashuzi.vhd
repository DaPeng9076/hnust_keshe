library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity shumashuzi is
	port(
		 clk7:in std_logic;
		 sel:out std_logic_vector(2 downto 0);
		 dain0,dain1,dain2,dain3,dain4,dain5,dain6,dain7:in std_logic_vector(3 downto 0);
		 daout:out std_logic_vector(3 downto 0));
end shumashuzi;

architecture a of shumashuzi is
	signal temp:integer range 0 to 7 ;
	
begin
	
	process(clk7)
	begin
		if clk7'event and clk7='1' then
			if temp=7 then temp<=0;
			else temp<=temp+1;
		end if;
			case temp is
				when 0=>sel<="000";daout<=dain0;
				when 1=>sel<="001";daout<=dain1;
				when 2=>sel<="010";daout<=dain2;
				when 3=>sel<="011";daout<=dain3;
				when 4=>sel<="100";daout<=dain4;
				when 5=>sel<="101";daout<=dain5;
				when 6=>sel<="110";daout<=dain6;
				when 7=>sel<="111";daout<=dain7;
			end case;
		end if;
	end process;
end a;