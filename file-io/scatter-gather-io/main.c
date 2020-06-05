#include <unistd.h>
#include <sys/uio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

int test_gather()
{
    char *str1 = "First line";
    char *str2 = "Second line";
    char *str3 = "Third line";
    
    int fd = open("test_gather.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    
    struct iovec vec[3];
    ssize_t bytes_size;
    
    vec[0].iov_base = str1;
    vec[0].iov_len = strlen(str1);
    bytes_size += vec[0].iov_len;
    
    vec[1].iov_base = str2;
    vec[1].iov_len = strlen(str2);
    bytes_size += vec[1].iov_len;
    
    vec[2].iov_base = str3;
    vec[2].iov_len = strlen(str3);
    bytes_size += vec[2].iov_len;
    
    ssize_t vec_size = sizeof(vec) / sizeof(struct iovec);
    
    ssize_t written = writev(fd, vec, vec_size);
    printf("Written bytes: %lu\n", written);
    
    if (written < bytes_size) {
        printf("Failed to write scatter data\n");
        //return EXIT_FAILURE;
    }
    
    close(fd);
    
    return EXIT_SUCCESS;
}

int test_scatter()
{
    struct iovec vec[3];
    
    char buf1[20];
    char buf2[20];
    char buf3[20];
    
    int fd = open("test_scatter.txt", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file\n");
        return EXIT_FAILURE;
    }
    
    ssize_t bytes_required = 0;
    
    vec[0].iov_base = buf1;
    vec[0].iov_len = sizeof(buf1);
    bytes_required += vec[0].iov_len;
    
    vec[1].iov_base = buf2;
    vec[1].iov_len = sizeof(buf2);
    bytes_required += vec[1].iov_len;
    
    vec[2].iov_base = buf3;
    vec[2].iov_len = sizeof(buf3);
    bytes_required += vec[2].iov_len;
    
    ssize_t vec_size = sizeof(vec) / sizeof(struct iovec);
    ssize_t bytes_read;
    
    bytes_read = readv(fd, vec, vec_size);
    if (bytes_read < bytes_required) {
        printf("Warning: failed to read the required number of bytes\n");
        //return EXIT_FAILURE;
    }
    
    close(fd);
    
    // add '\0' to complete strings
    char *cptr;
    
    cptr = (char *)vec[0].iov_base; 
    cptr[vec[0].iov_len - 1] = '\0';
    
    cptr = (char *)vec[1].iov_base; 
    cptr[vec[1].iov_len - 1] = '\0';
    
    cptr = (char *)vec[2].iov_base; 
    cptr[vec[2].iov_len - 1] = '\0';
    
    printf("%s\n", (char *)(vec[0].iov_base));
    printf("%s\n", (char *)(vec[1].iov_base));
    printf("%s\n", (char *)(vec[2].iov_base));
    
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    // gather data from  multiple buffers and store them into a contiguous memory
    test_gather();
    
    // test scatter
    test_scatter();
    
    return 0;
}
