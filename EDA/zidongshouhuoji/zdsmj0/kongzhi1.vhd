library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity kongzhi1 is
port(clk1:in std_logic;
	 choose1:in std_logic;
	 buy1:in std_logic;
	 login1:in std_logic_vector(3 downto 0);
	 j1:buffer std_logic_vector(3 downto 0);
	 j11:buffer std_logic_vector(3 downto 0);
	 num1:out std_logic_vector(3 downto 0);
	 price1:out std_logic_vector(2 downto 0);
	 chuhuo1:out std_logic;
	 quehuo1:out std_logic);
end kongzhi1;
	 
architecture a of kongzhi1 is
begin
process(choose1,clk1,buy1)
variable count:std_logic_vector(3 downto 0);
variable init:bit;
variable j111,j1111:std_logic_vector(3 downto 0);
variable jianyi:bit;
variable reset:bit;
	begin
	if  clk1'event and clk1='1' then
	if init='0' then
	count:=login1;init:='1';
	end if;
	
		if choose1='1'  then
			if count="0000" then quehuo1<='1';
			else price1<="100";
					if j111="0000" and j1111="0000" and reset='0' then
					j111:="0110";j1111:="0000";
					end if;
				if buy1='0'  then
					j111:="0000";j1111:="0000";chuhuo1<='1';
						if jianyi='0' then
						count:=count-1;jianyi:='1';
						end if;
			    else				
						if j111="0000" and j1111="0000" then
							price1<="000";chuhuo1<='0';quehuo1<='0';
						else 				
								if j1111/="0000" then j1111:=j1111-1;
								else j1111:="1001";j111:=j111-1;
								end if;
									if j1111="0000" and j111="0000" then
									quehuo1<='0';chuhuo1<='0';price1<="000";reset:='1';
									end if;
								
						end if;
				end if; 
			end if;
			num1<=count;j1<=j111;j11<=j1111;
		else num1<=count;price1<="000";quehuo1<='0';chuhuo1<='0';j1<="0000";j11<="0000";jianyi:='0';j111:="0000";j1111:="0000";reset:='0';
		end if;
	end if;
end process;
end a;
	