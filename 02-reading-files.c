#include <assert.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    assert(argc>=2);
    const char *filepath = argv[1];

    int fd = open(filepath, O_RDONLY);
    assert(fd>=0);

    struct stat statbuff;
    int err = fstat(fd, &statbuff);
    assert(err>=0);

    int *ptr = mmap(NULL, statbuff.st_size, PROT_READ, MAP_PRIVATE , fd, 0);
    assert(ptr!= MAP_FAILED);
    close(fd);

    // 1 is writing to stdout
    ssize_t n = write(1, ptr, statbuff.st_size);
    assert(n == statbuff.st_size);

    int unmap_err = munmap(ptr, statbuff.st_size);
    assert(unmap_err>=0);

    printf("hello world..");
    return 0;
}
