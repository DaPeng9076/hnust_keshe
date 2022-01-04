library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity clkdiv is
	port(
		 clk: in std_logic;
		 ksjs,pay: in std_logic;
		 chaoshi,chuhuo: out std_logic;
		 gewei,shiwei: out std_logic_vector(3 downto 0));
end clkdiv;

architecture rt1 of clkdiv is
	signal count : integer range 0 to 100:=0;
	signal pcount : integer range 0 to 2:=0;
	signal clkdiv: std_logic;
	signal chuhuo0: std_logic:='0';
	signal chaoshi0: std_Logic:='0';
	signal gewei1: std_logic_vector(3 downto 0);
	signal shiwei1: std_logic_vector(3 downto 0):="0110";
begin
process(clk)
begin
	if(clk'event and clk='1') then
		if(count=100) then
			count<= 0;
		else
			count<=count + 1;
		end if;
	end if;
	
	if(clk'event and clk='1') then
		if(count=100) then
			clkdiv<='1';
		else
			clkdiv<='0';
		end if;
	end if;
	
end process;

process(clkdiv)
begin
	if(ksjs='1') then
		if(clkdiv='1') then
			if(gewei1="1111" and shiwei1="1111") then
				gewei1<="0000"; shiwei1<="0110";
			elsif(gewei1="0000" and shiwei1/="0000") then
				gewei1<="1001";shiwei1<=shiwei1-1;
			elsif(gewei1="0000" and shiwei1="0000") then
				gewei1<="1111";shiwei1<="1111";chaoshi0<='1';
			else
				gewei1<=gewei1-1;
			end if;
		end if;
	else
		gewei1<="1111";shiwei1<="1111";chaoshi0<='0';
	end if;
	gewei<=gewei1;shiwei<=shiwei1;chaoshi<=chaoshi0;
end process;

process(clk,clkdiv)
begin 
	if(pay='0') then
		chuhuo0<='1';
	end if;	

	if(clkdiv='1') then
		if(chuhuo0='1') then
			if(pcount=2) then
				pcount<=0;
				chuhuo0<='0';
			else pcount<=pcount+1;
			end if;
		end if;
	end if;
	chuhuo<=chuhuo0;
end process;
end rt1;