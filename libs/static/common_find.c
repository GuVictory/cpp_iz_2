//
// Created by Victoria Gubanova on 24/10/2019.
//

#include "find_max_word.h"
#include "stdio.h"
#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr)   __builtin_expect(!!(expr), 1)

int find_max_word(const char* arr_of_words)
{
    if(arr_of_words == NULL)
    {
        return 0;
    }
    int max_lenght = 0;
    int current_lenght = 0;
    int space = 0;
    int i = 0;

    //Идем по строке пока не встречаем символ конца строки
    while (likely(*(arr_of_words + i) != '\0'))
    {
        //Если текущий символ является пробелом
        if(unlikely(*(arr_of_words + i) == ' '))
        {
            space++;
            //Если мы нашли больше предыдущего максимального
            if(unlikely(current_lenght <= max_lenght))
            {
                current_lenght = 0;
            }
            else {
                max_lenght = current_lenght;
                current_lenght = 0;
            }
        }
        else
        {
            current_lenght++;
        }

        ++i;
    }
    if(unlikely(space == 0))
        max_lenght = current_lenght;
    if(unlikely(current_lenght > max_lenght))
        max_lenght = current_lenght;

    return max_lenght;
}
