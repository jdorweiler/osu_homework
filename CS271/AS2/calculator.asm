; Name: Jason Dorweiler
; Description: Calculates addition, subtraction, multiplication, and division
; Course : CS271
; Revision date: 1/8/14

INCLUDE Irvine32.inc

.data
; General purpose variables
a      DWORD     ?
b      DWORD     ?
e      BYTE      ?
d      BYTE      ?
upperLevel   DWORD     18
lowerLevel   DWORD      3
; Strings
yes    BYTE     "Yes",0
no     BYTE     "No",0
maybe  BYTE     "Maybe",0

.code
   main PROC
   mov   eax, 1
   cmp   AH, e
   jg    option1
   jmp   option3
option1:
   mov   edx, OFFSET yes
   call  WriteString
   jmp   endOfProgram
option2:
   mov   edx, OFFSET no
   call  WriteString
   jmp   endOfProgram
option3:
   mov   edx, OFFSET maybe
   call  WriteString
endOfProgram:
   exit
main ENDP
END main 