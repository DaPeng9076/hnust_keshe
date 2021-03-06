library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity goods is
	port(
		 clk: in std_logic;
		 pricein,goods: in std_logic_vector(3 downto 0);
		 priceout,goodsnum: out std_logic_vector(3 downto 0);
		 pay0,choose,chaoshi,reset: in std_logic;
		 quehuo,jishi: out std_logic);
end goods;

architecture onee of goods is
	signal quehuo0,init : std_logic:='0';
	signal jishi0,buying : std_logic:='0';
	signal quehuo1 : std_logic:='0';
	signal goodsnum1,price0: std_logic_vector(3 downto 0);

begin
process(clk,choose,chaoshi)	
begin
	if(clk'event and clk='1') then
		if(init='0') then
			goodsnum1<=goods;init<='1';
			jishi0<='0';
			price0<="0000";
		end if;
		
		if(reset='1') then
			goodsnum1<=goods;
			price0<="0000";
			jishi0<='0';
			buying<='0';
			quehuo0<='0';
		end if;
		
		if(choose='0') then
			if(goodsnum1="0000") then
				quehuo0<='1';
				price0<="0000";
			else
				price0<=pricein;
				quehuo0<='0';
				buying<='1';
				jishi0<='1';
			end if;
		end if;
		
		if(buying='1') then
			if(pay0='0') then
				buying<='0';
				jishi0<='0';
				price0<="0000";
				goodsnum1<=goodsnum1-1;
			end if;
			
			if(chaoshi='1') then
				price0<="0000";
				buying<='0';
				jishi0<='0';
			end if;
		end if;
		goodsnum<=goodsnum1;
		quehuo<=quehuo0;
		jishi<=jishi0;
		priceout<=price0;
	end if;
end process;

end onee;