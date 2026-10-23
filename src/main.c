#include <stdio.h>
#include <stdlib.h>
int main(void) {

	size_t arrSize = 3; // локальна змінна
    // локальна змінна (вказівник на купу)
    int *arr = (int *)malloc(arrSize * sizeof(int)); 


    for (int i = 0; i < arrSize ; ++i) {
		arr[i] = i * 10; // заповнення
    }
    // print
	printf("[STACK] Змінна arrSize: %p\n[STACK] Змінна *arr: %p\n[HEAP] Адреса масиву: %p\n", &arrSize, &arr, arr);


    size_t newSize = arrSize + 2;
    int *temp = (int *)realloc(arr, newSize * sizeof(int));

    if (temp == NULL) {
      free(arr);
	  return 1;
    }
    
    arr = temp;
    
    printf("\n\n[HEAP] Адреса після realloc(): %p\n", arr);
    for (size_t i = arrSize; i < newSize; i++)
    {
        arr[i] = 10*i;
    }
    
    arrSize = newSize;

    printf("\n\n Адреси елементів масиву\n");
	for (size_t i = 0; i < arrSize; i++)
    {
        printf("arr[%d] = %d | Адреса: %p\n", i, arr[i], &arr[i]);
    }
    
    free(arr);
    arr = NULL;

	
	return 0;
}