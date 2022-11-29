/* 
file_list.c
주어진 디렉토리 내에 존재하는 파일과 디렉토리를 나열하고, 디렉토리의 경우
재귀적으로 방문해서 그 디렉토리 내에 존재하는 파일과 디렉토리를 나열하는 프로그램을 작성하시오. 
즉, “ls –R” 명령과 동일한 결과를 보이도록 하시오. 
*/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

void fatal(char *error)
{
	perror(error);
	exit(1);
}

void printDirectory(DIR *dir, char *file)
{
	DIR *directory_file;
	char buff[1024];
	struct dirent *directory;
	struct stat statFile;
	void fatal(char *);
	while(directory = readdir(dir))
	{
		if(!strncmp(directory->d_name, ".", 1) || !strcmp(directory->d_name, ".."))
			continue;
		if(directory->d_ino == 0)
			continue;
		
		sprintf(buff, "%s/%s", file, directory->d_name);
		puts(buff);
		
		if(lstat(buff, &statFile) < 0)
			fatal("stat");
		if(S_ISDIR(statFile.st_mode))
		{
			printf("directory ");
			directory_file = opendir(buff);
			printDirectory(directory_file, buff);
		}
	}
	closedir(dir);
}



int main(int argc, char *argv[])
{
	void printDirectory(DIR *, char *);
	void fatal(char *);
	DIR *dir;
	char file[1024];
	struct dirent *directory;

	if(argc == 1)
	{
		strcpy(file, ".");
	}
	else
		strcpy(file, argv[1]);

	if((dir = opendir(file)) == NULL)
	{
		fatal("opendir");
	}
	printDirectory(dir, file);
}
