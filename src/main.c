#include <stdio.h>
#include <math.h>
#include <string.h>
#define PI 3.14

int group_number = 79;
int variant_number = 9;// Мій номер за журналом

void checkSqrt(int groupNum, int nameLen) {
    double root = sqrt(groupNum);
    int truncRoot = (int) root;
    if (truncRoot > nameLen) {
        printf("Сума: %.2fs\n", (root + (double) nameLen));
        return;
    }
    else if (truncRoot == nameLen) {
        printf("Корінь: %.2f, Довжина імені: %d\n", root, nameLen);
        return;
    }
    else if (truncRoot < nameLen) {
        printf("Добуток: %.2fn\n", (root * (double) nameLen));
        return;
    }
}  

int main(void) {
    float fsin = cosf(variant_number);

    char name[] = "Костянтин";
    const int NAME_NUMBER = 9;

    printf("Мій номер за журналом: %d, його косинус = %.4f\n", variant_number, fsin);
    printf("Група %d, варіант %d, ім'я %s\n", group_number, variant_number, name);

    double exp = PI * variant_number;

    printf("Добуток = %.2f, Конвертоване = %d\n", exp, (int) exp);

    
    //цикл
    int sum = 0; 
    for (int i = (NAME_NUMBER + variant_number); i > 0; --i) {
        sum += i;
    }
    printf("Кількість літер імені: %d\nНомер за журналом: %d\nСума чисел: %d\n", NAME_NUMBER, variant_number, sum);

    int nameLength = (int) strlen(name);
    checkSqrt(group_number, nameLength);

    //switch
    int groupNumber = 0;
    printf("Введіть номер групи: ");
    scanf("%d", &groupNumber);

    switch (groupNumber)
    {
    case 75 ... 80:
        printf("IV Курс\n");
        break;
    case 81 ... 86:
        printf("III курс\n");
        break;
    case 87 ... 91:
        printf("II курс\n");
        break;
    case 92 ... 99:
        printf("I курс\n");
        break;
    default:
        printf("Немає такої групи\n");
        break;
    }
    return 0;
}