	# Michael Pottker

	# This program recursively counts how many times
	# a specified digit appears in the given number.
	# Each call to count_digit divides the number by 10
	# and gets the rightmost digit until the base
	# case is reached. Result is then set to either
	# 0 or 1 for the base case and then is set equal
	# to the return of the recursive call and
	# incremented accordingly. It then prints out
	# the number of occurrences.
	
	.data
	
x:	.word 0
y:	.word 0
answer:	.word -1
newln:	.asciiz "\n"

	.text

main:	li $sp, 0x7ffffffc	# set up stack pointer
	
	li       $v0, 5         # scanf("%d", &x)
	syscall
	move    $t1, $v0
	sw      $t1, x

	li       $v0, 5         # scanf("%d", &y)
	syscall
	move    $t2, $v0
	sw      $t2, y
	
	sw	$t1, ($sp)	# push x
	sub 	$sp, $sp, 4

	sw 	$t2, ($sp)	# push y
	sub 	$sp, $sp, 8
	
	jal	count_digit	# call count_digit

	add	$sp, $sp, 12	# pop arg
	
	move 	$t0, $v0	# store return value
	sw	$t0, answer
        
	move    $a0, $t0        # printf("%d", answer)
	li      $v0, 1
	syscall

	la      $a0, newln    # printf("%c", '\n')
	li      $v0, 4
	syscall

	li      $v0, 10         # quit program
	syscall

count_digit:			#prologue
	sub 	$sp, $sp, 16 	# set new stack ptr
	sw 	$ra, 16($sp)	# save $ra
	sw 	$fp, 12($sp)	# save fp
	add	$fp, $sp, 16	# set new $fp

	lw	$t3, 12($fp)	# get arg num
	lw	$t4, 8($fp)	# get arg digit
	
	li 	$t0, -1		# result= -1
	sw	$t0, 8($sp)	
	
	blt	$t4, 0, endif	# if (digit < 0) skip if
	bgt	$t4, 9, endif	# if (digit > 9) skip if

	
	li	$t0, 0		# result= 0
	sw	$t0, 8($sp)

	bge 	$t3, 0, skip1	# if (num >= 0) skip if

	mul	$t3, $t3, -1	# num= -num
	sw	$t3, 12($fp)
	j	skip1
	
skip1:	blt 	$t3, 0, else	# if (num < 0) do else
	bgt	$t3, 9, else	# if (num > 9) do else

	bne	$t3, $t4, ielse	# if (num != digit) do inner else

	li	$t0, 1		# result= 1
	sw	$t0, 8($sp)
	j 	endif

ielse:	li	$t0, 0		# result= 0
	sw	$t0, 8($sp)
	j 	endif
	
else:	rem	$t5, $t3, 10	# rightmost= num % 10
	sw	$t5, 4($sp)

	div	$t3, $t3, 10	# push num / 10
	sw	$t3, ($sp)
	sub	$sp, $sp, 4
		
	sw	$t4, ($sp)	# push digit
	sub	$sp, $sp, 8
	
	
	jal 	count_digit	# call count_digit

	add 	$sp, $sp, 12	# pop arg

	move    $t0, $v0        # store return value
	sw      $t0, 8($sp)

	lw	$t5, 4($sp)	# restore rightmost
	
	bne	$t5, $t4, endif	# if (rightmost != digit)

	add	$t0, $t0, 1	# result++
	sw	$t0, 8($sp)	
	
endif:	move	$v0, $t0	# return result

				# epilogue
	lw	$ra, 16($sp)	# restore $ra
	lw	$fp, 12($sp)	# reset $fp
	add	$sp, $sp, 16	# reset $sp
	jr	$ra		# return to caller
	
	
