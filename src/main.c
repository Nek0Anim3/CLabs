#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void) {
     FILE *fd = fopen("chrono.log", "a");

     time_t current_time = time(NULL);
     struct tm local_tm;

     localtime_r(&current_time, &local_tm);

     char buff[128];
     strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", &local_tm);

     fprintf(fd, "[%s] Time log!\n", buff);
     return 0;
}
