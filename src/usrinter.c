#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <execinfo.h>
#include <string.h>
typedef enum {
     LOG_INFO = 0,
     LOG_WARN = 1,
     LOG_ERR = 2
} LogLevel;

const char *getStatusStr(LogLevel level) {
     switch (level) {
         case LOG_INFO:
              return "[info]";
         case LOG_WARN:
              return  "[warn]";
         case LOG_ERR:
              return "[error]";
         default: return "[info]";
     }
}


//глобальні змінні для програми. Зроблено саме так, бо простіше викликати завантаження конфігу з SIGUSR1
LogLevel level = LOG_INFO;
int interval = 1;



void debugLog(LogLevel level, int interval) {
     printf("%s Повiдомлення системи, iнтервал %d\n", getStatusStr(level), interval);
}

void loadConfig(LogLevel *logLevel, int *interval) {
    FILE *fd;
    fd = fopen("config.txt", "r");
    if (fd == NULL) {
         printf("Помилка вiдкриття config.txt. Вiн iснує?");
         return;
    }
    int i_interval = 0;
    int i_logLevel = 0;

    if (fscanf(fd, "interval=%d level=%d", &i_interval, &i_logLevel) == 2) {
         if (!(i_logLevel < 0) || !(i_logLevel > 2)) {
              *logLevel = i_logLevel;
         }
         *interval = i_interval;
    }
    fclose(fd);
    printf("\n[LOAD CONFIG] Конфігурацію завантажено!\n\n");

}

void sigusrHandler(int sig) {
     loadConfig(&level, &interval);
}

int main() {
     signal(SIGUSR1, sigusrHandler);
     int pid = getpid();
     printf("Процес має PID: %d\nДля оновлення конфігу:  kill -USR1 %d\n", pid, pid);
     while (1) {
          debugLog(level, interval);
          sleep(interval);
     }
    
     return 0;
}
