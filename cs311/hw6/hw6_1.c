#define _BSD_SOURCE

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void *mount_shmem(char *path, int object_size){
	int shmem_fd;
	void *addr;

	shmem_fd = shm_open(path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

	if(shmem_fd == -1){
		printf( "Failed to open shared memory object");
		exit(EXIT_FAILURE);
	}

	if(ftruncate(shmem_fd, object_size) == -1){
		printf( "failed to resize shared memory object");
	}

	addr = mmap(NULL, object_size, PROT_READ | PROT_WRITE, MAP_SHARED,
				shmem_fd, 0);

	if(addr == MAP_FAILED){
		printf( "Failed to map shared memory object");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv){

	unsigned char *bitmap;
	int bitmap_size = 340000000 / 8 + 1;

	int *perfect_numbers;
	int perfect_number_count = 10;

	int object_size = 1024 * 1024 * 6;

	void *addr = mount_shmem("/jd", object_size);
	printf("addr %x", addr);

	bitmap = (unsigned char*)addr;
	perfect_numbers = (int*)(bitmap + bitmap_size);

	perfect_numbers[0] = 6;

	printf( "%d\n", perfect_numbers[0]);

	return 0;
}