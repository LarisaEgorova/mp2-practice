#include "list.h"

#include <gtest.h>

TEST(TList, can_create_list)
{
    ASSERT_NO_THROW(TList<int> list);
}

TEST(TList, can_create_list_with_parameters)
{
    ASSERT_NO_THROW(TList<int> list(5));
}

TEST(TList, can_create_copied_list)
{
    TList<int> list(5);
    ASSERT_NO_THROW(TList<int> list1(list));
}

TEST(TList, copied_list_is_equal_to_source_one)
{
    TList<int>  list(5), list1(list);
    EXPECT_EQ(list, list1);
}

TEST(TList, can_use_the_assignment_operator)
{
    TList<int> a(5);
    TList<int> s;
    ASSERT_NO_THROW(s = a);
}

TEST(TList, correct_use_the_assignment_operator)
{
    TList<int> a(5);
    TList<int> s;
    s = a;
    EXPECT_TRUE(s == a);
}

TEST(TList, correct_push_front)
{
    TList<int> a;
    a.pushFront(5);
    EXPECT_EQ(5, a.getPFirst()->Data);
}

TEST(TList, correct_push_back)
{
    TList<int> a;
    a.pushBack(5);
    a.pushBack(5);
    EXPECT_EQ(5, a.getPFirst()->pNext->Data);
}

TEST(TList, correct_pop_back)
{
    TList<int> a;
    a.pushBack(5);
    a.pushBack(10);
    a.PopBack();
    EXPECT_EQ(5, a.getPFirst()->Data);
}

TEST(TList, correct_pop_front)
{
    TList<int> a;
    a.pushBack(10);
    a.pushBack(5);
    a.PopFront();
    EXPECT_EQ(5, a.getPFirst()->Data);
}

TEST(TList, cant_popback_from_empty_list)
{
    TList<int> st;
    ASSERT_ANY_THROW(st.PopBack());
}
TEST(TList, cant_popfront_from_empty_list)
{
    TList<int> st;
    ASSERT_ANY_THROW(st.PopFront());
}
TEST(TList, correct_get_size)
{
    TList<int> a;
    a.pushBack(5);
    a.pushBack(5);
    EXPECT_EQ(2, a.size());
}

TEST(TList, is_empty_false_when_list_no_empty)
{
    TList<int> a;
    a.pushBack(5);
    EXPECT_EQ(false, a.IsEmpty());
}

TEST(TList, is_empty_true_when_list_empty)
{
    TList<int> a;
    EXPECT_EQ(true, a.IsEmpty());
}

TEST(TList, is_ended_false_when_list_not_end)
{
    TList<int> a;
    a.pushBack(5);
    a.pushBack(5);
    a.reset();
    EXPECT_EQ(false, a.IsEnded());
}

TEST(TList, is_ended_true_when_list_end)
{
    TList<int> a;
    a.pushBack(5);
    a.reset();
    EXPECT_EQ(true, a.IsEnded());
}

TEST(TList, correct_reset)
{
    TList<int> a;
    a.pushBack(5);
    a.pushBack(5);
    a.reset();
    EXPECT_EQ(false, a.IsEnded());
}

TEST(TList, correct_push_before)
{
    TList<int> a;
    a.pushBack(5);
    a.pushBefore(10, 5);
    EXPECT_EQ(10, a.getPFirst()->Data);
}

TEST(TList, correct_push_after)
{
    TList<int> a;
    a.pushBack(5);
    a.pushAfter(10, 5);
    EXPECT_EQ(10, a.getPFirst()->pNext->Data);
}