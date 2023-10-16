.syntax unified
.section .text

.global factorial

factorial:
CMP r0, #0x0 @if input is 0 or 1 we return 0. If input less than 0 we return 9999 as a placeholder error value
BEQ isZero
BLT invalidInput
CMP r0, #0xd
BLT validInput

invalidInput: @negative values of n
MOV r0, #0x99 @ERROR VALUE
bx lr

isZero: @n=0
MOV r0, #0x01 @by def 0! = 1
bx lr @jump back to function call
validInput:
CMP r0, #0x01 @check if input is 1
BEQ isOne

b greaterThanOne @if input is greater than 1 we need to calculate recursively

isOne:
MOV r0, #0x01 @by def 1! = 1
bx lr @return 1 if input is 1

greaterThanOne:
MOV r1, r0 @hold value of r0 in r1 and then we push it to stack
recursive:

@----prologue-----
PUSH {r1, lr} @r1 is our current 'n' and then we also push our link register for returning calls
@----------------

SUB r1, r1, #0x01 @ n = n-1 and check condition of (n==1)
@recursive part

CMP r1, #0x01 @if n==1
BEQ one @branch to one
bl recursive @if n>1 we do it again
one:
MUL r0, r1 @ n * 1 * 2 * ... * (n-1)
CMP r1, r2
BEQ escape @if our current n value is equal to one less than original n then we are done
@--------epilogue--------
POP {r1, pc} @jumps you back to 'recursive:' with new r1
@-----------------------
escape: @finally we just need to return to the caller line

POP {pc}


.global addition
addition: @trivial
PUSH {lr}
ADD r0, r0, r1
POP {pc}

.global subtraction
subtraction: @trivial
PUSH {lr}
SUB r0, r0, r1
POP {pc}

.global multiplication
multiplication:@trivial
PUSH {lr}
MUL r0, r1, r0
POP {pc}

.global division
division:
PUSH {lr}

MOV r4, #0x01 @if we dont have negative inputs then we end up mulitplying by 1
MOV r5, #0x01 @these are modified later if the input is negative

CMP r0, #0x0 @checking if negative
BLT negative_r0
b skip_negative_r0
negative_r0:
MOV r4, #0x-1 @if we were dividing by a negative than we want to flip the sign
MUL r0, r0, r4@if r0 is negative we make it positive and multiply rseult by -1


skip_negative_r0: @get here if r0 was positive
CMP r1, #0x0
BLT negative_r1 @if r1 is negative then we want to multiply result by -1
b skip_negative_r1

negative_r1:
MOV r5, #0x-1
MUL r1, r1, r5 @if r1 is negative then we make it positive and multiply result by -1


skip_negative_r1:
MOV r2, #0x0 @START OF DIVISION
MOV r3, #0x0

div_loop_start:
CMP r0, r1 @if r0 <= r1 we are done
BLT exit_div
BEQ exit_div
SUB r0, r0, r1 @if not <= we must subtract from numerator and add one to counter
ADD r2, #0x01
b div_loop_start @repeat until less than or =
exit_div: @reached when less than or equal to
BNE div_end
ADD r2, #0x01 @if r1 = r0 then we need to add one more to counter (possibly not best way but it works :D )
div_end:
MOV r0, r2
MUL r0, r0, r4 @dealing with signs of input
MUL r0, r0, r5
POP {pc}

.global exponentiation
exponentiation:
PUSH {lr}

MOV r2, r0 @this is our base
CMP r2, #0x01 @if base is one then result will be one
BEQ sum_end

CMP r1, #0x30 @This would always result in overflow if greater than
BGT exp_invalid

exp_loop_start:
CMP r1, #0x1 
BLT exp_zero_or_negative @if exponent less than one we recieved a negative exponent input
BEQ exit_exp @done when r1 = 1
MUL r0, r2 @we multiply r0 by the base until the exponent has reached 0
SUB r1, #0x01 @decrement exponent
b exp_loop_start
exp_zero_or_negative:
CMP r1, #0x00
BNE exp_negative @else exponent is zero
MOV r0, #0x1 @anything to the power of zero is 1
b exit_exp
exp_negative:
MOV r0, #0x0 @negative exponent so return 0

b exit_exp
exp_invalid: @return -1 if invalid input
MOV r0, #0x0
SUB r0, #0x1

exit_exp:
POP {pc}

.global sumation
sumation: @sum from i to n
PUSH {lr}
LDR r3, =max_int @for checking purposes
MOV r2, #0x0 
sum_loop_start:
CMP r0, r1 @we know to stop when the counter is the upper bound (i=n)
BGT sum_end @greater than because we include upper bound
SUB r4, r3, r2 @if max_int - r2 < r0 then we will overflow
CMP r4, r0
BLT sum_invalid

ADD r2, r0 @add current value of 'i'
ADD r0, #0x01
b sum_loop_start
sum_invalid:
MOV r2, #0x0
SUB r2, #0x1 @-1 is the error value

sum_end:
MOV r0, r2
POP {pc}

.global gcd
gcd: @if we subtract the greater value from the lesser value until they're equal we get the gcd
PUSH {lr}
gcd_start:
CMP r0, r1
BEQ gcd_equal @If r1 = r0 then we have found the gcd
BLT gcd_less
SUBS r0, r0, r1 @this is the "greater than" path
b gcd_start
gcd_less:
SUBS r1, r1, r0
b gcd_start

gcd_equal: @done
POP {pc}

.global bit_counting
bit_counting:
PUSH {lr}
MOV r3, #0x0
MOV r1, #0b1 @we will be shifting this value to count ones
bit_loop_start:
CMP r1, r0 @if 0b0000..010...0 is greater than input than we wont get any more ones
BGT exit_bit_counting
AND r2, r0, r1 @result is 0x0 if there wasnt a 1 in this location
CMP r2, #0x0
LSL r1, #0x1 @shift left and repeat
BNE add_bit_counting @if result was not 0 then there was a one in that location, add to counter
b bit_loop_start
add_bit_counting:
ADD r3, #0x01 @increment counter
b bit_loop_start

exit_bit_counting:
MOV r0, r3
POP {pc}

.section .data
max_int: .word  0xffffffff

