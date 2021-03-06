library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
entity xuanzeshuma is
	port(
		 sel:in std_logic_vector(2 downto 0);
		 teq:out std_logic_vector(7 downto 0));
end xuanzeshuma;
architecture one of xuanzeshuma is
begin
	teq<="11111110" when sel=0 else
		"11111101" when sel=1 else
		"11111011" when sel=2 else
		"11110111" when sel=3 else
		"11101111" when sel=4 else
		"11011111" when sel=5 else
		"10111111" when sel=6 else
		"01111111" when sel=7 else
		"11111111";
end one;