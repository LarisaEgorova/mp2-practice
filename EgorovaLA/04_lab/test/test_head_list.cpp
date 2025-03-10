#include "head_list.h"

#include <gtest.h>

/*TEST(THeadList, can_create_headlist)
{
    ASSERT_NO_THROW(THeadList<int> list);
}

TEST(THeadList, can_create_headlist_with_parameters)
{
    ASSERT_NO_THROW(THeadList<int> list(5, 6));
}

TEST(THeadList, can_create_copied_headlist)
{
    THeadList<int> list(5, 6);
    ASSERT_NO_THROW(THeadList<int> list1(list));
}

TEST(THeadList, copied_headlist_is_equal_to_source_one)
{
    THeadList<int>  list(5, 6), list1(list);
    EXPECT_EQ(list, list1);
}

TEST(THeadList, correct_push_front_headlist)
{
    THeadList<int> a;
    a.pushFront(5,1);
    EXPECT_EQ(5, a.getPFirst()->Data);
}

TEST(THeadList, correct_push_back_headlist)
{
    THeadList<int> a;
    a.pushBack(5, 1);
    a.pushBack(6, 2);
    EXPECT_EQ(6, a.getPFirst()->pNext->Data);
}

TEST(THeadList, correct_pop_back_headlist)
{
    THeadList<int> a;
    a.pushBack(5, 1);
    a.pushBack(10, 2);
    a.PopBack();
    EXPECT_EQ(5, a.getPFirst()->Data);
}

TEST(THeadList, correct_pop_front_headlist)
{
    THeadList<int> a;
    a.pushBack(10,2);
    a.pushBack(5,1);
    a.PopFront();
    EXPECT_EQ(5, a.getPFirst()->Data);
}

TEST(THeadList, cant_popback_from_empty_headlist)
{
    THeadList<int> st;
    ASSERT_ANY_THROW(st.PopBack());
}

TEST(THeadList, cant_popfront_from_empty_headlist)
{
    THeadList<int> st;
    ASSERT_ANY_THROW(st.PopFront());
}

TEST(THeadList, correct_get_size_headlist)
{
    THeadList<int> a;
    a.pushBack(5,1);
    a.pushBack(5,2);
    EXPECT_EQ(3, a.size());
}

TEST(THeadList, is_empty_false_when_headlist_no_empty)
{
    THeadList<int> a;
    a.pushBack(5,1);
    EXPECT_EQ(false, a.IsEmpty());
}

TEST(THeadList, is_empty_true_when_headlist_empty)
{
    THeadList<int> a;
    EXPECT_EQ(true, a.IsEmpty());
}

TEST(THeadList, can_use_the_assignment_operator)
{
    THeadList<int> a(5,1);
    THeadList<int> s;
    ASSERT_NO_THROW(s = a);
}

TEST(THeadList, correct_use_the_assignment_operator)
{
    THeadList<int> a(5,1);
    THeadList<int> s(6,2);
    s = a;
    EXPECT_TRUE(s == a);
}

TEST(THeadList, correct_pushAfter)
{
    THeadList<int> a(5, 1);
    a.pushAfter(10,2,1);
    TNode<int>* tmp = a.findElem(1);
    EXPECT_EQ(10, tmp->pNext->Data);
}

TEST(THeadList, correct_pushBefore)
{
    THeadList<int> a(5, 1);
    a.pushBefore(10, 0, 1);
    TNode<int>* tmp = a.findElem(0);
    EXPECT_EQ(10, tmp->Data);
}

*/