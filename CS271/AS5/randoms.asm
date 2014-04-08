TITLE CS271 homework #5			(randoms.asm)
; Name: Jason Dorweiler
; **** Extra Credit See Description Below *****
; Description: 
;	This program gets a user entered integer and generates a 
;	an array of random integers in the range of 100 - 999
;	The array is sorted using **Recursive Heap Sort** and
;	the output	is formatted into columns. 
;
; Course : CS271
; Revision date: 2/28/14

INCLUDE Irvine32.inc
MAXSIZE	= 200
MINSIZE = 10
lo = 100
hi = 999

.data
array		DWORD	MAXSIZE DUP(?)
number		DWORD	?
arrSize		DWORD	?
intro_1		BYTE	"This program will calculate random numbers in the range [100 .. 999],",0 
intro_2		BYTE	"it displays the original list, sorts the list using Heap Sort, calculates the median, and prints the list in decending order.",0
prompt1		BYTE	"How many numbers should be generated? [10 .. 200]: ",0
unsort		BYTE	"Un-sorted array",0
sorted		BYTE	"Sorted array",0
error		BYTE	"Invalid input",0
medPrompt	BYTE	"The median is ",0
space		BYTE		"   ",0
beep		BYTE	7h, 0

.code
main PROC
	call	Randomize

	push	OFFSET intro_1
	push	OFFSET intro_2
	call	Intro

	push	OFFSET beep
	push	OFFSET error
	push	OFFSET prompt1
	push	OFFSET number
	call	getData			;number from user

	push	OFFSET array
	push	OFFSET arrSize
	push	number
	call	fillArray		;fill array with random numbers

	push	OFFSET unsort
	push	OFFSET space
	push	OFFSET array
	push	arrSize
	call	printList

	push	OFFSET array
	push	arrSize
	call	sortList		;sort list with heap sort

	push	OFFSET medPrompt
	push	OFFSET array
	push	arrSize
	call	median			;calc and print median

	push	OFFSET sorted
	push	OFFSET space
	push	OFFSET array
	push	arrSize
	call	printList		;print sorted list
	call	crlf

	exit			
main ENDP

; ***************** Calculate and display median **************
;des: calculates the median of the array.  If the array has a 
; even number of elements it calculates the rounded average.
;receives: medPrompt, array by referance
;returns: none
;preconditions: array is sorted
;registers changed edx, ecx, edi, eax, ebp
; ***************************************************************
median PROC
	push	ebp
	mov	ebp,esp
	mov	eax,[ebp+8]		;array size in eax
	mov	edi,[ebp+12]	;address of array in esi

	mov ebx, 2
	cdq
	div ebx

	cmp edx, 0
	jg odd
	je evenN


odd:
	mov eax, [edi+eax*4]
	mov edx, [ebp+16]
	call writeString
	call writeDec
	call crlf
	call crlf
	jmp done

evenN:
	; calculate average of array here
	xor eax, eax
	mov ecx, [ebp+8]
cont:
	mov ebx, ecx
	dec ebx
	add eax, [edi+ebx*4]
	loop cont
	mov ecx, [ebp+8]
	div ecx				;eax has median
	mov ebx, eax
	mov eax, edx		;check rounding
	mov ecx, [ebp+8]	;array size
	div ecx
	cmp edx, 5
	jl print
	inc ebx
print:
	mov eax, ebx
	mov edx, [ebp+16]
	call writeString
	call writeDec
	call crlf
	call crlf
	jmp done

done:
	pop	ebp
	ret	16
median ENDP

; ***************** Print introduction **************************
;receives: intro1, intro2 by referance
;returns: none
;preconditions: none
;registers changed edx,ebp
; ***************************************************************
intro	PROC
	push ebp
	mov	ebp,esp
	mov	edx,[ebp+12]
	call WriteString
	mov	edx, [ebp+8]
	call WriteString
	call Crlf
	pop	ebp
	ret	8
