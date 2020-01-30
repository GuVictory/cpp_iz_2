//
// Created by Victoria Gubanova on 24/10/2019.
//

#include "find_max_word.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include <pthread.h>
#include "unistd.h"
#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr)   __builtin_expect(!!(expr), 1)


void* threadFunc(void* thread_data)
{
    //получаем структуру с данными
    pthr_data *data = (pthr_data*) thread_data;

    int new_size = data->end_pos - data->start_pos + 2;
    //создаем строку из того промежутка основной строки, которая принадлежит потоку
    char new_string[new_size];
    strncpy(new_string, data->arr_of_words + data->start_pos, data->end_pos - data->start_pos + 1);
    new_string[data->end_pos - data->start_pos + 1] = '\0';

    //выполняем функцию поиска для нашего потока и записываем результат в массив
    data->sizes_of_max_word = find_max_word(new_string);

    return NULL;
}


int find_max_in_arr(pthr_data *arr, int arr_size)
{
    if(unlikely(arr == NULL)) return 0;
    int max = 0;
    for(int i = 0; i < arr_size; ++i)
    {
        if(likely(arr[i].sizes_of_max_word > max))
        {
            max = arr[i].sizes_of_max_word;
        }
    }
    return max;
}

unsigned long* find_start_pos(const char* arr_of_words, int *number_of_pthreads, unsigned long string_size)
{
    unsigned long* arr_of_start_pos = (unsigned long*) malloc (*number_of_pthreads * sizeof(unsigned long));
    //сначала найдем первое разбиение
    arr_of_start_pos[0] = 0;

    //найдем индексы элементов по которым мы будем разбивать строку
    for(int i = 1; i < *number_of_pthreads; i++)
    {
        unsigned long middle_pos = arr_of_start_pos[i - 1] + string_size/(*number_of_pthreads);
        if(likely(middle_pos != 0))
        {
            if(likely(middle_pos < string_size))
            {
                while (*(arr_of_words+middle_pos) != ' ')
                {
                    if(unlikely(middle_pos == string_size - 1))
                    {
                        *number_of_pthreads = i;
                        break;
                    }
                    middle_pos++;
                }

                arr_of_start_pos[i] = middle_pos;
            } else
            {
                *number_of_pthreads = i - 1;
                continue;
            }

        }
    }

    return arr_of_start_pos;
}



int parallel_find(const char* arr_of_words)
{
    //проверяем строку на пустоту
    if(unlikely(arr_of_words == NULL))
    {
        return 0;
    }

    long string_size = strlen(arr_of_words);
    int number_of_pthreads = 0; //количество изспользуемых потоков
    pthread_t* threads = NULL;
    pthr_data* threadData = NULL;

    //если строка маленькая, то не создаем потоки
    if(unlikely(string_size < 10))
    {
        number_of_pthreads = 1;
        //выделяем память под массив идентификаторов потоков
        threads = (pthread_t*) malloc(number_of_pthreads * sizeof(pthread_t));

        //сколько потоков - столько и структур с потоковых данных
        threadData = (pthr_data*) malloc(number_of_pthreads * sizeof(pthr_data));

        threadData[0].pthr_id = 0;
        threadData[0].arr_of_words = arr_of_words;
        threadData[0].start_pos = 0;
        threadData[0].end_pos = string_size - 1;
        threadData[0].sizes_of_max_word = 0;
        //запускаем поток
        pthread_create(&(threads[0]), NULL, threadFunc, &threadData[0]);
    } else
    {
        number_of_pthreads = sysconf(_SC_NPROCESSORS_ONLN);
        unsigned long* arr_of_start_pos = find_start_pos(arr_of_words, &number_of_pthreads, string_size);

        //выделяем память под массив идентификаторов потоков
        threads = (pthread_t*) malloc(number_of_pthreads * sizeof(pthread_t));

        //сколько потоков - столько и структур с потоковых данных
        threadData = (pthr_data*) malloc(number_of_pthreads * sizeof(pthr_data));


        for(int i = 0; i < number_of_pthreads; ++i)
        {
            threadData[i].pthr_id = i;
            threadData[i].arr_of_words = arr_of_words;
            threadData[i].start_pos = arr_of_start_pos[i];

            if(likely(i != number_of_pthreads -1))
            {
                threadData[i].end_pos = arr_of_start_pos[i + 1] - 1;
            } else
            {
                threadData[i].end_pos = string_size - 1;
            }
            threadData[i].sizes_of_max_word = 0;
            //запускаем поток
            pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
        }
        free(arr_of_start_pos);
    }

    if(unlikely(threads == NULL)) return 0;

    //ожидаем выполнение всех потоков
    for(int i = 0; i < number_of_pthreads; i++)
        pthread_join(threads[i], NULL);

    //находим максимальное значение длины слова
    int result = find_max_in_arr(threadData, number_of_pthreads);

    //освобождаем память
    free(threads);
    free(threadData);
    return result;
}

int main()
{
    return 0;
}
