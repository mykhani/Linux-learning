#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	pid_t pid, groupid, session_id;

	pid = getpid();
 	groupid = getpgid(pid);
	session_id =  getsid(pid);

	printf("process 1 with PID: %d, Group ID: %d, Session ID: %d \n", pid, groupid, session_id);
	return 0;
}
