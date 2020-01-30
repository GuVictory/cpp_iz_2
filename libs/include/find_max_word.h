//
// Created by Victoria Gubanova on 24/10/2019.
//

#ifndef TP_CPP_IZ2_FIND_MAX_WORD_H
#define TP_CPP_IZ2_FIND_MAX_WORD_H

//специальная структура для данных потока
typedef struct{
    int pthr_id;
    int start_pos; //первый символ для обработки строки
    int end_pos; //последний символ для обработки
    int sizes_of_max_word; //массив результата подсчета длины слов для каждого потока
    const char* arr_of_words; //указатель на исходную строку
} pthr_data;

int find_max_word(const char*);
int parallel_find(const char*);



#endif //TP_CPP_IZ2_FIND_MAX_WORD_H
