library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity xuanze is
	port(
		 price1,price2,price3,price4,price5,price6: in std_logic_vector(3 downto 0);
		 price: out std_logic_vector(3 downto 0);
		 jishi1,jishi2,jishi3,jishi4,jishi5,jishi6: in std_logic;
		 ksjs,showjs: out std_logic);
end xuanze;

architecture one of xuanze is

begin
	process(jishi1,jishi2,jishi3,jishi4,jishi5,jishi6)
	begin
		if(jishi1='1' or jishi2='1' or jishi3='1' or jishi4='1' or jishi5='1' or jishi6='1') then
			ksjs<='1';showjs<='1';
		else ksjs<='0';showjs<='0';
		end if;
		
		if price1/="0000" then price<=price1;
		elsif price2/="0000" then price<=price2;
		elsif price3/="0000" then price<=price3;
		elsif price4/="0000" then price<=price4;
		elsif price5/="0000" then price<=price5;
		elsif price6/="0000" then price<=price6;
		else  price<="0000";
		end if;
	end process;
	
end one;