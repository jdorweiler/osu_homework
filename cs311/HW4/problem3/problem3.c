/*
#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 4
*/
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>
#include <ar.h>
#include <dirent.h> // directory info for -A, -W see pg 352. 

#define BLOCKSIZE sizeof(char)
#define STR_SIZE sizeof("rwxrwxrwx")
#define UMASK_SETTING (S_IWOTH|S_IXGRP) // pg 302, umask for other write and group exe permission

void printTable(const char *fileName, char option);
void appendAR(int argc, char **argv, char option);
void extractAR(int argc, char **argv, int option);
//void **getDirFiles(char *curProg);
void deleteAR(int argc, char **argv);
char *getDate(time_t date);
char *filePermStr(mode_t p, int flag);

int main(int argc, char **argv){
	char option;
	while (( option = getopt(argc, argv, "q:xt:v:V:d:Aw")) != -1){
		switch(option){
			case 'q':
				// quickly append
				// if no optarg then just make a new file with <arch> tag
				appendAR(argc, argv, 'q');
				break;
			case 'x':
				// extract named members
				// extract all if none are given
				if(argv[3]){ 
					extractAR(argc, argv, 0);
				} else {
					extractAR(argc, argv, 1);
				}	
				break;
			case 't':
				// print out a table of contents
				printTable(optarg,'t');

				break;
			case 'v':
				// verbose table
				printTable(optarg,'v');
				break;
			case 'V':
				// verbose table
				printTable(optarg,'v');
				break;			
			case 'd':
				// delete named files
				deleteAR(argc, argv);
				break;
			case 'A':
				// quickly append regular files
				if(argv[3]){
					printf("Option -A does not take any members\n");
				}
				appendAR(argc, argv, 'A');
				break;
			case 'w':
				// add modified files

				break;
			}
	}

	return 0;
}

char **getDirFiles(char *curProg){
	// see pg. 356
	DIR *dirp;
	struct dirent *dp;
	struct stat fileStat;
	static char *fileList[50]; // static to not return a null pointer, 50 files
	int i = 3; // start at 3 since we

	// get current dir name and remove from argv[0]
	// to get the running program name
	//getcwd(currentDir, 255);
	//runningFile = argv[0] + strlen(currentDir)+1;
	curProg = curProg+2;
	printf("cur prog: %s\n", curProg);
	// open current dir
	if((dirp = opendir(".")) == NULL){
		perror("open dir failed \n");
		exit(EXIT_FAILURE);
	}

	for(;;){
		errno = 0;
		// from pg 353 each call to readdir reads the next
		// file entry in the stream, dirp
		if((dp = readdir(dirp)) == NULL){
			break;
		}

		// file name is in dp->d_name
		// stat to check for regular file
		stat(dp->d_name, &fileStat);
		if(S_ISREG(fileStat.st_mode) && strcmp(curProg, dp->d_name) != 0){
			fileList[i] = dp->d_name;
			i++;
			printf("Added reg file: %s\n", dp->d_name);
		}
	}
	return fileList;
}

void deleteAR(int argc, char **argv){
	char buf[BLOCKSIZE];
	char fileName[16];
	char ck_AR[SARMAG];
	int in_fd;
	int new_Arch;
	int fsize;
	int skipFlag = 0;
	struct ar_hdr record;
	struct stat oldArchive;
	int AR_SIZE = sizeof(struct ar_hdr);

	// no files to remove were entered
	if(argc < 4){
		return;
	}

	// open  archive file
	in_fd = open(argv[2], O_RDONLY);
		if(in_fd == -1){
		perror("cant open file");
		exit(EXIT_FAILURE);
	}
	// does it have the archive string? ARMAG
	// strncmp the first 7 chars to ignore newline
	lseek(in_fd, 0, SEEK_SET);
	read(in_fd, ck_AR, SARMAG);
	if(strncmp(ck_AR, ARMAG, SARMAG-1) != 0){
		perror("That doesn't look like an archive file\n");
		exit(EXIT_FAILURE);
	}

	// get stat on the archive then unlink
	stat(argv[2], &oldArchive);
	if(unlink(argv[2]) == -1){
		perror ("unlink");
		exit(EXIT_FAILURE);
	}

	// open the new archive file and write the arch header
	if((new_Arch = open(argv[2], O_CREAT | O_WRONLY | O_APPEND |O_EXCL, oldArchive.st_mode)) == -1){
		perror("Could not create new archive file\n");
		exit(EXIT_FAILURE);
	}

	// write arch tag to the new file
	write(new_Arch, ARMAG, sizeof(ARMAG)-1);
	lseek(in_fd, 0, SEEK_SET);
	lseek(in_fd, SARMAG, SEEK_CUR);

	// loop through each record in the archive copying each
	// into the new file.  If the file name matches one of 
	// the argv names then skip to the next record and do 
	// not coppy that file over. 
	while(read(in_fd, &record, AR_SIZE) != 0){
		skipFlag = 0;
		// get the file name, remove /
		int k;
		for(k = 0; k < sizeof(record.ar_name); k++){
			if(record.ar_name[k] != '/'){
				fileName[k] = record.ar_name[k];
			} else {
				break;
			}
		}

		// loop through argv 
		int i;
		for(i = 3; i < argc; i++){
			fsize = atoi(record.ar_size);
			if(strcmp(fileName, argv[i]) == 0){
				lseek(in_fd, fsize+(fsize%2), SEEK_CUR);
				skipFlag = 1;
				break; // dont copy this record over
			}
		}

		if(!skipFlag) {	 
			// write the header to new archive
			write(new_Arch, &record, sizeof(record));
			// write the data to new archive
			int j;
			for(j = 0; j < fsize*2+fsize%2; ++j){
				j += read(in_fd, buf, BLOCKSIZE);
				write(new_Arch, buf, BLOCKSIZE);
			}
		}
	}
	close(in_fd);
	close(new_Arch);
}

