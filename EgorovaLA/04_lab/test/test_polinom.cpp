#include "polinom.h"

#include <gtest.h>

TEST(Monom, can_create_monom)
{
	ASSERT_NO_THROW(Monom<int> s);
}

TEST(Monom, can_create_Monom_with_parameters)
{
	ASSERT_NO_THROW(Monom<int> list(5, 6));
}

TEST(Monom, can_create_copied_monom)
{
	Monom<int> s;
	ASSERT_NO_THROW(Monom<int> s1(s));
}

TEST(Monom, copied_monom_is_equal_to_source_one)
{
	Monom<int> s, s1(s);
	EXPECT_EQ(s, s1);
}

TEST(Monom, can_use_the_assignment_operator)
{
    Monom<int> a(5, 1);
    Monom<int> s;
    ASSERT_NO_THROW(s = a);
}

TEST(Monom, correct_use_the_assignment_operator)
{
    Monom<int> a(5, 1);
    Monom<int> s(6, 2);
    s = a;
    EXPECT_TRUE(s == a);
}

TEST(Monom, correct_summation_this_monom)
{
    Monom<int> a(1, 5);
    Monom<int> s(1, 6);
    s=s+a;
    EXPECT_EQ(11, s.GetConsts());
}

TEST(Monom, correct_division_this_monom)
{
    Monom<int> a(1, 5);
    Monom<int> s(1, 6);
    s = s - a;
    EXPECT_EQ(1, s.GetConsts());
}

TEST(Monom, correct_product_this_monom)
{
    Monom<int> a(1, 5);
    Monom<int> s(1, 6);
    s = s * a;
    EXPECT_EQ(32, s.GetKey()+s.GetConsts());
}

