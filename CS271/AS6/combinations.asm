TITLE CS271 homework #6b			(combintions.asm)
; Name: Jason Dorweiler
;
; Description:  Generates a random C(n,r) problem that is displayed to the 
;	user.  The user's input is read using writeStr, a procedure that reads
;	a string and converts it to a decimal number. 
;
; Course : CS271
; Revision date: 3/10/14

INCLUDE Irvine32.inc

;write string macro used in lecture
WriteStr MACRO buffer
	push edx
	mov edx, OFFSET buffer
	call WriteString
	pop edx
ENDM

.data
hi = 12
Rlo = 1
Nlo = 3
MAXSIZE	= 100

prompt1	BYTE "Welcome to the combinations calculator by Jason Dorweiler",0
prompt2	BYTE "I'll give you a problem.  Enter your answer, and I'll tell",0
prompt3	BYTE "you if you are correct.",0
another	BYTE "Another problem? (y/n): ",0
q1		BYTE "Number of elements to chose from the set: ",0
q2		BYTE "How many ways can you choose? ",0
q3		BYTE "Number of elements in the set: ",0
ans1	BYTE "There are ",0
ans2	BYTE " combinations of ",0
ans3	BYTE " items from a set of ",0
prob	BYTE "Problem:",0
right	BYTE "You are correct!",0
wrong	BYTE "Incorrect, you need more practice",0
err		BYTE "Integers only! Please enter an integer number: ",0
err2	BYTE "Invalid response ",0
goodbye	BYTE "OK ... goodbye.",0
sLength	DWORD	0
again	BYTE	?

inSt	BYTE	MAXSIZE DUP(?)		; User's string
rval	DWORD ?
nval	DWORD ?
rsave	DWORD ?
nsave	DWORD ?
rnval	DWORD ?
usrAns	DWORD ?
result	DWORD ?

.code
main PROC
	call Randomize		;seed PRNG

	call intro			;show user the intro heading

	push OFFSET nsave
	push OFFSET rsave
	push OFFSET rval
	push OFFSET nval
	call showProblem	;generate random c(n,r) problem

	push OFFSET usrAns
	call getdata		;read users response with writeStr

	push OFFSET rnval
	push OFFSET result
	push OFFSET nval
	push OFFSET rval
	call doCalc			;calculate c(n,r)

	push usrAns
	push nsave
	push rsave
	push result
	call showResult		;evaluate users ans and show results
	 
	exit			
main ENDP

; ****************** Show the result of the calculation *********
;desc: this procedure shows the results of the c(n,r) calculation
;receives: userAns, nsave, rsave, result by value
;returns: print to screen
;preconditions: the variables have been determined by other proc
;registers changed eax, ecx both saved and restored 
; ***************************************************************
showResult PROC
	push ebp
	mov	ebp,esp

	WriteStr ans1
	mov eax, [ebp+8]
	call writeDec

	WriteStr ans2
	mov eax, [ebp+12]
	call writeDec

	WriteStr ans3
	mov eax, [ebp+16]
	call writeDec
	call crlf

	mov eax, [ebp+8]
	mov ecx, [ebp+20]
	cmp eax, ecx
	je correct

incorrect:
	WriteStr wrong
	call crlf
	jmp done
correct:
	WriteStr right
	call crlf

done:
	writeStr another
	mov edx, OFFSET again
	call ReadString
	mov esi, edx	;move string here
	cld
	lodsb
	cmp	al,110	; 'n' 
	je getOut
	cmp	al,121	; 'y'
	je runAgain
	WriteStr err2
	jmp done

runAgain:
	call crlf
	call main
	 
getOut:
	writeStr goodbye
	call crlf	
	pop ebp
	ret 16

showResult ENDP

; ****************** Do the C(n,r) calculation ******************
;desc: does the c(n,r) calculation
;receives: nrval, rval, nval, result by ref
;returns: values are calculated and updated
;preconditions: none
;registers changed eax, ecx, edi all saved and restored 
; ***************************************************************
doCalc PROC
	push ecx
	push eax
	push edi
	push ebx
	push ebp
	mov	ebp,esp
	sub esp, 4			;3 locals

	;calc n-r
	mov ecx, [ebp+28]
	mov edx, [ecx]
	mov ecx, [ebp+24]
	mov ebx, [ecx]
	sub edx, ebx
	mov ecx, [ebp+36]
	mov [ecx], edx

	;get r!	
	push [ebp+24]	
	call factorial

	;get n!		
	push [ebp+28]
	call factorial

	;get (n-r)!
	push [ebp+36]		
	call factorial

	mov ecx, [ebp+36]
	mov edi, [ecx]		;(n-r)! in edi
	mov ecx, [ebp+24]
	mov eax, [ecx]		;n!
	mul edi				
	mov ebx, eax		;n!(n-r)! in ebx

	mov edi, [ebp+28]
	mov eax, [edi]
	cdq
	div ebx
	mov ecx, [ebp+32]
	mov [ecx], eax		;store result

	mov esp, ebp		;clean up locals
	pop ebp
	pop ebx
	pop edi
	pop eax
	pop ecx
	ret 16