intro	ENDP

; ****************** get data from user *************************
;des: prompt and get an integer from the user
;receives: beep, error, prompt1, number by referance
;returns: number is stored
;preconditions: none
;registers changed edx, eax, ebp
; ***************************************************************
getData	PROC
	push	ebp
	mov	ebp,esp

prompt:
	mov	edx,[ebp+12]
	call Crlf
	call WriteString		;prompt user
	call ReadInt			;get user's number

	cmp eax, MINSIZE
	jl printErr
	cmp eax, MAXSIZE
	jg printErr
	jmp store

printErr:
	mov edx, [ebp+16]
	call writeString
	mov edx, [ebp+20]
	call WriteString
	call CrLf
	jmp prompt
store:
	mov	ebx,[ebp+8]			;address of count in ebx
	mov	[ebx],eax			;store in global variable
	call Crlf
	pop	ebp
	ret	16
getData	ENDP

; ****************** Fill array with random ints ****************
;des: fills the array with random integers in the range of 100 -
; 999
;receives:array, arrSize by referance, number by value
;returns: array is filled with random numbers
;preconditions: none
;registers changed edx, ecx, edi, eax, ebp
; ***************************************************************
fillArray	PROC
	push	ebp
	mov	ebp,esp
	mov	ecx,[ebp+8]			;loop counter = number
	mov	edi,[ebp+16]		;addr of array in edi
	xor ebx, ebx
	
fill:
	mov eax,hi				;random int code used in lecture
	sub eax,lo
	inc eax
	call RandomRange
	add eax, lo
	mov [edi], eax			;add random to array
	add edi, 4
	inc ebx
	loop fill

	mov ecx, [ebp+12]
	mov [ecx], ebx			;store arraySize
	pop	ebp
	ret	12
fillArray	ENDP

; ****************** Print the array ****************************
;des: print the array out
;receives: array, arrSize by referance
;returns: print to screen
;preconditions: none
;registers changed edx, eax, ebp, ebx, ecx
; ***************************************************************
printList	PROC
	push	ebp
	mov	ebp,esp
	mov	ecx,[ebp+8]		;array size in edx
	mov	edi,[ebp+12]	;address of array in esi

	mov edx,[ebp+20]
	call writeString
	call Crlf

	xor edx, edx
	dec	edx				;array starts a 0 so -1 for size
	mov ebx, 0


more:
	mov eax, [edi]
	call writeDec
	add edi, 4
	inc ebx
	mov edx, [ebp+16]	;print spaces
	call writeString
	cmp ebx, 10
	jge	jump
	loop more

	jmp getout
jump:
	call CrLf
	mov ebx, 0
	loop more
getout:
	call	crlf
	call	Crlf
	pop	ebp
	ret	12
printList	ENDP

; ******************* Sort the Array ****************************
;des: Sorts the array in decending order
;receives: array and array size by referance
;returns: sorted array
;preconditions: none
;registers changed edx, eax, ebp, ecx, edi, ebx
; ***************************************************************
sortList	PROC
	push	ebp
	mov	ebp,esp
	mov	ecx,[ebp+8]		;array size in edx
	mov	edi,[ebp+12]	;address of array in esi

	pushad
	push edi			;push array
	push ecx			;push array size
	call buildHeap
	popad

	;run heap sort from exc, to 0 
again:
	dec ecx
	mov ebx, [edi]	;val at array[0]
	mov edx, [edi+ecx*4]
	mov [edi], edx	;swap indo array[0]

	mov eax, 4		;swap array[ecx]
	mul ecx
	mov edx, edi
	add edx, eax
	mov [edx], ebx

	pushad
	push edi
	push ecx		;send ecx as heap sort max index
	push 0			;send 0 as heap sort min index
	call adjustHeap
	popad
	cmp ecx, 0
	jg again
	pop ebp
	ret 12

sortList	ENDP

