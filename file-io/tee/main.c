#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h> // for S_IRUSR, S_IWUSR i.e. for file permission flags for file i/o
#include <fcntl.h> // for file mode flags O_CREAT etc

/*
 * An implementation of UNIX tee command
 * Take input from stdin
 * Show a copy of input on the stdout
 * Create a copy of the input into a new file
 */

/*
 * Already opened file descriptors
 * STDIN_FILENO : stdin
 * STDOUT_FILENO : stdout
 * STDERR_FILENO : stderr
 */
 
 // set opterr to 1 to suppress getopt() parsing errors
extern int optind, opterr, optopt;
extern char *optarg;

int main(int argc, char **argv)
{
    char byte;
    int append = 0; // get as -a arg in command line
    int opt;
    char *filename = "default.log"; // get from cmdline argument
    int mode = O_WRONLY | O_CREAT;
    int perm = S_IRUSR | S_IWUSR;
    
    while((opt = getopt(argc, argv, "a")) != -1) {
        if (opt == '?' || opt == ':') {
            printf("Unknow arg or missing value for arg -%c\n", optopt);
        }
        
        switch(opt) {
        case 'a':
            append = 1;
            break;
        }
        
    } 
    
    if (argv[optind] == NULL) {
        printf("Filename not specified, using the default filename: %s\n", filename);
    } else {
        filename = argv[optind];
    }
    
    int fd;
    
    fd = open(filename, mode | (append ? O_APPEND: O_TRUNC), perm);
    if (fd < 0) {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }
    
    printf("File: \"%s\" opened in %s mode\n", filename, append ? "append": "truncate");
    
    /* read stdin till EOF */
    while(read(STDIN_FILENO, &byte, 1) != 0) {
        // show on output
        write(STDOUT_FILENO, &byte, 1);
    // write to file
        write(fd, &byte, 1);
    }
    
    close(fd);
    
    return 0;
}