void extractAR(int argc, char **argv, int option){
	// read through archive
	// open file 
	char buf[BLOCKSIZE];
	char ck_AR[sizeof(ARMAG)];
	char fileName[16];
	int in_fd;
	int out_fd;
	int fsize;
	struct ar_hdr record;
	struct stat new_file;
	struct utimbuf new_file_times;
	int AR_SIZE = sizeof(struct ar_hdr);

	umask(UMASK_SETTING);

	// check for option flag, inc argc to jump into loop once
	if(option){
		argc += 1;
	}

	in_fd = open(argv[2], O_RDONLY);
		if(in_fd == -1){
		perror("cant open file");
		exit(EXIT_FAILURE);
	}
	// does it have the archive string? ARMAG
	// strncmp the first 7 chars to ignore newline
	lseek(in_fd, 0, SEEK_SET);
	read(in_fd, ck_AR, SARMAG);
	if(strncmp(ck_AR, ARMAG, SARMAG-1) != 0){
		perror("That doesn't look like an archive file\n");
		exit(EXIT_FAILURE);
	}

	// we have a file to extract
		int i;
		for(i = 3; i < argc; i++){
			lseek(in_fd, 0, SEEK_SET);
			lseek(in_fd, SARMAG, SEEK_CUR);
			// print out the ar_names for each
			while(read(in_fd, &record, AR_SIZE) != 0){
				// get the file name, remove /
				int k;
				for(k = 0; k < sizeof(record.ar_name); k++){
					if(record.ar_name[k] != '/'){
						fileName[k] = record.ar_name[k];
					} else {
						break;
					}
				}
				fsize = atoi(record.ar_size);
				if(option || strcmp(argv[i], fileName) == 0){
					// found a match, create the file with ar_mode permissions
					out_fd = open(fileName, O_CREAT | O_WRONLY | O_EXCL, strtol(record.ar_mode,NULL,8));

					// update the times on the file. 
					// get info for open file with fstat
					fstat(out_fd, &new_file);   /********************* changed this from fileName to out_fd */

					// add the times to the utimebuf 
					new_file_times.actime = atoi(record.ar_date);
					new_file_times.modtime = atoi(record.ar_date);

					// update the file times with utime
					utime(fileName, &new_file_times);

					// write the file
					int j;
					for(j = 0; j < fsize*2+fsize%2; ++j){
						j += read(in_fd, buf, BLOCKSIZE);
						write(out_fd, buf, BLOCKSIZE);
					}
					close(out_fd);
				} else {
					lseek(in_fd, fsize+(fsize%2), SEEK_CUR);
				}
			}
			if(option){ break;}
		}
		close(in_fd);
}

// I found some helpful code on the format for sprintf 
// here: https://stackoverflow.com/questions/14656026/using-fwrite-to-store-an-ar-hdr-struct-to-a-file
void appendAR(int argc,char **argv, char option){
	struct stat sb;
	struct ar_hdr head;
	char buf[BLOCKSIZE];
	char fileName[64];
	char **fileList;
	char *argvFile;
	int fname;
	int fd, in_fd;

	// check for A option to all all regular files
	if(option == 'A'){
		// add all regular files to argv 
		fileList = getDirFiles(argv[0]);
		argc = sizeof(argv)+3;
	} else {
		fileList = argv;
	}

	// option W use popen to run append
	// open for appending
	// check to see if open failed
	if((fd = open(argv[2], O_APPEND | O_WRONLY)) == -1){
		if(ENOENT){ // check ENOENT flag
			// create file
			fd = open(argv[2], O_CREAT | O_APPEND | O_WRONLY, 00666);
			write(fd, ARMAG, sizeof(ARMAG)-1);
		} else {
			perror("cant open/create file");
			exit(EXIT_FAILURE);	
		}	
	}
		int i;
		for(i = 3; i < argc; i++){
			//get stat info on file
			strncpy(fileName, fileList[i], 64);
			fname = stat(fileList[i], &sb);
			if(fname != -1){
				//open file and write data to the archive file
				if((in_fd = open(fileList[i], O_RDONLY)) == -1){
					printf("Cant read file: %s\n", argv[i]);
					break;
				}

				// we have a stat on the file, add the data
				// to the ar_hdr struct.
				// see top of function for note about this format. 
				//fileName = *argv[i];
				sprintf(&head,"%-16s%-12ld%-6ld%-6ld%-8o%-10lld%c%c", strcat(fileName, "/"),
					sb.st_mtime, sb.st_uid, sb.st_gid, sb.st_mode, sb.st_size,0x60,0xa);
				write(fd, &head, sizeof(head));

				int j;
				for(j = 0; j < (int)(sb.st_size*2+sb.st_size%2); ++j){
					j += read(in_fd, buf, BLOCKSIZE);
					write(fd, buf, BLOCKSIZE);
				}
			} else {
				printf("Can't add file named: %s\n", argv[i]);
			}
	}
}

