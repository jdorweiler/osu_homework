;TITLE Basic Math Calculator			(fibonacci.asm)
; Name: Jason Dorweiler
; Description: Gets user input and displays Fibonacci numbers
; Course : CS271
; Revision date: 1/16/14

INCLUDE Irvine32.inc

.data

factorial   DWORD   ?
a   DWORD   4

.code
main PROC

	mov ecx, a
	mov factorial, 1

	top:
	mul ecx
	loop top

	call WriteDec


main ENDP	
END main 