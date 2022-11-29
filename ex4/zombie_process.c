// zombie_process.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	
	if ((pid = fork()) < 0) {
		perror("folk");
		exit(1);
	}
	
	else if (pid == 0) /* child */
		exit(0);

	/* parent */
	sleep(4);

	system("ps -o pid,ppid,state,tty,command");
	exit(0);
	
return 0;
}
