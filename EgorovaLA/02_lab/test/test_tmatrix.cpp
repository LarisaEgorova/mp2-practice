#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);
  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(5), m1(m);
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5), m1(m);
	m[0][0] = 1;
	EXPECT_NE(m, m1);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	m[0][0] = 1;
	EXPECT_EQ(1, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(-3).at(-3) = 1000);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(10).at(10) = 1000);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(5), m1(5);
	ASSERT_NO_THROW(m = m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(5), m1(6);
	m = m1;
	EXPECT_EQ(6, m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(5), m1(6);
	m[0][0] = 1000;
	m1 = m;
	EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(5), m1(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5-i; j++) {
			m[i][j] = i + j;
			m1[i][j] = i + j;
		}
	}
	EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);
	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(5), m1(6);
	EXPECT_FALSE(m == m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(5), m1(5), res(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) {
			m[i][j] = i + j;
			m1[i][j] = i + j;
			res[i][j] = 2 * i + 2 * j;
		}
	}
	EXPECT_EQ(m + m1, res);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(5), m1(6);
	ASSERT_ANY_THROW(m+m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(5), m1(5), res(5); 
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) {
			m[i][j] = i + j;
			m1[i][j] = i + j;
			res[i][j] = i + j - i - j;
		}
	}
	EXPECT_EQ(m - m1, res);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(5), m1(6);
	ASSERT_ANY_THROW(m - m1);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_const) {
	TDynamicMatrix<int> m(5), res(5);
	const int val = 10;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5 - i; j++)
		{
			m[i][j] = i + j;
			res[i][j] = (i + j)*val;
		}
	}
	EXPECT_EQ(m*val, res);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
	TDynamicMatrix<int> m(3);
	TDynamicVector<int> v(3), res(3);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3 - i; j++) {
			m[i][j] = i + j;
		}
		v[i] = i+1;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3 - i; j++) {
			res[i] += m[i][j] * v[j];
		}
		v[i] = i + 1;
	}
	EXPECT_EQ(m * v, res);
}

TEST(TDynamicMatrix, cant_multiply_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(5), m1(6);
	ASSERT_ANY_THROW(m * m1);
}

TEST(TDynamicMatrix, can_multiply_matrixes_with_equal_size)
{
	TDynamicMatrix<int> m(5), m1(5), res(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) {
			m[i][j] = i + j;
			m1[i][j] = i + j;
			res[i][j] = 0;
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) {
			for (int k = 0; k < j + 1; k++) {
				res[i][j] += m[i][k] * m1[k + i][j - k];
			}
		}
	}

	EXPECT_EQ(m * m1, res);
}
