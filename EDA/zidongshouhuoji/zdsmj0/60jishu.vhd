library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity jishu60 is
port(shiwei1,shiwei2,shiwei3,shiwei4,shiwei5,shiwei6,gewei1,gewei2,gewei3,gewei4,gewei5,gewei6:in std_logic_vector(3 downto 0);
	 num7,num8:out std_logic_vector(3 downto 0));
end jishu60;	 

architecture js of jishu60 is
begin
process(gewei1,gewei2,gewei3,gewei4,gewei5,gewei6,shiwei1,shiwei2,shiwei3,shiwei4,shiwei5,shiwei6)
begin 
 if shiwei1/="0000" or gewei1/="0000" then
 num7<=gewei1;num8<=shiwei1;
elsif shiwei2/="0000" or gewei2/="0000" then
 num7<=gewei2;num8<=shiwei2;
 elsif shiwei3/="0000" or gewei3/="0000" then
 num7<=gewei3;num8<=shiwei3;

elsif shiwei4/="0000" or gewei4/="0000" then
 num7<=gewei4;num8<=shiwei4;

elsif shiwei5/="0000" or gewei5/="0000" then
 num7<=gewei5;num8<=shiwei5;

elsif shiwei6/="0000" or gewei6/="0000" then
 num7<=gewei6;num8<=shiwei6;
 
 else
num7<="0000";num8<="0000";
end if;
end process;
end js;