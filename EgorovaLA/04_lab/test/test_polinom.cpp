#include "polinom.h"

#include <gtest.h>

//MONOMS

TEST(Monom, can_create_monom)
{
	ASSERT_NO_THROW(Monom s);
}

TEST(Monom, can_create_Monom_with_parameters_int)
{
	ASSERT_NO_THROW(Monom list(5, 6));
}

TEST(Monom, can_create_Monom_with_parameters_string)
{
    ASSERT_NO_THROW(Monom m("x^2*20*z^3*-20*y^3"));
}

TEST(Monom, can_correct_create_Monom_with_parameters_string)
{
    Monom mon("x^2*20*z^3*-20*y^3*x^2");
    Monom m(433, -400);
    EXPECT_EQ(m, mon);
}

TEST(Monom, can_create_copied_monom)
{
    Monom s;
	ASSERT_NO_THROW(Monom s1(s));
}

TEST(Monom, copied_monom_is_equal_to_source_one)
{
    Monom s, s1(s);
	EXPECT_EQ(s, s1);
}

TEST(Monom, can_use_the_assignment_operator)
{
    Monom a(5, 1);
    Monom s;
    ASSERT_NO_THROW(s = a);
}

TEST(Monom, correct_use_the_assignment_operator)
{
    Monom a(5, 1);
    Monom s(6, 2);
    s = a;
    EXPECT_TRUE(s == a);
}

TEST(Monom, correct_summation_this_monom)
{
    Monom a(1, 5);
    Monom s(1, 6);
    s=s+a;
    EXPECT_EQ(11, s.GetConsts());
}

TEST(Monom, correct_division_this_monom)
{
    Monom a(1, 5);
    Monom s(1, 6);
    s = s - a;
    EXPECT_EQ(1, s.GetConsts());
}

TEST(Monom, correct_product_this_monom)
{
    Monom a(1, 5);
    Monom s(1, 6);
    s = s * a;
    EXPECT_EQ(32, s.GetKey()+s.GetConsts());
}

TEST(Monom, correct_summation_const)
{
    Monom m(5, 10);
    Monom resm(5, 30);
    m = m + 20;
    EXPECT_EQ(resm, m);
}

TEST(Monom, correct_division_const)
{
    Monom m(5, 10);
    Monom resm(5, -10);
    m = m - 20;
    EXPECT_EQ(resm, m);
}

TEST(Monom, correct_product_const)
{
    Monom m(5, 10);
    Monom resm(5, 200);
    m = m * 20;
    EXPECT_EQ(resm, m);
}




//POLINOMS

TEST(Polinom, can_create_polinom)
{
    ASSERT_NO_THROW(Polinom polinom);
}

TEST(Polinom, can_create_polinom_this_parameters_ringheadlist)
{
    Monom m(10, 111);
    TRingHeadList<Monom> list(m);
    Monom m1(20, 222);
    list.pushBack(m1);
    ASSERT_NO_THROW(Polinom polinom(list));
}

TEST(Polinom, can_create_this_parameters_string) {
    string str = "x^2*20*z^3*(-20)*y^3+x^3+10*x^3*z^9-30*y^4+30";
    ASSERT_NO_THROW (Polinom pol(str));
}

TEST(Polinom, can_correct_create_this_parameters_string) {
    string str = "x^2*20*z^3*(-20)*y^3+x^3+10*x^3*z^9-30*y^4+30";
    TRingHeadList<Monom> list;
    list.pushBack(Monom(233, -400));
    list.pushBack(Monom(300, 1));
    list.pushBack(Monom(309, 10));
    list.pushBack(Monom(40, -30));
    list.setHead(Monom(0,30));
    EXPECT_EQ(Polinom(list), Polinom(str));
}

TEST(Polinom, can_create_copied_polinom)
{
    Monom m(10, 111);
    Polinom P(m);
    ASSERT_NO_THROW(Polinom polinom(P));
}

TEST(Polinom, copied_polinom_is_equal_to_source_one)
{
    Monom m(10, 111);
    Polinom P(m), P1(P);
    EXPECT_EQ(P, P1);
}

TEST(Polinom, can_use_the_assignment_operator)
{
    Monom m(10, 111);
    Polinom a(m);
    Polinom s;
    ASSERT_NO_THROW(s = a);
}

TEST(Polinom, can_correct_use_the_assignment_operator)
{
    Monom m(10, 111);
    Polinom a(m);
    Polinom s = a;
    EXPECT_EQ(s, a);
}

TEST(Polinom, correct_summation_polinom)
{
    Monom m(5, 10);
    Monom resm(5, 20);

    Polinom a(m);
    Polinom s(m);
    Polinom res(resm);

    s = s + a;
    EXPECT_EQ(res, s);
}

TEST(Polinom, correct_division_polinom)
{
    Monom m(5, 10);
    Monom resm(5, 0);

    Polinom a(m);
    Polinom s(m);
    Polinom res(resm);

    s = s - a;
    EXPECT_EQ(res, s);
}

TEST(Polinom, correct_product_polinom)
{
    Monom m(4, 10);
    Monom resm(8, 100);

    Polinom a(m);
    Polinom s(m);
    Polinom res(resm);

    s = s * a;
    EXPECT_EQ(res, s);
}

TEST(Polinom, correct_summation_const)
{
    Monom c(0, 10);
    Polinom s(c);
    s = s + c;
    EXPECT_EQ(20, s.getPolinom().getHead()->Data.GetConsts());
}

TEST(Polinom, correct_division_const)
{
    Monom c(0, 10);
    Polinom s(c);
    s = s - c;
    EXPECT_EQ(0, s.getPolinom().getHead()->Data.GetConsts());
}

TEST(Polinom, correct_product_const)
{
    Monom c(0, 10);
    Polinom s(c);
    s = s * c;
    EXPECT_EQ(100, s.getPolinom().getHead()->Data.GetConsts());
}
