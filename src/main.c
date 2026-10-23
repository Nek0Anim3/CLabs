#include <stdio.h>
#include <stdlib.h>
int main(void) {
	size_t arrSize = 3;
    int *arr = (int *)malloc(arrSize * sizeof(int));

    for (int i = 0; i < arrSize ; ++i) {
		arr[i] = i * 10; // заповнення
    }


    // print

	printf("Стек змінна: %p\nВказівник: %p\nБлок масиву (1й елемент): %p\n", &arrSize, &arr, arr);

    size_t newSize = arrSize + 2;
    int *temp = (int *)realloc(arr, newSize * sizeof(int));

    if (temp == NULL) {
      free(arr);
	  return 1;
    }


	
    arr = temp;
    arrSize = newSize;

	printf("Масив вказівник адреса: %p\n", arr);
    free(arr);
    arr = NULL;

	
	return 0;
}