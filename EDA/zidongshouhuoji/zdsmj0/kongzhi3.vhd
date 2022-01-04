library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity kongzhi3 is
port(clk3:in std_logic;
	 choose3:in std_logic;
	 buy3:in std_logic;
	 login3:in std_logic_vector(3 downto 0);
	 j3:buffer std_logic_vector(3 downto 0);
	 j33:buffer std_logic_vector(3 downto 0);
	 num3:out std_logic_vector(3 downto 0);
	 price3:out std_logic_vector(2 downto 0);
	 chuhuo3:out std_logic;
	 quehuo3:out std_logic);
end kongzhi3;
	 
architecture a of kongzhi3 is
begin
process(choose3,clk3,buy3)
variable count:std_logic_vector(3 downto 0);
variable init:bit;
variable j333,j3333:std_logic_vector(3 downto 0);
variable jianyi:bit;
variable reset:bit;
	begin
	if  clk3'event and clk3='1' then
	if init='0' then
	count:=login3;init:='1';
	end if;
	
		if choose3='1' then
			if count="0000" then quehuo3<='1';
			else price3<="100";
					if j333="0000" and j3333="0000" and reset='0' then
					j333:="0110";j3333:="0000";
					end if;
				if buy3='1'  then
					j333:="0000";j3333:="0000";chuhuo3<='1';
						if jianyi='0' then
						count:=count-1;jianyi:='1';
						end if;
			    else				
						if j333="0000" and j3333="0000" then
							price3<="000";chuhuo3<='0';quehuo3<='0';
						else 				
								if j3333/="0000" then j3333:=j3333-1;
								else j3333:="1001";j333:=j333-1;
								end if;
									if j3333="0000" and j333="0000" then
									quehuo3<='0';chuhuo3<='0';price3<="000";reset:='1';
									end if;
								
						end if;
				end if; 
			end if;
			num3<=count;j3<=j333;j33<=j3333;
		else num3<=count;price3<="000";quehuo3<='0';chuhuo3<='0';j3<="0000";j33<="0000";jianyi:='0';j333:="0000";j3333:="0000";reset:='0';
		end if;
	end if;
end process;

end a;
	