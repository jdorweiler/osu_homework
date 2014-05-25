import os, sys
import subprocess
import pipes

def main():

	process1 = subprocess.Popen(["rev"], stdout=subprocess.PIPE)
	process2 = subprocess.Popen(["sort"], stdin=process1.stdout, stdout=subprocess.PIPE)
	process3 = subprocess.Popen(["uniq", "-c"], stdin=process2.stdout, stdout=subprocess.PIPE)
	process4 = subprocess.Popen(["wc"], stdin=process3.stdout)
	stdout, stderr = process4.communicate()

if __name__ == '__main__':
	main()