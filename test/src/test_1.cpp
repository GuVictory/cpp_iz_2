//
// Created by Victoria Gubanova on 23/10/2019.
//


#include "gtest/gtest.h"
extern "C"
{
#include "find_max_word.h"
}


TEST(example, find_max_word_par_1)
{
    char arr[] = "qwe cv fghr crd a nf";
    int res = parallel_find(arr);
    ASSERT_EQ(4, res);
}


TEST(example, find_max_word_par_2)
{
    char arr[] = " ";
    int res = parallel_find(arr);
    ASSERT_EQ(0, res);
}

TEST(example, find_max_word_par_3)
{
    char arr[] = "as as as as as as ";
    int res = parallel_find(arr);
    ASSERT_EQ(2, res);
}

TEST(example, find_max_word_par_4)
{
    char arr[] = " as as as as as as";
    int res = parallel_find(arr);
    ASSERT_EQ(2, res);
}

TEST(example, find_max_word_par_5)
{
    char arr[] = "vvvaaaddd";
    int res = parallel_find(arr);
    ASSERT_EQ(9, res);
}


TEST(example, find_max_word_1)
{
    char arr[] = "qwe cv fghr crd a nf";
    int res = find_max_word(arr);
    ASSERT_EQ(4, res);
}

TEST(example, find_max_word_2)
{
    char arr[] = " ";
    int res = find_max_word(arr);
    ASSERT_EQ(0, res);
}

TEST(example, find_max_word_3)
{
    char arr[] = "as as as as as as ";
    int res = find_max_word(arr);
    ASSERT_EQ(2, res);
}

TEST(example, find_max_word_4)
{
    char arr[] = " as as as as as as";
    int res = find_max_word(arr);
    ASSERT_EQ(2, res);
}

TEST(example, find_max_word_5)
{
    char arr[] = "vvvaaaddd";
    int res = find_max_word(arr);
    ASSERT_EQ(9, res);
}


//Пропишем тесты, которые сравинивают значение разных реализций между собой
TEST(example, is_the_same_1)
{
    char arr[] = "qwe cv fghr crd a nf";
    int res1 = find_max_word(arr);
    int res2 = parallel_find(arr);
    ASSERT_EQ(res1, res2);
}

TEST(example, is_the_same_2)
{
    char arr[] = " ";
    int res1 = find_max_word(arr);
    int res2 = parallel_find(arr);
    ASSERT_EQ(res1, res2);
}

TEST(example, is_the_same_3)
{
    char arr[] = "as as as as as as ";
    int res1 = find_max_word(arr);
    int res2 = parallel_find(arr);
    ASSERT_EQ(res1, res2);
}

TEST(example, is_the_same_4)
{
    char arr[] = " as as as as as as";
    int res1 = find_max_word(arr);
    int res2 = parallel_find(arr);
    ASSERT_EQ(res1, res2);
}

TEST(example, is_the_same_5)
{
    char arr[] = "vvvaaaddd";
    int res1 = find_max_word(arr);
    int res2 = parallel_find(arr);
    ASSERT_EQ(res1, res2);
}
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}