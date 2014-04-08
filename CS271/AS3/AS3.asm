TITLE CS271 homework #3			(HW3.asm)
; Name: Jason Dorweiler
; Description: sum all the positive numbers entered by the user
;	stop adding when a negative is entered and print the average
; Course : CS271
; Revision date: 1/29/14

INCLUDE Irvine32.inc

quiz4 MACRO p,q
	LOCAL here
	push eax
	push ecx
	mov eax, p
	mov ecx, q
here:
	mul p
	loop here

	mov p,eax
	pop ecx
	pop eax
ENDM

.data
x	DWORD 3

.code
main PROC
	mov ebx, 3
	mov ecx, 12
	mov edx, ecx
	quiz4 x, 4
	mov eax, x
	call writeDec

main ENDP
	
END main 