from math import floor
import sys
import numpy as np
def main(x):
	array = [1,2,3,4,5,6,7,8,9]
	binarySearch(array, int(x))

def binarySearch(array, val):
	mid = int(floor(len(array)/2))

	if(array[mid] == val):
		print "Found value"
		return

	#handle base case
	if (mid == 1):
		if(array[0] == val):
			print "Found value"
			return
		else:
			print "did not find value"
			return

	#split array and recursive call
	if(val > array[mid]):
		return binarySearch(array[mid+1:], val)
	elif(val < array[mid]):
		return binarySearch(array[:mid-1], val)


if __name__ == '__main__':
	main(sys.argv[1])