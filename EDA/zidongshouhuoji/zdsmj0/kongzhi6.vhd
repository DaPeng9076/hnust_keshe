library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity kongzhi6 is
port(clk6:in std_logic;
	 choose6:in std_logic;
	 buy6:in std_logic;
	 login6:in std_logic_vector(3 downto 0);
	 j6:buffer std_logic_vector(3 downto 0);
	 j66:buffer std_logic_vector(3 downto 0);
	 num6:out std_logic_vector(3 downto 0);
	 price6:out std_logic_vector(2 downto 0);
	 chuhuo6:out std_logic;
	 quehuo6:out std_logic);
end kongzhi6;
	 
architecture a of kongzhi6 is
begin
process(choose6,clk6,buy6)
variable count:std_logic_vector(3 downto 0);
variable init:bit;
variable j666,j6666:std_logic_vector(3 downto 0);
variable jianyi:bit;
variable reset:bit;
	begin
	if  clk6'event and clk6='1' then
	if init='0' then
	count:=login6;init:='1';
	end if;
	
		if choose6='1'  then
			if count="0000" then quehuo6<='1';
			else price6<="100";
					if j666="0000" and j6666="0000" and reset='0' then
					j666:="0110";j6666:="0000";
					end if;
				if buy6='1'  then
					j666:="0000";j6666:="0000";chuhuo6<='1';
						if jianyi='0' then
						count:=count-1;jianyi:='1';
						end if;
			    else				
						if j666="0000" and j6666="0000" then
							price6<="000";chuhuo6<='0';quehuo6<='0';
						else 				
								if j6666/="0000" then j6666:=j6666-1;
								else j6666:="1001";j666:=j666-1;
								end if;
									if j6666="0000" and j666="0000" then
									quehuo6<='0';chuhuo6<='0';price6<="000";reset:='1';
									end if;
								
						end if;
				end if; 
			end if;
			num6<=count;j6<=j666;j66<=j6666;
		else num6<=count;price6<="000";quehuo6<='0';chuhuo6<='0';j6<="0000";j66<="0000";jianyi:='0';j666:="0000";j6666:="0000";reset:='0';
		end if;
	end if;
end process;

end a;
	