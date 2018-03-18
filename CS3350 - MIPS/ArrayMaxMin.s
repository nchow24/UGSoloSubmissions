# problem3.s
#
# Prints the maximum and minimum of an array
# 
# Nicole Chow (nchow24)
# Feb 26, 2018


        .data
maxH:	.asciiz "Maximum: "							# max heading (used in printing)
minH:	.asciiz "     Minimum: "					# min heading (used in printing)
array:  .word 5, 18, 9, 1, 3, 14, 10, 4, 6, 7		# array v[]
	.extern foobar 4

        .text
        .globl main
main:   li $v0, 4									# syscall 4 (print string)
        la $a0, maxH								# argument: the max heading
		syscall										# print the max heading

		#set up registers to find max and min from array
		la $a0, array								# address of array is in a0
		addi $a1, $zero, 10							# there are 10 elements in the array
		jal maxMin									# call maxMin function

		#print return values
		add $a0, $v0, $zero							# argument: the max
		li $v0, 1									# syscall 1 (print integer)
		syscall										# print the max value
		li $v0, 4									# syscall 4 (print string)
        la $a0, minH								# argument: string
		syscall										# print the min heading
		li $v0, 1									# syscall 1 (print integer)
		add $a0, $v1, $zero							# argument: the min	
		syscall										# print min
		li $v0, 10									# syscall 10 (exit)
		syscall										# end program



maxMin: 
		add $t0, $zero, $zero						# initialize counter
		lw	$t1, 0($a0)								# initialize min with v[0]
		lw	$t2, 0($a0)								# initialize max with v[0]
loop:	beq $t0, $a1, done							# if counter > # elements, exit
		sll $t3, $t0, 2								# calculate offset
		add $t3, $t3, $a0 							# calculate address of element
		lw	$t4, 0($t3)								# load element
		bgt $t4, $t1, max							# if t4 > t1 then skip setting min
		add $t1, $t4, $zero							# set min
max:	blt $t4, $t2, nextEl						# if t4 < t2, then skip setting max
		add $t2, $t4, $zero							# set max
nextEl:	addi $t0, $t0, 1							# increment counter to get next element
        j loop										# loop 
done:	add $v0, $t2, $zero							# save max as a return variable
		add $v1, $t1, $zero							# save min as a return variable
		jr $ra										# exit function