doCalc ENDP

; ****************** get user value *****************************
;desc: get the number input from the user.  Read it in as a string
; and convert it to a number
;receives: nval by ref
;returns: nval is updated to the user's value
;preconditions: none
;registers changed edx, ecx, ebx, eax
; ***************************************************************
getData PROC
	push ebp
	mov	ebp,esp
	mov	ecx,[ebp+8]		;nval
top:
	mov	edx,OFFSET inSt
	mov	ecx,MAXSIZE
	call ReadString
	mov esi, edx	;move string here
	mov	sLength,eax		;number of chars in string
	mov	ecx,eax
	cld
	mov ebx, 0

counter:
	lodsb
	cmp	al,48	; 'a' is character 97
	jl	notNum
	cmp	al,57	; 'z' is character 122
	jg	notNum
	
	sub al, 48
	mov dl, al ;store in dl
	mov al, bl
	mov dh, 10	
	mul dh
	add al,dl
	mov ebx, eax
	loop	counter
	jmp done

notNum:
	writeStr err
	jmp top

done:
	mov edi, [ebp+8]
	mov [edi], eax
	pop ebp
	ret 8
getData ENDP

; ****************** Print the intro header    ******************
;desc: print out the start screen
;receives: prompt1, promp2, prompt as string global
;returns: prints to the screen
;preconditions: none
;registers changed edx
; ***************************************************************
intro PROC
	WriteStr prompt1
	call crlf
	WriteStr prompt2
	call crlf
	WriteStr prompt3
	call crlf
	call crlf
	ret
intro ENDP

; ****************** Recursive Factorial Calc  ******************
;desc: Takes the number by ref and calculates the factorial of 
; that number
;receives: number by ref
;returns: changes value stored in number
;preconditions: none
;registers eax, edi, ecx
; ***************************************************************
factorial PROC
	push ebp
	mov	ebp,esp
	mov	edi,[ebp+8]		;number in ecx
	mov eax, [edi]
	sub esp, 4			;locals
	cmp eax, 0
	je bcase

	mov [ebp-4], eax	;store eax
	 
	dec eax
	mov [edi], eax
	push edi
	call factorial
	mov ecx, [ebp-4]
	mul ecx
	mov [edi], eax
	jmp quit	;skip over base

bcase:
	mov eax, 1

quit:
	mov esp, ebp		;clean up locals
	pop ebp
	ret 8
factorial ENDP

; ****************** Display the problem  ***********************
;desc: Generate a random c(n,r) problem and display it to the user
;receives: nval,rval,nsave,rsave all by ref
;returns: value in nval, rval, nsave, rsave are updated
;preconditions: none
;registers eax, edi, ecx saved and restored
; ***************************************************************  
showProblem PROC
	push eax
	push edi
	push ecx
	push ebp
	mov	ebp,esp
	sub esp, 4	
	mov	ecx,[ebp+20]	;nval
	mov	edi,[ebp+24]	;rval

	WriteStr prob
	call crlf
	WriteStr q3
	;generate random n
	mov eax,hi				;random int code used in lecture
	sub eax,nlo
	inc eax
	call RandomRange
	add eax, nlo
	mov edi, [ebp+20]
	mov [edi], eax		;store random in rval
	mov [ebp-4], eax
	mov edi, [ebp+32]
	mov [edi], eax		;save nval again 

	; write rval
	call writeDec
	call crlf
l1:
	mov eax, [ebp-4]	;set rval as high limit				
	sub eax,Rlo
	inc eax
	call RandomRange
	add eax, rlo
	mov edi, [ebp+24]
	mov [edi], eax
	mov edi, [ebp+28]
	mov [edi], eax		;save rval again 
	cmp eax, [ebp-4]
	jge l1

	WriteStr q1
	call writeDec
	call crlf
	WriteStr q2


	mov esp, ebp		;clean up locals
	pop ebp
	pop ecx
	pop edi
	pop eax
	ret 8
showProblem ENDP

END main
 