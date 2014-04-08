TITLE CS271 homework #3			(primes.asm)
; Name: Jason Dorweiler
;
; Description: Calcualte and print out primes based on a user entered limit
;	The algorithm uses a sieve of Eratosthenes method
;	https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
;	A static array holds boolean values that show if the 
;	index number of that element is prime Array[i] 1:prime 0:not prime
;	
; Course : CS271
; Revision date: 2/9/14

INCLUDE Irvine32.inc

.data
intro_1		BYTE	"    CS271 Homework #4 Prime number calculator  by Jason Dorweiler", 0
prompt_1	BYTE	"Enter your name: ", 0
prompt_2	BYTE	"Enter a number from 1 .. 200 and I will calculate that number of primes", 0
prompt_3	BYTE	"Enter a number: ", 0
greeting	BYTE	" Hello, ", 0
goodbye		BYTE	"Goodbye, ",0
error		BYTE	"Numbers from 1 - 200 only",0
Lspaces		BYTE	"   ",0
Sspaces		BYTE	" ",0
numLimit = 200					;upper limit on number that is entered	
MAX = 80
arrayLimit	= 1500						;we need a static array big enough to calculate 200 primes
sqrtLimit	=	42						;sqrt(arrayLimit) hard coded for now untill I can figure out how to calculate a square root
										;this is needed to control the outter loop of the seive.
number		DWORD	?					;current user entered number
prime		DWORD	?					;temp prime number storage
UsrName		BYTE	MAX+1 DUP(?)		;max user name, +1 for null
numArray	DWORD	arrayLimit DUP(0)	;array for arrayLimit numbers
lineNum	= 10							;number of primes printed on a line 
printNum = 1000							;largest prime we need to print


.code
main PROC

	call	intro
	call	getName
	call	setupArray	;sets the array to hold primes
	call	calcPrimes	
	call	farewell

main ENDP

;Procedure to print intro
;receives: intro_1 as global
;returns: nothing
;preconditions: none
;registers changed edx
intro PROC
	; print title and get users name
	mov edx, OFFSET intro_1
	call	WriteString
	call	CrLf
	ret
intro ENDP

;Procedure to print farewell
;receives: intro_1 as global
;returns: nothing
;preconditions: none
;registers changed edx
farewell PROC
	; Say goodbye
	call	CrLf
	mov edx, OFFSET goodbye
	call	WriteString
	mov edx, OFFSET usrName
	call	WriteString
	call	CrLf
	pop eax
	ret
farewell ENDP


;Procedure to get users name
;receives: prompt_1, prompt_2, greeting as global
;returns: global UsrName
;preconditions: none
;registers changed edx, ecx
getName PROC
	; Ask user for their name
	mov edx, OFFSET prompt_1
	call	WriteString
	;get name from user
	mov edx, OFFSET UsrName
	mov	ecx, MAX
	call	ReadString
	call	CrLf
	call	CrLf
	; greet the user
	mov edx, OFFSET greeting
	call	WriteString
	mov edx, OFFSET UsrName
	call	WriteString
	call	CrLf
	call	CrLf
	; print out instructions
getNumber:
	mov edx, OFFSET prompt_2
	call	WriteString
	call	CrLf
	call	CrLf
	call	ReadInt
	mov	number, eax
	cmp eax, numLimit
	jg printError
	cmp eax, 0
	jle printError
	call	CrLf
	ret
printError:
	mov edx, OFFSET error
	call	WriteString
	call	CrLf
	jmp getNumber
getName ENDP

setupArray PROC
;Procedure to fill the static array with 1s
;receives: numArray global
;returns: changes value in numArray
;preconditions: none
;registers changed eax, ecx
	xor ecx, ecx
	restart:
	mov eax, ecx
	mov [numArray+4*ecx], 1	;set array to 1
	mov eax, [numArray+4*ecx]
	inc	ecx
	cmp ecx, [arrayLimit-1]		;upto arrayLimit-1 since we starte ecx at 0
	jb	restart
	ret
setupArray ENDP


calcPrimes PROC
;Procedure to calculate primes with sieve of Eratosthenes
; the outter loop runs from i=0 to i < sqrt(n)
; inner loop runs from i=i^2 i < n 
;receives: numArray, sqrtLimit, lineNum as globals
;returns: changes value in numArray
;preconditions: numArray is initialized to all 1s
;registers changed edx, ebx, edi, eax, ecx
	mov edi, esp	;stack got a little wonky so store esp for later
	xor ecx, ecx
	xor ebx, ebx
	xor eax, eax
	xor edx, edx
	mov ecx, sqrtLimit
	add eax, 2
	push eax					;store counter on stack

	outterLoop:
	push ecx
	mov eax, [sqrtLimit+2]		
	sub eax, ecx				;eax stores i, outter loop counter
	push eax	
	cmp [numArray+4*eax], 1
	jne	increment
		
	innerLoop:
	pop eax
	push eax		;store i
	push edx		;store j
	mul eax			; eax^2
	pop edx			; j off stack
	pop ebx			;get i off stack, ebx now contains i
	push ebx		;store i back on stack
	push eax		;store i^2
	mov eax, edx	;inner loop counter in eax (j)
	push edx		; store j on stack
	mul ebx			; i*j, stored in eax
	pop edx			; get j from stack
	mov ebx, eax	;copy to ebx
	pop eax			;get i^2 from stack
	add	eax, ebx	;eax now contains i^2+j*i
	cmp eax, arrayLimit
	jg	increment

	setPrime:
	mov [numArray+4*eax], 0	; this is not a prime now
	inc edx					;j++ counter
	jmp innerLoop

	increment:
	mov edx, 0		;set inner loop counter to 0
	loop outterLoop	; use loop for counter in assignment requirements
	
	getOut:
	call printArray
	mov esp, edi	;move the stored esp back
	ret
calcPrimes ENDP

;Procedure to calculate primes with sieve of Eratosthenes
; the outter loop runs from i=0 to i < sqrt(n)
; inner loop runs from i=i^2 i < n 
;receives: numArray, sqrtLimit, lineNum as globals
;returns: changes value in numArray
;preconditions: numArray is initialized to all 1s
;registers changed edx, ebx, edi, eax, ecx
printArray PROC
	xor ecx, ecx
	xor ebx, ebx
	xor edx, edx

	mov ebx, 2
	mov ecx, number

	continue:
	mov eax, [numArray+4*ebx]
	cmp eax, 1
	jl skip
	mov eax, ebx
	call	WriteDec
	push edx		;store counter for number of primes on a line
	push ebx		;store ebx on stack
	mov prime, eax
	mov edx, OFFSET Lspaces
	call	WriteString
	mov eax, printNum

	printSpaces:
	mov ebx, 10
	cmp eax, prime
	jl noSpace		;prime is greater or equal so don't print spaces
	cdq
	idiv ebx		;eax/ebx, quotent in eax
	mov edx, OFFSET Sspaces
	call	WriteString
	jmp printSpaces

	noSpace:
	pop ebx
	pop edx
	dec ecx			;number of primes printed
	inc edx
	cmp edx, lineNum
	jl skip
	call	CrLf

	skip:
	inc	ebx	
	inc ecx
	cmp edx, lineNum
	jl toTop
	mov edx, 0

	toTop:
	loop continue	;use loop to print primes from the array
	ret
printArray ENDP
END main 