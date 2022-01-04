library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity init is	--init goods num
	port(
		 price1,price2,price3,price4,price5,price6: out std_logic_vector(3 downto 0);
		 goods1,goods2,goods3,goods4,goods5,goods6: out std_logic_vector(3 downto 0));
end init;

architecture goods of init is
begin
	goods1<="1001";
	goods2<="0000";
	goods3<="1001";
	goods4<="1001";
	goods5<="1001";
	goods6<="1001";
	
	price1<="0001";
	price2<="0010";
	price3<="0011";
	price4<="0100";
	price5<="0101";
	price6<="0110";
end goods;