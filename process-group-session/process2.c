#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char *line;
	size_t len = 1024;

	int ret;

	line = malloc(sizeof(char) * len);

	pid_t pid, groupid, session_id;

	pid = getpid();
 	groupid = getpgid(pid);
	session_id =  getsid(pid);

	ret = getline(&line, &len, stdin);
	if (ret == -1) {
		printf("Failed to read input \n");
		return -1;
	} 	

	printf("%s", line);
	printf("process 2 with PID: %d, Group ID: %d, Session ID:%d \n", pid, groupid, session_id);
	return 0;
}
