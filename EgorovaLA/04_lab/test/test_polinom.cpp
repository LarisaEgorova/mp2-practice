#include "polinom.h"

#include <gtest.h>

//MONOMS

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

TEST(Monom, correct_summation_const)
{
    Monom<int> m(5, 10);
    Monom<int> resm(5, 30);
    m = m + 20;
    EXPECT_EQ(resm, m);
}

TEST(Monom, correct_division_const)
{
    Monom<int> m(5, 10);
    Monom<int> resm(5, -10);
    m = m - 20;
    EXPECT_EQ(resm, m);
}

TEST(Monom, correct_product_const)
{
    Monom<int> m(5, 10);
    Monom<int> resm(5, 200);
    m = m * 20;
    EXPECT_EQ(resm, m);
}


//POLINOMS

TEST(Polinom, can_create_polinom)
{
    ASSERT_NO_THROW(Polinom<int> polinom);
}

TEST(Polinom, can_create_polinom_this_parameters)
{
    TRingHeadList<int> list(5);
    list.pushBack(1);
    ASSERT_NO_THROW(Polinom<int> polinom(list));
}

TEST(Polinom, can_create_copied_polinom)
{
    Polinom<int> P(5);
    ASSERT_NO_THROW(Polinom<int> polinom(P));
}

TEST(Polinom, copied_polinom_is_equal_to_source_one)
{
    Polinom<int>  P(5), P1(P);
    EXPECT_EQ(P, P1);
}

TEST(Polinom, can_use_the_assignment_operator)
{
    Polinom<int> a(5);
    Polinom<int> s;
    ASSERT_NO_THROW(s = a);
}

TEST(Polinom, correct_summation_polinom)
{
    Monom<int> m(5, 10);
    Monom<int> resm(5, 20);

    Polinom<Monom<int>> a(m);
    Polinom<Monom<int>> s(m);
    Polinom<Monom<int>> res(resm);

    s = s + a;
    EXPECT_EQ(res, s);
}

TEST(Polinom, correct_division_polinom)
{
    Monom<int> m(5, 10);
    Monom<int> resm(5, 0);

    Polinom<Monom<int>> a(m);
    Polinom<Monom<int>> s(m);
    Polinom<Monom<int>> res(resm);

    s = s - a;
    EXPECT_EQ(res, s);
}

TEST(Polinom, correct_product_polinom)
{
    Monom<int> m(4, 10);
    Monom<int> resm(8, 100);

    Polinom<Monom<int>> a(m);
    Polinom<Monom<int>> s(m);
    Polinom<Monom<int>> res(resm);

    s = s * a;
    EXPECT_EQ(res, s);
}

TEST(Polinom, correct_summation_const)
{
    Polinom<int> s(10);
    s = s + 10;
    EXPECT_EQ(10, s.getPolinom().getHead()->Data);
}

TEST(Polinom, correct_division_const)
{
    Polinom<int> s(10);
    s = s - 10;
    EXPECT_EQ(-10, s.getPolinom().getHead()->Data);
}

TEST(Polinom, correct_product_const)
{
    Polinom<int> s(10);
    s = s * 10;
    EXPECT_EQ(0, s.getPolinom().getHead()->Data);
}
