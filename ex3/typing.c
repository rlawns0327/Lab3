/*
typing.c
몇 개의 문장을 타자하도록 하여 잘못 타이핑한 횟수와 평균 분당 타자수를 
측정하는 타자 연습 프로그램을 구현하여 보시오
*/
#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define CONTENTS_COUNT 2
int main(void)
{
	int fd;
	int nread, cnt=0, right_cnt=0, wrong_cnt=0;
	int total_time=0;
	char ch;
	char* text[CONTENTS_COUNT] = {"this is typing test contents", "abcdefghijklmnop"};
	time_t time_start, time_end;
	struct termios init_attr, new_attr;
	
	fd = open(ttyname(fileno(stdin)), O_RDWR);
	tcgetattr(fd, &init_attr);
	new_attr = init_attr;
	new_attr.c_lflag &= ~ICANON;
	new_attr.c_lflag &= ~ECHO;/* ~(ECHO | ECHOE | ECHOK | ECHONL); */
	new_attr.c_cc[VMIN] = 1;
	new_attr.c_cc[VTIME] = 0;
	
	if (tcsetattr(fd, TCSANOW, &new_attr) != 0) {
		fprintf(stderr, "터미널 속성을 설정할 수 없음.\n");
	}
	printf("다음 문장을 그대로 입력하세요.\n");
	time_start=time(NULL);
	
	for(int i=0; i<CONTENTS_COUNT; i++){
		cnt = 0;
		printf("%s\n", text[i]);

		while ((nread=read(fd, &ch, 1)) > 0 && ch != '\n') {
			if (ch == text[i][cnt++]){
				write(fd, &ch, 1);
				right_cnt++;
			}
			else {
				write(fd, "*", 1);
				wrong_cnt++;
			}
		}
		printf("\n");
	
	}
	time_end=time(NULL);
	
	total_time = (int)(time_end-time_start);
	
	printf("\n총 시간 : %d초\n", total_time);
	printf("분당 타자수 : %.1f\n", (float)((60*right_cnt)/total_time));
	printf("총 글자수 : %d\n", wrong_cnt+right_cnt);
	printf("오타 수 : %d\n", wrong_cnt);
	printf("올바른 글자 수 : %d\n", right_cnt);
	
	tcsetattr(fd, TCSANOW, &init_attr); close(fd);
	
return 0;
}

