module Forwarding(
					EX_RSaddr,
					EX_RTaddr,
					MEM_RegWrite,
					MEM_RDaddr,
					WB_RegWrite,
					WB_RDaddr,
					FACtrl,
                    FBCtrl
                );

					
input[4:0] 	EX_RSaddr;
input[4:0] 	EX_RTaddr;
input		MEM_RegWrite;
input[4:0] 	MEM_RDaddr;
input		WB_RegWrite;
input[4:0]	WB_RDaddr;
output[1:0]	FACtrl;
output[1:0]	FBCtrl;

reg[1:0]	FACtrl;
reg[1:0]	FBCtrl;

wire	EXhazard_RS;
wire	EXhazard_RT;
wire	MEMhazard_RS;
wire	MEMhazard_RT;

assign 	EXhazard_RS = ( MEM_RegWrite && MEM_RDaddr && (MEM_RDaddr==EX_RSaddr) ) ? 1 : 0;
assign 	EXhazard_RT = ( MEM_RegWrite && MEM_RDaddr && (MEM_RDaddr==EX_RTaddr) ) ? 1 : 0;
assign	MEMhazard_RS= ( WB_RegWrite && WB_RDaddr && !EXhazard_RS && (WB_RDaddr==EX_RSaddr) ) ? 1 : 0;
assign	MEMhazard_RT= ( WB_RegWrite && WB_RDaddr && !EXhazard_RT && (WB_RDaddr==EX_RTaddr) ) ? 1 : 0;

always@(*)
begin

	if(EXhazard_RS) 
    begin
		FACtrl <= 2'b10;
		FBCtrl <= 2'b00;
	end
	else if(EXhazard_RT) 
    begin
		FACtrl <= 2'b00;
		FBCtrl <= 2'b10;
	end
	else if(MEMhazard_RS)
    begin
		FACtrl <= 2'b01;
		FBCtrl <= 2'b00;
	end
	else if(MEMhazard_RT)
    begin
		FACtrl <= 2'b00;
		FBCtrl <= 2'b01;
	end
	else
    begin
		FACtrl <= 2'b00;
		FBCtrl <= 2'b00;
	end

end

endmodule
