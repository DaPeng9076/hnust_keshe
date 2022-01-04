library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity zidongshouhuoji is
port(
	 clk,clkk,reset,pay: in std_logic;
	 choose1,choose2,choose3,choose4,choose5,choose6: in std_logic;
	 quehuo1,quehuo2,quehuo3,quehuo4,quehuo5,quehuo6: out std_logic;
	 chuhuo,showjs: out std_logic;
	 price: out std_logic_vector(3 downto 0);
	 smg,smgnum: out std_logic_vector(7 downto 0));
end zidongshouhuoji;

architecture one of zidongshouhuoji is
	component init	--init goods
	port(
		 price1,price2,price3,price4,price5,price6: out std_logic_vector(3 downto 0);
		 goods1,goods2,goods3,goods4,goods5,goods6: out std_logic_vector(3 downto 0));
	end component;
	
	component clkdiv	--daojishi
	port(
		 clk: in std_logic;
		 ksjs,pay: in std_logic;
		 chaoshi,chuhuo: out std_logic;
		 gewei,shiwei: out std_logic_vector(3 downto 0));
	end component;
	
	component showsmg
	port(
		 clk: in std_logic;
		 nin0,nin1,nin2,nin3,nin4,nin5,nin6,nin7: in std_logic_vector(3 downto 0);
		 smg: out std_logic_vector(7 downto 0);
		 smgnum: out std_logic_vector(7 downto 0));
	end component;
	
	component goods
	port(
		 clk: in std_logic;
		 pricein,goods: in std_logic_vector(3 downto 0);
		 priceout,goodsnum: out std_logic_vector(3 downto 0);
		 pay0,choose,chaoshi,reset: in std_logic;
		 quehuo,jishi: out std_logic);
	end component;
	
	component xuanze
	port(
		 price1,price2,price3,price4,price5,price6: in std_logic_vector(3 downto 0);
		 price: out std_logic_vector(3 downto 0);
		 jishi1,jishi2,jishi3,jishi4,jishi5,jishi6: in std_logic;
		 ksjs,showjs: out std_logic);
	end component;
	
	signal igoods11,igoods22,igoods33,igoods44,igoods55,igoods66:std_logic_vector(3 downto 0);
	signal goods11,goods22,goods33,goods44,goods55,goods66:std_logic_vector(3 downto 0);
	signal price1,price2,price3,price4,price5,price6: std_logic_vector(3 downto 0);
	signal priceout1,priceout2,priceout3,priceout4,priceout5,priceout6: std_logic_vector(3 downto 0);
	signal jishi1,jishi2,jishi3,jishi4,jishi5,jishi6: std_logic;
	signal gewei,shiwei: std_logic_vector(3 downto 0);
	signal chaoshi, ksjs: std_logic:='0';
	
	
begin
	u1: init port map(goods1=>igoods11,goods2=>igoods22,goods3=>igoods33,goods4=>igoods44,goods5=>igoods55,goods6=>igoods66,price1=>price1,price2=>price2,price3=>price3,price4=>price4,price5=>price5,price6=>price6);
	u2: clkdiv port map(chuhuo=>chuhuo,pay=>pay,chaoshi=>chaoshi,clk=>clk,gewei=>gewei,shiwei=>shiwei,ksjs=>ksjs);
	u3: xuanze port map(price=>price,price1=>priceout1,price2=>priceout2,price3=>priceout3,price4=>priceout4,price5=>priceout5,price6=>priceout6,jishi1=>jishi1,jishi2=>jishi2,jishi3=>jishi3,jishi4=>jishi4,jishi5=>jishi5,jishi6=>jishi6,ksjs=>ksjs,showjs=>showjs);
	
	g1: goods port map(reset=>reset,pricein=>price1,priceout=>priceout1,chaoshi=>chaoshi,clk=>clkk,goods=>igoods11,choose=>choose1,quehuo=>quehuo1,goodsnum=>goods11,jishi=>jishi1,pay0=>pay);
	g2: goods port map(reset=>reset,pricein=>price2,priceout=>priceout2,chaoshi=>chaoshi,clk=>clkk,goods=>igoods22,choose=>choose2,quehuo=>quehuo2,goodsnum=>goods22,jishi=>jishi2,pay0=>pay);
	g3: goods port map(reset=>reset,pricein=>price3,priceout=>priceout3,chaoshi=>chaoshi,clk=>clkk,goods=>igoods33,choose=>choose3,quehuo=>quehuo3,goodsnum=>goods33,jishi=>jishi3,pay0=>pay);
	g4: goods port map(reset=>reset,pricein=>price4,priceout=>priceout4,chaoshi=>chaoshi,clk=>clkk,goods=>igoods44,choose=>choose4,quehuo=>quehuo4,goodsnum=>goods44,jishi=>jishi4,pay0=>pay);
	g5: goods port map(reset=>reset,pricein=>price5,priceout=>priceout5,chaoshi=>chaoshi,clk=>clkk,goods=>igoods55,choose=>choose5,quehuo=>quehuo5,goodsnum=>goods55,jishi=>jishi5,pay0=>pay);
	g6: goods port map(reset=>reset,pricein=>price6,priceout=>priceout6,chaoshi=>chaoshi,clk=>clkk,goods=>igoods66,choose=>choose6,quehuo=>quehuo6,goodsnum=>goods66,jishi=>jishi6,pay0=>pay);
	
	u: showsmg port map(clk=>clkk,nin0=>goods11,nin1=>goods22,nin2=>goods33,nin3=>goods44,nin4=>goods55,nin5=>goods66,nin6=>gewei,nin7=>shiwei,smg=>smg,smgnum=>smgnum);

end one;