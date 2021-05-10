.begin
.org 2048
prog: 	ld [base], %r1		! Your assembly code here
	ld [base], %r2
	ld [exp], %r10
	
pow:	subcc %r10, 1, %r10
	ble fin

multi:	add %r1, %r3, %r3
	subcc %r2, 1, %r2
	bg multi
	
	mov %r3, %r1
	clr %r3
	ld [base], %r2
	ba pow

fin:	st %r1, [res]
	halt

	base: 4
	exp: 7 	! 4 to the power of 7 (47)
	res: 0 	! Should be 16384 when program is done

.end

