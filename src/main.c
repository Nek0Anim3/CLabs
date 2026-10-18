#include <stdio.h>
#include <math.h>  
#include <stdlib.h>
 
void Calculations(int *a, int *b, float *c) {
    int sum = (*a) + (*b) + (*c);
    int exp = (*a) * (*b) * (*c);
    float cosRes = cosf(sum); 
 
    *a = sum;
    *b = exp;
    *c = cosRes;
    return;
}
 
int SumOfDigits(int n) {
    n = abs(n);
    
    if (n < 10) {
        return n;
    }
    return (n % 10) + SumOfDigits(n / 10);
}
 
#pragma region PRINT_ARRAY
 
void PrintArrayF(float *first, size_t arrSize) {
    printf("Елементи масиву: [");
    for (int i = 0; i < arrSize / sizeof(*first); i++) {
        printf("%.2f, ", *(first + i)); 
    }
    printf("]\n");
 
}
 
void PrintArrayI(int *first, size_t arrLength) {
        printf("==== Елементи масиву ====\n");
    for (int i = 0; i < arrLength; i++) {
        printf("[%d] || %d | Адреса: %p\n", i, *(first + i), (void *)(first + i));
    }
    printf("\n");
}
#pragma endregion
 
int main(void) {
    //змінні
    const int VARIANT_NUMBER = 9;
    int groupNum = 79;
    int varNum = VARIANT_NUMBER;
    float crsNum = 4.0;
    
    //Завдання 1
    printf("Група: %d, Варіант: %d, Курс: %.0f\n", groupNum, varNum, crsNum);
    
    Calculations(&groupNum, &varNum, &crsNum);
 
    printf("(Нові значення) Група: %d, Варіант: %d, Курс: %.4f\n", groupNum, varNum, crsNum);
 
 
    //завдання 2
    int n = -4508;
    int res = SumOfDigits(n);
    printf("%d | Сума %d\n", n, res);
 
    //завдання 3
    float arr[] = {1, 2, groupNum, varNum, crsNum};
 
    PrintArrayF(&arr[0], sizeof(arr));
 
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
        arr[i] += VARIANT_NUMBER;
    }
 
    PrintArrayF(&arr[0], sizeof(arr));
 
    
    //завдання 4
    size_t arrSize = 0;
 
    const int MAX_NUM = 99;
    const int MIN_NUM = 10;
 
    while (1) {
        printf("Введіть розмір масиву (1 - 99): ");
        scanf("%zu", &arrSize);
        printf("\n");
 
        if (arrSize < 1 || arrSize > MAX_NUM) {
            printf("Невірний розмір масиву, спробуйте ще раз.\n");
            continue;
        }
        else {
            break;
        }
    }
 
    int arr2[arrSize];
    int *arrPtr = &arr2[0];
    
    for (int i = 0; i < arrSize; ++i) {
        int num = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
        *arrPtr = num;
        arrPtr++;
    }

    PrintArrayI(&arr2[0], arrSize);


    arrPtr = &arr2[0];
    int *minPtr = &arr2[0];
    int *maxPtr = &arr2[0];
	
	
    for (int i = 0; i < arrSize; ++i) {
      if (*arrPtr > *maxPtr) {
        maxPtr = arrPtr;
	  }
      if (*arrPtr < *minPtr) {
		  minPtr = arrPtr;
      }
	  arrPtr++;
    }
	
	printf("==== Мінімальне / Максимальне ====\n");
	printf("Max || %d | Адреса: %p\nMin || %d | Адреса: %p\n", *maxPtr, (void *)maxPtr, *minPtr, (void *)minPtr);

    printf("\n==== Після зміни місцями ====\n");

    int tempVal = 0;
	tempVal = *minPtr;
    *minPtr = *maxPtr;
	*maxPtr = tempVal;


	
	
    PrintArrayI(&arr2[0], arrSize);

	
    return 0;
}
