library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity kongzhi5 is
port(clk5:in std_logic;
	 choose5:in std_logic;
	 buy5:in std_logic;
	 login5:in std_logic_vector(3 downto 0);
	 j5:buffer std_logic_vector(3 downto 0);
	 j55:buffer std_logic_vector(3 downto 0);
	 num5:out std_logic_vector(3 downto 0);
	 price5:out std_logic_vector(2 downto 0);
	 chuhuo5:out std_logic;
	 quehuo5:out std_logic);
end kongzhi5;
	 
architecture a of kongzhi5 is
begin
process(choose5,clk5,buy5)
variable count:std_logic_vector(3 downto 0);
variable init:bit;
variable j555,j5555:std_logic_vector(3 downto 0);
variable jianyi:bit;
variable reset:bit;
	begin
	if  clk5'event and clk5='1' then
	if init='0' then
	count:=login5;init:='1';
	end if;
	
		if choose5='1'  then
			if count="0000" then quehuo5<='1';
			else price5<="100";
					if j555="0000" and j5555="0000" and reset='0' then
					j555:="0110";j5555:="0000";
					end if;
				if buy5='1'  then
					j555:="0000";j5555:="0000";chuhuo5<='1';
						if jianyi='0' then
						count:=count-1;jianyi:='1';
						end if;
			    else				
						if j555="0000" and j5555="0000" then
							price5<="000";chuhuo5<='0';quehuo5<='0';
						else 				
								if j5555/="0000" then j5555:=j5555-1;
								else j5555:="1001";j555:=j555-1;
								end if;
									if j5555="0000" and j555="0000" then
									quehuo5<='0';chuhuo5<='0';price5<="000";reset:='1';
									end if;
								
						end if;
				end if; 
			end if;
			num5<=count;j5<=j555;j55<=j5555;
		else num5<=count;price5<="000";quehuo5<='0';chuhuo5<='0';j5<="0000";j55<="0000";jianyi:='0';j555:="0000";j5555:="0000";reset:='0';
		end if;
	end if;
end process;

end a;
	