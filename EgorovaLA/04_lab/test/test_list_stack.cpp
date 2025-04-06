#include "list_stack.h"

#include <gtest.h>

TEST(TListStack, can_create_stack)
{
	ASSERT_NO_THROW(TListStack<int> s);
}

TEST(TListStack, can_create_copied_stack)
{
	TListStack<int> s;
	ASSERT_NO_THROW(TListStack<int> s1(s));
}

TEST(TListStack, copied_stack_is_equal_to_source_one)
{
	TListStack<int> s, s1(s);
	EXPECT_EQ(s, s1);
}

TEST(TListStack, copied_stack_has_its_own_memory)
{
	TListStack<int> s, s1(s);
	s.Push(15);
	s1.Push(1);
	EXPECT_NE(s.Top(), s1.Top());
}

TEST(TListStack, stack_is_empty) {
	TListStack<int> s;
	EXPECT_EQ(s.IsEmpty(), 1);
}

TEST(TListStack, stack_can_push_element) {
	TListStack<int> s;
	ASSERT_NO_THROW(s.Push(15));
}

TEST(TListStack, stack_is_full) {
	TListStack<int> s;
	s.Push(15);
	EXPECT_EQ(s.IsFull(), 1);
}

TEST(TListStack, stack_can_top_element) {
	TListStack<int> s;
	s.Push(15);
	EXPECT_EQ(s.Top(), 15);
}

TEST(TListStack, stack_can_pop_element) {
	TListStack<int> s;
	s.Push(15);
	s.Pop();
	EXPECT_TRUE(s.IsEmpty());
}

TEST(TListStack, can_assign_stacks_of_equal_size)
{
	TListStack<int> s, s1;
	s.Push(15);
	s1 = s;
	EXPECT_EQ(s1,s);
}

TEST(TListStack, can_assign_stacks_of_different_size)
{
	TListStack<int> s, s1;
	s.Push(15);
	s.Push(15);
	s1 = s;
	EXPECT_EQ(s,s1);;
}

TEST(TListStack, compare_equal_stacks_return_true)
{
	TListStack<int> s, s1;
	s.Push(15);
	s1.Push(15);
	EXPECT_TRUE(s1 == s);
}

TEST(TListStack, compare_stack_with_itself_return_true)
{
	TListStack<int> s;
	s.Push(15);
	EXPECT_TRUE(s == s);
}
