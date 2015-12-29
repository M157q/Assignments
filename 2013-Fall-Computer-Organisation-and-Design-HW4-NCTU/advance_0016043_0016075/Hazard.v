module Hazard(
					ID_RSaddr,
					ID_RTaddr,
					EX_MemRead,
					EX_RTaddr,
					PC_Stall,
					IFID_Stall,
                    ID_Flush
                );

input[4:0] 	ID_RSaddr;
input[4:0]	ID_RTaddr;
input		EX_MemRead;
input[4:0]	EX_RTaddr;
output	reg	PC_Stall;
output	reg	IFID_Stall;
output	reg	ID_Flush;



always@(*)
begin
	if( EX_MemRead && ( (EX_RTaddr==ID_RSaddr) || (EX_RTaddr==ID_RTaddr) ))
    begin
		PC_Stall <= 1'b1;
		IFID_Stall <= 1'b1;
		ID_Flush <= 1'b1;
	end
	else
    begin
		PC_Stall <= 1'b0;
		IFID_Stall <= 1'b0;
		ID_Flush <= 1'b0;
	end

end
endmodule