void printTable(const char *fileName, char option){
	// open file 
	char output[BLOCKSIZE];
	char ck_AR[sizeof(ARMAG)];
	int in_fd;
	int fsize;
	struct ar_hdr record;
	int AR_SIZE = sizeof(struct ar_hdr);

	in_fd = open(fileName, O_RDONLY);
		if(in_fd == -1){
		perror("cant open file");
		exit(EXIT_FAILURE);
	}
	// does it have the archive string? ARMAG
	// strncmp the first 7 chars to ignore newline
	printf("opening file and checking\n");
	lseek(in_fd, 0, SEEK_SET);
	read(in_fd, ck_AR, SARMAG);
	if(strncmp(ck_AR, ARMAG, SARMAG-1) != 0){
		perror("That doesn't look like an archive file\n");
		exit(EXIT_FAILURE);
	}

	// print out the ar_names for each
	while(read(in_fd, &record, AR_SIZE) != 0){
		// small table
		if(option == 't'){
			int i;
			for(i = 0; i < sizeof(record.ar_name); i++){
				if(record.ar_name[i] != '/'){
					printf("%c", record.ar_name[i]);
				} else {
					printf("\n");
					break;
				}
			}
			fsize = atoi(record.ar_size);
			lseek(in_fd, fsize+(fsize%2), SEEK_CUR);
		}
		// verbose table
		if(option == 'v'){
			// print out in the form;
			// rw-rw-r-- 1000/1000     41 Apr 16 08:51 2014 1-s.txt

			// print permission
			// this needs to be unsigned long int pg. 284. TLPI
			// http://www.cplusplus.com/reference/cstdlib/strtol/
			mode_t filePerm = strtol(record.ar_mode, NULL, 8); 
			printf("%s ", filePermStr(filePerm, 0));

			// print user/group
			printf("%d/%d", atoi(record.ar_uid), atoi(record.ar_gid));

			// print filesize
			printf("%7d ", atoi(record.ar_size));

			// print date
			time_t fileTime = atoi(record.ar_date);
			printf("%s ", getDate(fileTime));

			//print file name
			int i;
			for(i = 0; i < sizeof(record.ar_name); i++){
				if(record.ar_name[i] != '/'){
					printf("%c", record.ar_name[i]);
				} else {
					printf("\n");
					break;
				}
			}
			fsize = atoi(record.ar_size);
			lseek(in_fd, fsize+(fsize%2), SEEK_CUR);
		}
	}	
}

// turn a time_t into time string for printing
char *getDate(time_t date){
	char time_string[100];
	struct tm *printTime;
	printTime = localtime(&date);
	// month day time(H:M) year see pg 194 TLPI
	strftime(time_string, 100, "%b %e %R %Y", printTime);
	return time_string;
}

// from pg 296 TLPI converting permission mask to string
char *filePermStr(mode_t p, int flags){
	// set this to zero for now
	int FP_SPECIAL = 0;
 	static char str[STR_SIZE];
	snprintf(str, STR_SIZE, "%c%c%c%c%c%c%c%c%c",
	(p & S_IRUSR) ? 'r' : '-', (p & S_IWUSR) ? 'w' : '-',
	(p & S_IXUSR) ?
		(((p & S_ISUID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
		(((p & S_ISUID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
	(p & S_IRGRP) ? 'r' : '-', (p & S_IWGRP) ? 'w' : '-',
	(p & S_IXGRP) ?
		(((p & S_ISGID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
		(((p & S_ISGID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
	(p & S_IROTH) ? 'r' : '-', (p & S_IWOTH) ? 'w' : '-',
	(p & S_IXOTH) ?
		(((p & S_ISVTX) && (flags & FP_SPECIAL)) ? 't' : 'x') :
		(((p & S_ISVTX) && (flags & FP_SPECIAL)) ? 'T' : '-'));
return str;
}
