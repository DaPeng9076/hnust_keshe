library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity fenshiqi is
port(clkk:in std_logic;
     clkk1,clkk2,clkk3,clkk4,clkk5,clkk6:out std_logic);
end fenshiqi;
     
architecture a of fenshiqi is
signal c1,c2,c3,c4,c5,c6:std_logic;
begin
	clkk1<=clkk;
	clkk2<=clkk;
	clkk3<=clkk;
	clkk4<=clkk;
	clkk5<=clkk;
	clkk6<=clkk;
end a;