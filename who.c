#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

/*
 * man who
 * man -k utmp 
 * man 5 utmp 
 * 头文件内容在man 5 utmp中可以看到
 * */

voie show_info(struct utmp *utbuf);
void show_time(time_t);

int main(int argc, char* argv[]) {
    int fd = open(UTMP_FILE, O_RDONLY);
    if(fd == -1) {
        perror(UTMP_FILE);
        exit(1);
    }
    struct utmp cur_record;
    int len = sizeof(cur_record);
    while(read(fd, &cur_record, len) == len)
        show_info(&cur_record);
    close(fd);
	return 0;
}

void show_info(struct utmp *utbuf) {
    if(utbuf->ut_type != USER_PROCESS)
        return 0;
    printf("%-8.8s", utbuf->ut_user);
    printf(" ");
    printf("%-8.8s", utbuf->ut_line);
    printf(" ");
    time_t time = (utbuf->ut_tv).tv_sec;
    show_time(time);
    printf("\n");
    return 0;
}

void show_time(time_t tm) {
    char *cp;
    cp = ctime(&tm);
    printf("%20.20s", cp);
}
