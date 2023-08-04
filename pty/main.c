#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h> /* For toupper */
#define __USE_GNU /* For ptsname_r */
#include <stdlib.h>
#include <signal.h> /* For catchng Crtl+C */

static volatile int keep_running = 1;

void int_handler()
{
       keep_running = 0;
}

int main(int argc, char* argv[])
{
	char slave_path[256];
	int bytes_read = 0;
	int bytes_written = 0;
	int ret = -1;

	int ptm = open("/dev/ptmx", O_RDWR);
	if (ptm < 0) {
		perror("Failed to open pseudoterminal master-slave pair");
		return -1;
	}
	printf("Handle for master end: %d\n", ptm);

	ret = ptsname_r(ptm, slave_path, sizeof(slave_path));
	if (ret) {
		perror("Failed to find the slave path");
		goto end;
	}

	printf("Slave path: %s\n", slave_path);

	grantpt(ptm);
	unlockpt(ptm);

	/* catch Ctrl+c */
	signal(SIGINT, int_handler);

	char c;

	while(keep_running) {
		bytes_read = read(ptm, &c, 1);
		if (bytes_read < 0) {
			perror("Failed to read from master end\n");
			goto end;
		}
		printf("Read %d bytes\n", bytes_read);
		printf("Byte: %c\n", c);
		c = toupper(c);

		bytes_written = write(ptm, &c, 1);
		if (bytes_written < bytes_read) {
			perror("Failed to write bytes\n");
			goto end;
		
		}
	}
end:
	printf("Exiting...");
	close(ptm);
	return ret;
}
