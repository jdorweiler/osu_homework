TITLE MASM Template						(main.asm)

; Description:
; 
; Revision date:

INCLUDE Irvine32.inc
.data
myMessage BYTE "Jason Dorweiler",0dh,0ah,0

.code
main PROC
	call Clrscr

	mov	 edx,OFFSET myMessage
	call WriteString

	exit
main ENDP

END main