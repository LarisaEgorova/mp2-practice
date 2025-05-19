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
    Monom mon("x^2*20*z^3*-20*y^3*x^2*-4");
    Monom m(433, 1600);
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
    s = s + a;
    EXPECT_EQ(11, s.consts);
}

TEST(Monom, correct_division_this_monom)
{
    Monom a(1, 5);
    Monom s(1, 6);
    s = s - a;
    EXPECT_EQ(1, s.consts);
}

TEST(Monom, correct_product_this_monom)
{
    Monom a(1, 5);
    Monom s(1, 6);
    s = s * a;
    EXPECT_EQ(32, s.key + s.consts);
}


//POLINOMS

TEST(Polinom, can_create_polinom)
{
    ASSERT_NO_THROW(Polinom polinom);
}

TEST(Polinom, can_create_this_parameters_string) {
    string str = "x^2*20*z^3*-20*y^3+x^3+10*x^3*z^9-30*y^4+30";
    ASSERT_NO_THROW (Polinom pol(str));
}

TEST(Polinom, can_correct_create_this_parameters_string) {
    string str = "x^2*20*z^3*-20*y^3+x^3+10*x^3*z^9-30*y^4+30";
    Polinom pol;
    pol.insert_monom(Monom(309, 10));
    pol.insert_monom(Monom(300, 1));
    pol.insert_monom(Monom(233, -400));
    pol.insert_monom(Monom(40, -30));
    pol.insert_monom(Monom(0, 30));
    EXPECT_EQ(pol,  Polinom(str));
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
    Monom m(100, 10);
    Monom resm(100, 5);

    Polinom a(resm);
    Polinom s(m);
    Polinom res(resm);

    s = s - a;
    EXPECT_EQ(res, s);
}

TEST(Polinom, correct_product_polinom)
{
    Monom m(2, 10);
    Monom m1(20, 20);

    Polinom a(m);
    a.insert_monom(m1);
    Polinom s(m);
    Polinom res("200*y^2*z^2+100*z^4");

    s = s * a;
    EXPECT_EQ(res, s);
}

TEST(Polinom, correct_summation_const)
{
    Monom c(0, 10);
    Polinom s(c);
    s = s + c;
    EXPECT_EQ(Polinom(Monom(0, 20)), s);
}

TEST(Polinom, correct_division_const)
{
    Monom c(0, 10);
    Polinom s(c);
    s = s - c;
    Polinom m;
    EXPECT_EQ(m, s);
}

TEST(Polinom, correct_product_const)
{
    Monom c(0, 10);
    Polinom s(c);
    s = s * c;
    EXPECT_EQ(Polinom(Monom(0,100)), s);
}

TEST(Polinom, test1)
{
    Polinom p1("-x+1");
    Polinom p2("1+x");
    Polinom poli = p1 + p2;
    Polinom res("2");
    EXPECT_EQ(poli, res);
}

TEST(Polinom, test2)
{
    Polinom p1("-x+1");
    Polinom p2("1+x");
    Polinom poli = p1 - p2;
    Polinom res("-2*x");
    EXPECT_EQ(poli, res);
}

TEST(Polinom, test3)
{
    Polinom p1("-x+1");
    Polinom p2("1+x");
    Polinom poli = p1 * p2;
    EXPECT_EQ(poli, Polinom("1-x^2"));
}

TEST(Polinom, test4)
{
    Polinom p1("-x+1");
    Polinom p2("x+x^2+1");
    EXPECT_EQ(p1 * p2, Polinom("1-x^3"));
}

TEST(Polinom, test5)
{
    Polinom p1("x+1");
    Polinom p2("-x+x^2+1");
    EXPECT_EQ(p1 * p2, Polinom("1+x^3"));
}
