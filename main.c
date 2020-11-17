#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int rando() {
    int fd = open("/dev/random", O_RDONLY);
    int *buff;
    int x = 0;
    if (fd == -1){
        printf("Open /dev/random failure: %d  MSG: %s\n", errno, strerror(errno));
        return -1;
    }

    x = read(fd, buff, sizeof(buff));
    if (x == -1){
        printf("Read /dev/random failure: %d  MSG: %s\n", errno, strerror(errno));
    }
    close(fd);
    return *buff;
}


int main() {
    int x[10];
    int i;
    printf("Generating random numbers:\n");
    for(i = 0; i<10; i++){
        x[i] = rando();
        printf("\trandom %d: %d\n",i,x[i]);
    }
    printf("\nWriting numbers to file...\n\n");

    int copy = open("copy.txt", O_CREAT | O_WRONLY, 0664);
    if (copy == -1){
        printf("Open copy.txt failure: %d  MSG: %s\n", errno, strerror(errno));
        return -1;
    }
    int w = write(copy, x, sizeof(x));
    if (w == -1){
        printf("Write copy failure: %d  MSG: %s\n", errno, strerror(errno));
        return -1;
    }
    
    printf("Reading numbers from file...\n\n");
    int n[10];
    int cpyrd = open("copy.txt", O_RDONLY);
    if (cpyrd == -1){
        printf("fsOpen copy.txt failed: %d  MSG: %s\n", errno, strerror(errno));
        return -1;
    }
    int r = read(cpyrd, n, sizeof(n));
    
    if (r == -1) {
        printf("Read copy.txt failure: %d  MSG: %s\n", errno, strerror(errno));
        return -1;
    }

    printf("Verification that written values were the same:\n");
    for(i = 0; i<10; i++){
        printf("\trandom %d: %d\n",i,n[i]);
    }

    close(copy);
    close(cpyrd);
}