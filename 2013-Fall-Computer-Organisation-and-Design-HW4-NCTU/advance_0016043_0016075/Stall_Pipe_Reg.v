module Stall_Pipe_Reg(
    rst_i,
    clk_i,
    stall_i,
    data_i,
    data_o
);
					
parameter size = 0;

input               rst_i;
input               clk_i;	
input               stall_i;	  
input   [size-1: 0] data_i;

output  [size-1: 0] data_o;

reg     [size-1: 0] data_o;
reg 	[size-1: 0] data_stall;
	  
always @(posedge clk_i) 
begin
	if(~rst_i)
        data_o <= 0;
	else if(stall_i)
		data_o <= data_stall;
	else 
    begin
		data_o     <= data_i;
		data_stall <= data_i;
	end
end

endmodule	