; ******************* Build Heap from Array *********************
;des: Builds a minHeap from the array.  This is internal and only
; called by the sort procedure.
;receives: array and array size by referance
;returns: array is sorted in a min heap
;preconditions: none
;registers changed edx, eax, ebp, esp, ecx, ebx, edi
; ***************************************************************
buildHeap	PROC
	push	ebp
	mov	ebp,esp
	mov	ecx,[ebp+8]		;array size in edx
	mov	edi,[ebp+12]	;address of array in esi
	sub esp, 8			;two locals

	mov eax, ecx
	dec eax
	cdq
	mov ebx, 2
	div	ebx
	mov DWORD PTR [ebp-4], eax 	;last leaf node arrsize-1/2 here

	mov ebx, [ebp-4]
again:
	pushad
	push edi		;push array
	push ecx		;push sizeArray
	push ebx	;push last leaf node
	call adjustHeap
	popad
	cmp ebx, 0
	je done
	dec ebx
	jmp again
done:
	mov esp, ebp		;clean up locals
	pop ebp
	ret 8
buildHeap	ENDP

; ******************* Sort the min Heap by Swapping *************
;des: swap the root and element (i) of the heap and rebuild
; the heap from the top down. This sorts in decending order. 
;receives:  array, array size, and last leaf node by referance
;returns: array is sorted in decending order
;preconditions: none
;registers changed edx, eax, ebp, esp, edi, ebx
; ***************************************************************
adjustHeap PROC
	push	ebp
	mov	ebp,esp
	mov	ecx,[ebp+12]		;array size in edx
	mov	edi,[ebp+16]	;address of array in esi
	mov ebx, [ebp+8]	;leaf node
	sub esp, 16			;4 locals

	mov eax, 2
	mul ebx
	inc eax
	mov DWORD PTR [ebp-4], eax	;store left node value
	inc eax
	mov DWORD PTR [ebp-8], eax	;store right node value

leftORright:
	cmp eax, ecx	;is right node less than array size?
	jge left

	smallestNode:
		mov ebx, [ebp-4]	;left or right node smaller?
		mov ebx, [edi+ebx*4]; value of left node in ebx
		mov eax, [ebp-8]	
		mov eax, [edi+eax*4] ;value of node right node in eax
		cmp eax, ebx	;is right greater than left?
		jl	storeRight
		jge	storeLeft
		je	getout
	storeRight:	;store right node as smallest
		mov eax, [ebp-8]
		mov [ebp-12], eax
		jmp swap
	storeLeft:
		mov eax, [ebp-4]
		mov [ebp-12], eax
		jmp swap
	
	swap:
		;compare leaf node and min node
		mov ebx, [ebp+8]
		mov ebx, [edi+ebx*4]	;val of array at leaf node
		mov ecx, [ebp-12]
		mov ecx, [edi+ecx*4]	;val of array at minNode
		cmp ecx, ebx
		jge getout				;check of minNode is less than leaf
		;swap values in array
		mov edx, [ebp+8]		;index of leaf
		mov eax, 4
		mul edx
		mov ecx, edi
		add ecx, eax	;address of array at leaf 
		mov edx, [ebp-12]
		mov edx, [edi+edx*4]	;val of array at minNode
		mov [ecx], edx

		mov edx, [ebp-12]	;index of minNode
		mov eax, 4
		mul edx
		mov ecx, edi
		add ecx, eax	;address of array at minNode
		mov [ecx], ebx

		pushad
		push edi
		push [ebp+12]
		push [ebp-12]
		call adjustHeap ; recursive to rebuild heap in order
		popad
		jmp getout

left:
	mov eax, [ebp-4]
	cmp eax, [ebp+12]
	jge getout
	mov [ebp-12], eax ;move left to minNode
	jmp swap

getout:
	mov esp, ebp		;clean up locals
	pop ebp
	ret 12
adjustHeap ENDP
END main
 