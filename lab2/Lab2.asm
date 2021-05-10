	.begin
	.org 2048
prog: 	ld [flt], %r1				! Your assembly code here
	sll %r1, 1, %r3
	srl %r3, 24, %r4
	add %r4, -127, %r5
	st %r5, [exp]
	halt
flt: 	0xc14a0000 			! 32-bit float to load
exp: 	0x0 				! store exponent as integer here

	.end


