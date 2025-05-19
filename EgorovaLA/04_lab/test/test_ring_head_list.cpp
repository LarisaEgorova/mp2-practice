#include "ring_head_list.h"
#include <gtest.h>

TEST(TRingHeadList, can_create_headlist)
{
    ASSERT_NO_THROW(TRingHeadList<int> list);
}

TEST(TRingHeadList, can_create_headlist_with_parameters)
{
    ASSERT_NO_THROW(TRingHeadList<int> list(5));
}

TEST(TRingHeadList, can_create_copied_headlist)
{
    TRingHeadList<int> list(5);
    ASSERT_NO_THROW(TRingHeadList<int> list1(list));
}

TEST(TRingHeadList, copied_list_is_equal_to_source_one)
{
    TRingHeadList<int>  list(5), list1(list);
    EXPECT_EQ(list, list1);
}

TEST(TRingHeadList, can_use_the_assignment_operator)
{
    TRingHeadList<int> a(5);
    TRingHeadList<int> s;
    ASSERT_NO_THROW(s = a);
}

TEST(TRingHeadList, correct_push_front)
{
    TRingHeadList<int> a;
    a.pushFront(5);
    EXPECT_EQ(5, a.getPFirst()->Data);
}

TEST(TRingHeadList, correct_push_back)
{
    TRingHeadList<int> a;
    a.pushBack(5);
    a.pushBack(5);
    EXPECT_EQ(5, a.getPFirst()->pNext->Data);
}

TEST(TRingHeadList, correct_pop_back)
{
    TRingHeadList<int> a;
    a.pushBack(5);
    a.pushBack(10);
    a.PopBack();
    EXPECT_EQ(5, a.getPFirst()->Data);
}

TEST(TRingHeadList, correct_pop_front)
{
    TRingHeadList<int> a;
    a.pushBack(10);
    a.pushBack(5);
    a.PopFront();
    EXPECT_EQ(5, a.getPFirst()->Data);
}

TEST(TRingHeadList, is_empty_false_when_list_no_empty)
{
    TRingHeadList<int> a;
    a.pushBack(5);
    EXPECT_EQ(false, a.IsEmpty());
}

TEST(TRingHeadList, is_empty_true_when_list_empty)
{
    TRingHeadList<int> a;
    EXPECT_EQ(true, a.IsEmpty());
}

TEST(TRingHeadList, correct_push_before)
{
    TRingHeadList<int> a;
    a.pushBack(5);
    a.pushBefore(10, 5);
    EXPECT_EQ(10, a.getPFirst()->Data);
}

TEST(TRingHeadList, correct_push_after)
{
    TRingHeadList<int> a;
    a.pushBack(5);
    a.pushAfter(10, 5);
    EXPECT_EQ(10, a.getPFirst()->pNext->Data);
}

TEST(TRingHeadList, correct_get_size)
{
    TRingHeadList<int> a;
    a.pushBack(5);
    a.pushBack(5);
    EXPECT_EQ(2, a.size());
}