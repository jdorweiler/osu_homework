import sys
import math

def main():
	unSorted = [1,3,2,5,3,6,4,3,6,3,34,2,3,43,24,13,98,45]
	sortedArr =  mergeSort(unSorted)
	print sortedArr

def mergeSort(array):
	mid = len(array)/2
	if(len(array) == 1):
		return array
	else:
		left = mergeSort(array[:mid])
		right = mergeSort(array[mid:])
	result = merge(left,right)
	return result

def merge(left, right):
	print "Left: ", left
	print "Right: ",  right
	if(len(left) == 0):
		return right
	if(len(right) == 0):
		return left

	if(left[0] < right[0]):
		return left[0], merge(left[1:], right)
	else:
		return right[0], merge(left, right[1:])


if __name__ == '__main__':
	main()