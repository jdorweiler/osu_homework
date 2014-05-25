import subprocess
import shlex
import os
import sys
import stat
import time

def ls_sp():
	command = 'ls -latrn'
	command_seq = shlex.split(command)

	ls = subprocess.Popen(command_seq, stdout=subprocess.PIPE)
	ls_out = ls.stdout.readlines()

	for line in ls_out:
		print line,

if __name__ == '__main__':
	ls_sp()
