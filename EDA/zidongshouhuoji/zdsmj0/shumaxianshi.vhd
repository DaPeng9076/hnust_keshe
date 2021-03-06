library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
entity shumaxianshi is
port(num:in std_logic_vector(3 downto 0);
     smg:out std_logic_vector(7 downto 0));
     end shumaxianshi;
     
architecture a of shumaxianshi is
begin
	 process(num)
	 begin 
	   case num is
			    when "0000"=>smg<="00111111";
				when "0001"=>smg<="00000110";
				when "0010"=>smg<="01011011";
				when "0011"=>smg<="01001111";
				when "0100"=>smg<="01100110";
				when "0101"=>smg<="01101101";
				when "0110"=>smg<="01111101";
				when "0111"=>smg<="00100111";
				when "1000"=>smg<="01111111";
				when "1001"=>smg<="01101111";
				when others=>smg<="00000000";
				
		end case;
	end process;
end a;