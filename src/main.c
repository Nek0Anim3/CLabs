#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <unistd.h>

void printVersion() {
    printf("PWD1 1.0.0\nАвтор Кузеванов Костянтин\n=)\n");
}

void printHelp() {
    printf("Використання pwd1 [-h -v -L -P]\n================\nПрапори:\n-L --logical | Логiчний шлях до директорii\n-P --physical | Фiзичний шлях до директорii\n-h --help | Допомога\n-v --version | Версiя продукту\n");
}

void printPath(bool isPhysical, char *buf, size_t bufSize) {
      char *lPath = getenv("PWD");
      if (lPath != NULL && isPhysical == false) {
          printf("%s\n", lPath);
          return;
      }
    
      getcwd(buf, bufSize);
      printf("%s\n", buf);
}

int main(int argc, char *argv[]) {
    int opt = 0;
    char printbuffer[1024];
    
    
    const char *shortOpts = "vhLP";
    const struct option longOpts[] = {
        {"version", no_argument, NULL, 'v'},
        {"help", no_argument, NULL, 'h'},
        {"logical", no_argument, NULL, 'L'},
        {"physical", no_argument, NULL, 'P'}
    };
    while ((opt = getopt_long(argc, argv, shortOpts, longOpts, NULL)) != -1) {
        switch (opt)
        {
        case 'v':
            printVersion();
            break;
        case 'h':
            printHelp();
            break;
        case 'L':
            printPath(false, printbuffer, sizeof(printbuffer));
            break;
        case 'P':
            printPath(true, printbuffer, sizeof(printbuffer));
            break;
        default:
            printHelp();
            break;
        }
        break;
    }
    //якщо без аргументу
    if (opt == -1) {
        printPath(false, printbuffer, sizeof(printbuffer));
    }
    return 0;
}
