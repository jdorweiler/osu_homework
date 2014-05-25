;TITLE Basic Math Calculator			(main.asm)
; Name: Jason Dorweiler
; Description: Calculates addition, subtraction, multiplication, and division
; Course : CS271
; Revision date: 1/8/14

INCLUDE Irvine32.inc

.data
intro_1		BYTE	"    Elementary Arithmetic  by Jason Dorweiler", 0
prompt_1	BYTE	"First Number: ", 0
intro_2		BYTE	"Enter 2 numbers, and I'll show you the sum, difference, product, quotient, and remainder.",0
prompt_2	BYTE	"Second Number: ", 0
goodbye		BYTE	"	Impressed? Goodbye!",0
firstNum	DWORD	?
SecNum		DWORD	?
addition	DWORD	?
subtract	DWORD	?
multi		DWORD	?
quotient	DWORD	?
remainder	DWORD	?
d1			REAL8	?
rem			BYTE	" remainder ",0
plus		BYTE	" + ",0
subt		BYTE	" - ",0
mult		BYTE	" * ",0
divi		BYTE	" / ",0
equal		BYTE	" = ",0

.code
main PROC
	; Intro
	mov		edx, OFFSET intro_1
	call	WriteString
	call	CrLf
	call	CrLf
start:
	mov		edx, OFFSET intro_2
	call	WriteString
	call	CrLf
	call	CrLf

	; get the data
	mov		edx, OFFSET prompt_1
	call	WriteString
	call	ReadInt
	mov		firstNum, eax

	mov		edx, OFFSET prompt_2
	call	WriteString
	call	ReadInt
	mov		secNum, eax

	; calculate
	;add
	mov		eax, firstNum
	add		eax, secNum
	mov		addition, eax

	;subtract
	mov		eax, firstNum
	sub		eax, secNum
	mov		subtract, eax

	;multiply
	mov		eax, firstNum
	mul		secNum
	mov		multi, eax

	;divide
	mov		eax, firstNum
	cdq
	mov		ebx, secNum
	idiv	ebx
	mov		quotient, eax
	mov		remainder, edx


	; display results
	mov		eax, firstNum
	call	WriteDec
	mov		edx, OFFSET plus
	call	WriteString
	mov		eax, secNum
	call	WriteDec
	mov		edx, OFFSET equal
	call	WriteString
	mov		eax, addition
	call	WriteDec
	call	CrLf

	mov		eax, firstNum
	call	WriteDec
	mov		edx, OFFSET subt
	call	WriteString
	mov		eax, secNum
	call	WriteDec
	mov		edx, OFFSET equal
	call	WriteString
	mov		eax, subtract
	call	WriteInt
	call	CrLf

	mov		eax, firstNum
	call	WriteDec
	mov		edx, OFFSET mult
	call	WriteString
	mov		eax, secNum
	call	WriteDec
	mov		edx, OFFSET equal
	call	WriteString
	mov		eax, multi
	call	WriteDec
	call	CrLf

	mov		eax, firstNum
	call	WriteDec
	mov		edx, OFFSET divi
	call	WriteString
	mov		eax, secNum
	call	WriteDec
	mov		edx, OFFSET equal
	call	WriteString
	mov		eax, quotient
	call	WriteInt
	mov		edx, OFFSET rem
	call	WriteString
	mov		eax, remainder
	call	WriteDec
	call	CrLf
	call	CrLf
	call	CrLf
; say goodbye
	mov		edx, OFFSET goodbye
	call	WriteString
	call	CrLf
	call	CrLf
	call	CrLf

; loop forever
	jmp start


	exit
main ENDP

END main 