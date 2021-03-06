library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity kongzhi4 is
port(clk4:in std_logic;
	 choose4:in std_logic;
	 buy4:in std_logic;
	 login4:in std_logic_vector(3 downto 0);
	 j4:buffer std_logic_vector(3 downto 0);
	 j44:buffer std_logic_vector(3 downto 0);
	 num4:out std_logic_vector(3 downto 0);
	 price4:out std_logic_vector(2 downto 0);
	 chuhuo4:out std_logic;
	 quehuo4:out std_logic);
end kongzhi4;
	 
architecture a of kongzhi4 is
begin
process(choose4,clk4,buy4)
variable count:std_logic_vector(3 downto 0);
variable init:bit;
variable j444,j4444:std_logic_vector(3 downto 0);
variable jianyi:bit;
variable reset:bit;
	begin
	if  clk4'event and clk4='1' then
	if init='0' then
	count:=login4;init:='1';
	end if;
	
		if choose4='1'  then
			if count="0000" then quehuo4<='1';
			else price4<="100";
					if j444="0000" and j4444="0000" and reset='0' then
					j444:="0110";j4444:="0000";
					end if;
				if buy4='1'  then
					j444:="0000";j4444:="0000";chuhuo4<='1';
						if jianyi='0' then
						count:=count-1;jianyi:='1';
						end if;
			    else				
						if j444="0000" and j4444="0000" then
							price4<="000";chuhuo4<='0';quehuo4<='0';
						else 				
								if j4444/="0000" then j4444:=j4444-1;
								else j4444:="1001";j444:=j444-1;
								end if;
									if j4444="0000" and j444="0000" then
									quehuo4<='0';chuhuo4<='0';price4<="000";reset:='1';
									end if;
								
						end if;
				end if; 
			end if;
			num4<=count;j4<=j444;j44<=j4444;
		else num4<=count;price4<="000";quehuo4<='0';chuhuo4<='0';j4<="0000";j44<="0000";jianyi:='0';j444:="0000";j4444:="0000";reset:='0';
		end if;
	end if;
end process;

end a;
	