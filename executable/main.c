#include <stdio.h>
#include <stdlib.h>
#include "find_max_word.h"
#include "time.h"

int main(void)
{
    char* arr_of_words;
    arr_of_words = (char*) malloc(10 * sizeof(char));
    scanf("%[^\n]s", arr_of_words);

    //Произведем сравнение времени
    clock_t begin_1 = clock();
    int res1 = parallel_find(arr_of_words);
    clock_t end_1 = clock();
    double time_spent_1 = (double)(end_1 - begin_1 / CLOCKS_PER_SEC);

    clock_t begin_2 = clock();
    int res2 = find_max_word(arr_of_words);
    clock_t end_2 = clock();
    double time_spent_2 = (double)(end_2 - begin_2 / CLOCKS_PER_SEC);

    printf("Result by common_find: %d\nTime: %f\n\n"
           "Max size of word by parallel_find: %d\nTime: %f\n", res1, time_spent_2, res2, time_spent_1);
    free(arr_of_words);

    return 0;
}