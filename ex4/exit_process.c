// exit_process.c

#include <stdlib.h>
#include <stdio.h>
int main()
{
	int exit_status;
	
	printf("enter exit status: ");
	scanf("%d", &exit_status);
	
	exit(exit_status);
	
return 0;
}
