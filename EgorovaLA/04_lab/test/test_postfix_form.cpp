#include "postfix_form.h"
#include <gtest.h>

TEST(Postfix_Form, can_fill_const_correct)
{
	string str = "A+";
	vector<string> consts = fill_const(str);
	EXPECT_EQ("A", consts[0]);
}

TEST(Postfix_Form, can_check_priority)
{
	string elem = "*", elem2= "-";
	EXPECT_TRUE(priority(elem, elem2));
}

TEST(Postfix_Form, can_correct_read_str)
{
	vector<string> v = read("A+B");
	EXPECT_EQ("A+B", v[0]+ v[1]+ v[2]);
}

TEST(Postfix_Form, can_create_correct_expession_on_list)
{
	TStack<string>* stack1;
	TStack<string>* stack2;;

	stack1 = new TListStack <string>();
	stack2 = new TListStack <string>();

	vector<string> v = read("A+B");
	expression(stack1, stack2, v);
	string str;
	str = stack2->Top();
	stack2->Pop();
	str += stack2->Top();
	stack2->Pop();
	str += stack2->Top();
	EXPECT_EQ("AB+", str);
}

TEST(Postfix_Form, can_correct_calculate_list1)
{
	TStack<string>* stack1;
	TStack<string>* stack2;
	TStack<double>* stack3;

	stack1 = new TListStack <string>();
	stack2 = new TListStack <string>();
	stack3 = new TListStack <double>();

	vector<string> v = read("A+B");
	expression(stack1, stack2, v);
	map<string, double> var;
	var["A"] = 1; var["B"] = 1;
	EXPECT_EQ(2,calculate(stack3,stack2,var));
}

TEST(Postfix_Form, can_correct_calculate_list2)
{
	TStack<string>* stack1;
	TStack<string>* stack2;
	TStack<double>* stack3;

	stack1 = new TListStack <string>();
	stack2 = new TListStack <string>();
	stack3 = new TListStack <double>();

	vector<string> v = read("A-B");
	expression(stack1, stack2, v);
	map<string, double> var;
	var["A"] = 1; var["B"] = 3; 
	EXPECT_EQ(-2, calculate(stack3, stack2, var));
}

TEST(Postfix_Form, can_correct_calculate_list3)
{
	TStack<string>* stack1;
	TStack<string>* stack2;
	TStack<double>* stack3;

	stack1 = new TListStack <string>();
	stack2 = new TListStack <string>();
	stack3 = new TListStack <double>();

	vector<string> v = read("A-B*(A+C)");
	expression(stack1, stack2, v);
	map<string, double> var;
	var["A"] = 1; var["B"] = 2; var["C"] = 3;
	EXPECT_EQ(-7, calculate(stack3, stack2, var));
}

TEST(Postfix_Form, can_correct_calculate_list4)
{
	TStack<string>* stack1;
	TStack<string>* stack2;
	TStack<double>* stack3;

	stack1 = new TListStack <string>();
	stack2 = new TListStack <string>();
	stack3 = new TListStack <double>();

	vector<string> v = read("(A-B)/(C-A)*(K+B)+A");
	expression(stack1, stack2, v);
	map<string, double> var;
	var["A"] = 1; var["B"] = 3; var["C"] = 2; var["K"] = -2;
	EXPECT_EQ(-1, calculate(stack3, stack2, var));
}

