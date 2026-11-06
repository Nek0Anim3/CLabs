#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <execinfo.h>


volatile sig_atomic_t keepRunning = 1;

void sigquitExit(int sig) {
     void *buf[5];
     int ptrs;
     char **strings;

     ptrs = backtrace(buf, 5);
     strings = backtrace_symbols(buf, ptrs);
     printf("====== Stack Trace (SIGQUIT) ======\n");
     for (int i = 0; i < ptrs; ++i) {
          printf("%d    %s\n", i, strings[i]);
     }
     keepRunning = 0;
}

int main() {
     signal(SIGQUIT,sigquitExit);
 
     int pid = getpid();
     printf("Програму запущено. PID: %d\n", pid);
     printf("Виклик з iншого термiналу\n   kill -3 %d\n", pid);
     printf("\n\nОчiкування виходу... Ctrl + \\ \n");
     while (keepRunning) {
          sleep(1);
     }
     return 0;
}

