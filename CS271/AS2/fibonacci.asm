;TITLE Fibonacci number generator			(fibonacci.asm)
; Name: Jason Dorweiler
; Description: Gets user input and displays Fibonacci numbers
; Course : CS271
; Revision date: 1/26/14

INCLUDE Irvine32.inc

.data
intro_1		BYTE	"    Fibonacci Numbers  by Jason Dorweiler", 0
prompt_1	BYTE	"Enter your name: ", 0
prompt_2	BYTE	"Enter a number of Fibonacci numbers to see from 1 - 46: ", 0
greet		BYTE	"Hello, ",0
goodbye		BYTE	"Goodbye!",0
space		BYTE	" ",0
defaultS	BYTE	"             ",0 ; spaces for first two numbers
space5		BYTE	"     ",0 ; 5 spaces
error		BYTE	" *** Input Error: enter number between 1 - 46",0
fib1		DWORD	1 ;first fibonacci seed
fib2		DWORD	1 ;second fibonacci seed
count		DWORD	3 ;number of values per line set to 3 for 2 seeds
FibNum		DWORD	?
LargeNum	DWORD	100000000 ;largest fib number we expect
upperLim	DWORD	46 ; highest fib number to calculate
MAX = 80
UserName	BYTE	MAX+1 DUP(?) ; max size plus 1 for null


.code
main PROC
	; Intro
	mov eax,yellow + (black*16) ;sets text color to yellow
	call SetTextColor
	mov	edx, OFFSET intro_1
	call	WriteString
	call	CrLf
	call	CrLf

	
	; get the data
	mov	edx, OFFSET prompt_1
	call	WriteString
Name:
	;get users name
	mov	edx, OFFSET UserName
	mov	ecx, MAX
	call	ReadString

	;greet user
	mov	edx, OFFSET greet
	call	WriteString
	mov	edx, OFFSET UserName
	call	WriteString
	call	CrLf

	; we get the number from the user and 
	; check the number with the input filter
	; function. Loop back here if the input
	; is not correct.
Number:
	mov	edx, OFFSET prompt_2; ask for number
	call	WriteString
	call	ReadInt
	mov	FibNum, eax
	cmp	eax, 1
	jl	inputFilter			; check the input is 1 or greater
	mov	FibNum, eax
	cmp	eax, upperLim
	jg	inputFilter			; check the input is less than 47
	mov	eax, FibNum			;move here to do subtraction since first 2 are seed values
	sub	eax, 2
	mov	ecx,eax				;move to iterator, ecx is now FibNum - 2
	call	CrLf

	; Calculate fibonacci numbers
	;first display seed numbers
	mov eax,red + (black*16) ;sets text color to red
	call SetTextColor
	mov eax,fib1
	call	WriteDec
	mov edx, OFFSET defaultS
	call	WriteString
	mov eax, FibNum			;check the case for displaying 1 fib num. exit the program if true
	cmp eax, 2
	jl	endProg
	mov eax,fib1
	call	WriteDec
	mov edx, OFFSET defaultS
	call	WriteString
	mov eax, FibNum			;check the case for displaying 2 fib nums. exit the program if true
	cmp eax, 2
	je	endProg

	;calculate fibonacci
top:
	mov eax,fib1
	add	eax,fib2			; the next fib num is stored in eax
	call	WriteDec 
	mov ebx,fib1
	mov fib2,ebx
	mov	fib1,eax
	mov edx, OFFSET space5
	call	WriteString

	;how big is the number for printing
	mov eax, LargeNum
getNumSize:
	mov	ebx, 10
	cmp eax, fib1
	jl	return				;fib1 greater or equal than so stop printing spaces
	cdq
	idiv ebx				;eax/ebx, quotent in eax
	mov edx, OFFSET space
	call WriteString
	jmp getNumSize			;jmp up and print more spaces
	 
return:
	dec	count
	mov eax, 0
	cmp eax,count
	je reset
continue:
	loop top			; repeat until ecx is 0
	call	CrLf
	call	CrLf

; say goodbye
endProg:
	mov	edx, OFFSET goodbye
	call	WriteString
	call	CrLf
	call	CrLf
	call	CrLf

	exit
; print out error message and get number again
inputFilter:
	mov	edx, OFFSET error
	call	WriteString
	call	CrLf
	jmp	Number

; reset the counter for printing spaces
reset:
	mov	count, 5
	call	CrLf
	jmp continue

main ENDP	
END main 