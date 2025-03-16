#include "headlist_stack.h"

#include <gtest.h>

TEST(THeadList, can_create_headlist)
{
    ASSERT_NO_THROW(THeadList<int> list);
}

TEST(THeadList, can_create_headlist_with_parameters)
{
    ASSERT_NO_THROW(THeadList<int> list(5));
}

TEST(THeadList, can_create_copied_headlist)
{
    THeadList<int> list(5);
    ASSERT_NO_THROW(THeadList<int> list1(list));
}

TEST(THeadList, copied_list_is_equal_to_source_one)
{
    THeadList<int>  list(5), list1(list);
    EXPECT_EQ(list, list1);
}

TEST(THeadList, can_use_the_assignment_operator)
{
    THeadList<int> a(5);
    THeadList<int> s;
    ASSERT_NO_THROW(s = a);
}

TEST(THeadList, correct_push_front)
{
    THeadList<int> a;
    a.pushFront(5);
    EXPECT_EQ(5, a.getHead()->pNext->Data);
}

TEST(THeadList, correct_push_back)
{
    THeadList<int> a;
    a.pushBack(5);
    a.pushBack(5);
    EXPECT_EQ(5, a.getPFirst()->pNext->Data);
}

TEST(THeadList, correct_pop_back)
{
    THeadList<int> a;
    a.pushBack(5);
    a.pushBack(10);
    a.PopBack();
    EXPECT_EQ(5, a.getHead()->pNext->Data);
}

TEST(THeadList, correct_pop_front)
{
    THeadList<int> a;
    a.pushBack(10);
    a.pushBack(5);
    a.PopFront();
    EXPECT_EQ(5, a.getHead()->pNext->Data);
}

TEST(THeadList, is_empty_false_when_list_no_empty)
{
    THeadList<int> a;
    a.pushBack(5);
    EXPECT_EQ(false, a.IsEmpty());
}

TEST(THeadList, is_empty_true_when_list_empty)
{
    THeadList<int> a;
    EXPECT_EQ(true, a.IsEmpty());
}

TEST(THeadList, correct_push_before)
{
    THeadList<int> a;
    a.pushBack(5);
    a.pushBefore(10, 5);
    EXPECT_EQ(10, a.getHead()->pNext->Data);
}

TEST(THeadList, correct_push_after)
{
    THeadList<int> a;
    a.pushBack(5);
    a.pushAfter(10, 5);
    EXPECT_EQ(10, a.getPFirst()->pNext->Data);
}

TEST(THeadList, correct_get_size)
{
    THeadList<int> a;
    a.pushBack(5);
    a.pushBack(5);
    EXPECT_EQ(3, a.size());
}