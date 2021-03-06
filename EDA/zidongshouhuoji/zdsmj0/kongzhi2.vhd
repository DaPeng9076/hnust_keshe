library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity kongzhi2 is
port(clk2:in std_logic;
	 choose2:in std_logic;
	 buy2:in std_logic;
	 j2:buffer std_logic_vector(3 downto 0);
	 j22:buffer std_logic_vector(3 downto 0);
	 login2:in std_logic_vector(3 downto 0);
	 num2:out std_logic_vector(3 downto 0);
	 price2:out std_logic_vector(2 downto 0);
	 chuhuo2:out std_logic;
	 quehuo2:out std_logic);
end kongzhi2;
	 
architecture a of kongzhi2 is
begin
process(choose2,clk2,buy2)
variable count:std_logic_vector(3 downto 0);
variable init:bit;
variable j222,j2222:std_logic_vector(3 downto 0);
variable jianyi:bit;
variable reset:bit;
	begin
	if  clk2'event and clk2='1' then
	if init='0' then
	count:=login2;init:='1';
	end if;
	
		if choose2='1'  then
			if count="0000" then quehuo2<='1';
			else price2<="100";
					if j222="0000" and j2222="0000" and reset='0' then
					j222:="0110";j2222:="0000";
					end if;
				if buy2='1'  then
					j222:="0000";j2222:="0000";chuhuo2<='1';
						if jianyi='0' then
						count:=count-1;jianyi:='1';
						end if;
			    else				
						if j222="0000" and j2222="0000" then
							price2<="000";chuhuo2<='0';quehuo2<='0';
						else 				
								if j2222/="0000" then j2222:=j2222-1;
								else j2222:="1001";j222:=j222-1;
								end if;
									if j2222="0000" and j222="0000" then
									quehuo2<='0';chuhuo2<='0';price2<="000";reset:='1';
									end if;
								
						end if;
				end if; 
			end if;
			num2<=count;j2<=j222;j22<=j2222;
		else num2<=count;price2<="000";quehuo2<='0';chuhuo2<='0';j2<="0000";j22<="0000";jianyi:='0';j222:="0000";j2222:="0000";reset:='0';
		end if;
	end if;
end process;
end a;
	