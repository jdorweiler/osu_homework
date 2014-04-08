TITLE SquareList     (demo5.asm)

; Author: Paulson
; CS271	in-class demo        9/13/2012
; Description:  This program asks the user how many squares are required
;	and puts that many squares into an array so they can be displayed
;	in reverse order.

; Implementation note: Parameters are passed on the system stack.

INCLUDE Irvine32.inc
MAXSIZE	= 4
.data
array DWORD	MAXSIZE DUP(?)
.code
main PROC
	push Maxsize
	push 8
	push offset array
	call whatzit

	exit			;exit to operating system
main ENDP

whatzit PROC
	push ebp
	mov ebp, esp
	mov edi, [ebp+8]
	mov eax, 0
	mov ebx, [ebp+12]
	mov ecx, [ebp+16]
	mov edx, 0
fill:
	add eax, ebx
	mov [edi+edx], eax
	inc ebx
	dec eax
	add edx, 4
	loop fill

	pop ebp
	ret 12
whatzit ENDP

END main
