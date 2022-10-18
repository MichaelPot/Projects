        # Michael Pottker

	# This program computes the sum of the cubes
	# of the first n integers that were read in
	# by scanf(). It then prints out the sum.

	.data

ans:    .word -1
n:      .word 0
newln: 	.asciiz "\n"
	
	.text

	lw 	$t1, n
	lw	$t0, ans
	
main:	li	 $v0, 5		# scanf("%d", &n)
	syscall	
	move 	$t1, $v0
	sw 	$t1, n

	li 	$t0, -1		# ans= -1
	sw 	$t0, ans

	blt 	$t1, 0, next 	# if (n < 0) skip if
	add 	$t2, $t1, 1	# n + 1
	mul 	$t3, $t2, $t1	# n * (n + 1)
	div 	$t4, $t3, 2	# (n * (n + 1)) / 2
	mul 	$t0, $t4, $t4	# ((n * (n + 1)) / 2) * ((n * (n + 1)) / 2)
	sw 	$t0, ans

next:	move 	$a0, $t0 	# printf("%d", ans)
	li 	$v0, 1
	syscall

	la 	$a0, newln	# printf("%c", '\n')
	li 	$v0, 4
	syscall

	li 	$v0, 10		# quit program
	syscall
