# problem4.s
#
# Prints the combination of nCk given inputs n and k
# 
# Nicole Chow (nchow24)
# Feb 26, 2018


        .data
n:	.asciiz "Input n: "								# n heading (used in printing)
k:	.asciiz "Input k: "								# k heading (used in printing)
p41:.asciiz "Problem 4.1: "							# 4.1 heading (used in printing)
p42:.asciiz "     Problem 4.2: "					# 4.2 heading (used in printing)
	.extern foobar 4

        .text
        .globl main
main:   # get n
		addi $v0 , $0 , 4							# syscall 4 (print heading)   
		la $a0 , n									# argument: n heading 
		syscall										# print n heading
		addi $v0 , $0 , 5							# syscall 5 (get input)
		syscall										# get input for n
		move $a1 , $v0								# a1 holds n

		#get k
		addi $v0 , $0 , 4							# syscall 4 (print heading)   
		la $a0 , k									# argument: k heading 
		syscall										# print k heading
		addi $v0 , $0 , 5							# syscall 5 (get input)
		syscall										# get input for n
		move $a2 , $v0								# a2 holds k

		#calculate nCk using f41
		li $v0, 4									# syscall 4 (print string)
        la $a0, p41									# argument: 4.1 heading
		syscall										# print 4.1 heading
		jal f41										# call f41
		add $a0, $v0, $zero							# argument: return value from f41
		li $v0, 1									# syscall 1 (print integer)
		syscall										# print the return value

		#calculate nCk using f42
		li $v0, 4									# syscall 4 (print string)
        la $a0, p42									# argument: 4.2 heading
		syscall										# print 4.2 heading
		add $v0, $zero, $zero						# initialize return value
		jal f42										# call f42
		add $a0, $v0, $zero							# argument: return value from f42
		li $v0, 1									# syscall 1 (print integer)
		syscall	

		li $v0, 10									# syscall 10 (exit)
		syscall										# end program


f41:	add $t1, $zero, $zero						# initialize n!/k!
		blt $a1, $a2, exit							# if n < k, exit

		#calculate n!/k!
		add $t0, $zero, $a1							# initialize counter n!/k!
		addi $t1 $zero, 1							# t1 will hold n!/k!
loop1:	multu $t1, $t0								# calculate current n!/k! value
		mflo $t1									# load product
		addi $t0, $t0, -1							# decrement counter
		beq $t0, $a2, next1							# if counter < k, exit loop1 (n!/k! is done)
		j loop1										# loop to continue calculating n!/k!

		#calculate (n-k)!
next1:	addi $t0, $zero, 1							# initialize counter for (n-k)!
		addi $t2, $zero, 1							# initialize (n-k)!
		sub $t3, $a1, $a2							# get n-k
loop2:	multu $t2, $t0								# calculate current (n-k)! value
		mflo $t2									# load product
		beq $t0, $t3, next2							# if counter == n-k, exit loop2 ((n-k)! is done)
		addi $t0, $t0, 1							# increment counter
		j loop2

next2:	div $t1, $t2								# calculate combination
		mflo $t1									# load quotient
exit:	move $v0, $t1								# return combination
		jr $ra										# exit function



f42:	# push values on stack
		addi $sp, $sp, -12							# make space for 3 stack elements
		sw $a2, 8($sp)								# push k
		sw $a1, 4($sp)								# push n
		sw $ra, 0($sp)								# push return address

		# base case
		beq $a1, $a2, Base							# nCn = 1 so branch (no recursion needed)
		beq $a2, $zero, Base						# nC0 = 1 so branch (no recursion needed)

		# (n-1)C(k-1)
		addi $a1, $a1, -1							# decrement n
		addi $a2, $a2, -1							# decrement k
		jal f42										# recursive call with n = n-1 and k = k-1
		lw $ra, 0($sp)								# load last return address
		lw $a1, 4($sp)								# load last n
		lw $a2, 8($sp)								# load last k 

		# nC(k-1)
		addi $a1, $a1, -1							# decrement n
		jal f42										# recursive call with n = n-1 and k = k
		lw $ra, 0($sp)								# load last return address
		lw $a1, 4($sp)								# load last n
		lw $a2, 8($sp)								# load last k
		addi $sp, $sp, 12							# move stack pointer
		jr $ra										# exit 

Base:	addi $sp, $sp, 12							# pop top 3 from stack
		add $v0, $v0, 1								# nCn and nC0 = 1
		jr $ra										# exit 




 