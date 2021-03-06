library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity zidongshouhuoji is
port(clkk,clk7:in std_logic;
	 choose1,choose2,choose3,choose4,choose5,choose6:in std_logic;
	 buy1,buy2,buy3,buy4,buy5,buy6:in std_logic;
	 chuhuo1,chuhuo2,chuhuo3,chuhuo4,chuhuo5,chuhuo6:out std_logic;
	 quehuo1,quehuo2,quehuo3,quehuo4,quehuo5,quehuo6:out std_logic;
	 price1, price2, price3, price4, price5, price6:out std_logic_vector(2 downto 0);
	 smg:out std_logic_vector(7 downto 0);
	 teq:out std_logic_vector(7 downto 0));
end zidongshouhuoji;

architecture zd of zidongshouhuoji is
   component kongzhi1
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
	 end component;
	 
	 component kongzhi2
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
	 end component;
	 
	 component kongzhi3
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
	 end component;
	 
	 component kongzhi4
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
	 end component;
	 
	 component kongzhi5
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
	 end component;
	 
	 component kongzhi6
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
	 end component;
	 
  component shumashuzi
 port(	clk7:in std_logic;
		sel:out std_logic_vector(2 downto 0);
		dain0,dain1,dain2,dain3,dain4,dain5,dain6,dain7:in std_logic_vector(3 downto 0);
		daout:out std_logic_vector(3 downto 0));
  end component;
  
  component shumaxianshi
port(num:in std_logic_vector(3 downto 0);
     smg:out std_logic_vector(7 downto 0));
  end component;
  
  component xuanzeshuma
   port(
		 sel:in std_logic_vector(2 downto 0);
		 teq:out std_logic_vector(7 downto 0));
  end component;
  
  component jishu60
port(shiwei1,shiwei2,shiwei3,shiwei4,shiwei5,shiwei6,gewei1,gewei2,gewei3,gewei4,gewei5,gewei6:in std_logic_vector(3 downto 0);
	 num7,num8:out std_logic_vector(3 downto 0));

 end component;
 
 component huowushu
port(hw1,hw2,hw3,hw4,hw5,hw6:out std_logic_vector(3 downto 0));
end component;

component fenshiqi
port(clkk:in std_logic;
     clkk1,clkk2,clkk3,clkk4,clkk5,clkk6:out std_logic);
end component;    
     
  signal sel1:std_logic_vector(2 downto 0);
  signal daout1:std_logic_vector(3 downto 0);
  signal dain00,dain11,dain22,dain33,dain44,dain55,dain66,dain77:std_logic_vector(3 downto 0);
  signal gewei11,shiwei11,gewei22,shiwei22,gewei33,shiwei33,gewei44,shiwei44,gewei55,shiwei55,gewei66,shiwei66:std_logic_vector(3 downto 0);
  signal hw11,hw22,hw33,hw44,hw55,hw66:std_logic_vector(3 downto 0);
  signal f1,f2,f3,f4,f5,f6:std_logic;
begin
  u1:huowushu port map(hw1=>hw11,hw2=>hw22,hw3=>hw33,hw4=>hw44,hw5=>hw55,hw6=>hw66);
  u2:kongzhi1 port map(login1=>hw11,j1=>shiwei11,j11=>gewei11,num1=>dain00,clk1=>f1,choose1=>choose1,buy1=>buy1,chuhuo1=>chuhuo1,quehuo1=>quehuo1,price1=>price1);
  u3:kongzhi2 port map(login2=>hw22,j2=>shiwei22,j22=>gewei22,num2=>dain11,clk2=>f2,choose2=>choose2,buy2=>buy2,chuhuo2=>chuhuo2,quehuo2=>quehuo2,price2=>price2);
  u4:kongzhi3 port map(login3=>hw33,j3=>shiwei33,j33=>gewei33,num3=>dain22,clk3=>f3,choose3=>choose3,buy3=>buy3,chuhuo3=>chuhuo3,quehuo3=>quehuo3,price3=>price3);
  u5:kongzhi4 port map(login4=>hw44,j4=>shiwei44,j44=>gewei44,num4=>dain33,clk4=>f4,choose4=>choose4,buy4=>buy4,chuhuo4=>chuhuo4,quehuo4=>quehuo4,price4=>price4);
  u6:kongzhi5 port map(login5=>hw55,j5=>shiwei55,j55=>gewei55,num5=>dain44,clk5=>f5,choose5=>choose5,buy5=>buy5,chuhuo5=>chuhuo5,quehuo5=>quehuo5,price5=>price5);
  u7:kongzhi6 port map(login6=>hw66,j6=>shiwei66,j66=>gewei66,num6=>dain55,clk6=>f6,choose6=>choose6,buy6=>buy6,chuhuo6=>chuhuo6,quehuo6=>quehuo6,price6=>price6);
  u8:shumashuzi port map(dain0=>dain00,dain1=>dain11,dain2=>dain22,dain3=>dain33,dain4=>dain44,dain5=>dain55,dain6=>dain66,dain7=>dain77,daout=>daout1,sel=>sel1,clk7=>clk7);
  u9:shumaxianshi port map(num=>daout1,smg=>smg);
  u10:xuanzeshuma port map(sel=>sel1,teq=>teq);
  u11:jishu60 port map(shiwei1=>shiwei11,gewei1=>gewei11,shiwei2=>shiwei22,gewei2=>gewei22,shiwei3=>shiwei33,gewei3=>gewei33,shiwei4=>shiwei44,gewei4=>gewei44,shiwei5=>shiwei55,gewei5=>gewei55,shiwei6=>shiwei66,gewei6=>gewei66,num7=>dain66,num8=>dain77);
  u12:fenshiqi port map(clkk1=>f1,clkk2=>f2,clkk3=>f3,clkk4=>f4,clkk5=>f5,clkk6=>f6,clkk=>clkk);
end zd;
  