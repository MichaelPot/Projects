        # Michael Pottker 

	# This program counts the number of occurrences
	# of a specified digit in the given number.
	# It does this by calling count_digit()
	# which has a loop that divides the number by 10
	# to get the rightmost digit. And then checks
	# if that digit equals the one we're looking for.
	# It then prints out the number of occurrences.
	
	.data
	
x:	.word 0
y:	.word 0
result:	.word 0
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
	sw	$t0, result

	move    $a0, $t0        # printf("%d", result)
	li      $v0, 1
	syscall

	la      $a0, newln	# printf("%c", '\n')
	li      $v0, 4
	syscall

	li      $v0, 10         # quit program
	syscall

count_digit:			# prologue
	sub 	$sp, $sp, 16 	# set new stack ptr
	sw 	$ra, 16($sp)	# save $ra
	sw 	$fp, 12($sp)	# save fp
	add	$fp, $sp, 16	# set new $fp

	lw	$t3, 12($fp)	# get arg num
	lw	$t4, 8($fp)	# get arg digit
	
	li 	$t0, -1		# count= -1
	sw	$t0, 8($sp)	
	
	blt	$t4, 0, endif	# if (digit < 0) skip if
	bgt	$t4, 9, endif	# if (digit > 9) skip if

	li	$t0, 0		# count= 0
	sw	$t0, 8($sp)

	bge 	$t3, 0, skip1	# if (num >= 0) skip if

	mul	$t3, $t3, -1	# num= -num
	sw	$t3, 12($fp)
	
skip1:	bne 	$t3, 0, else	# if (num != 0) do else
	bne	$t4, 0, else	# if (digit != 0) do else
	
	li 	$t0, 1		# count= 1
	sw	$t0, 8($sp)

else:	
loop:	ble 	$t3, 0, endif	# if (num <= 0) exit while loop
	
	rem	$t5, $t3, 10	# rightmost= num % 10
	sw	$t5, 4($sp)

	bne 	$t5, $t4, skip 	# if (righmost != digit) skip if

	add	$t0, $t0, 1	# count++
	sw 	$t0, 8($sp)
	
skip:	div	$t3, $t3, 10	# num /= 10
	sw	$t3, 12($fp)

	j loop			# jump back to loop
	
endif:	move	$v0, $t0	# return count

				# epilogue
	lw	$ra, 16($sp)	# restore $ra
	lw	$fp, 12($sp)	# reset $fp
	add	$sp, $sp, 16	# reset $sp
	jr	$ra		# return to caller
	
	

	
