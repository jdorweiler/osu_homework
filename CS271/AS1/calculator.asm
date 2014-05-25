;TITLE Basic Math Calculator			(fibonacci.asm)
; Name: Jason Dorweiler
; Description: Gets user input and displays Fibonacci numbers
; Course : CS271
; Revision date: 1/16/14

INCLUDE Irvine32.inc
quiz4 MACRO p,q
	local here
	push eax
	push ecx
	mov eax,p
	mov ecx,q
here:
	mul	p
	loop here

	mov p,eax
	pop ecx
	pop eax
ENDM

.data

x   DWORD   3
y   DWORD   3


main PROC

mov ebx, 3
mov ecx, 12
mov edx, ecx
quiz4 ecx, ebx

main ENDP	
END main