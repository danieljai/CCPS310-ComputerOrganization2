.begin
.org 2048
prog: 	ld [x], %r1		! 8
	ld [y], %r2		! 3

rep: 	cmp %r1, %r2
	bl done
	subcc %r1, %r2, %r3

	inc %r10
	mov %r3, %r1
	ba rep

done: 	st %r10, [quot]
	st %r1, [rem]
	halt


	x: 8 ! Here, we're dividing 8/3
	y: 3
	quot: 0 ! Integer result would be 2 in this case
	rem: 0 ! remainder would also be 2

.end

