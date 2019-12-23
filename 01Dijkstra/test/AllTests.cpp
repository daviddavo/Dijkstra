#include "gtest/gtest.h"
#include "skewheap.h"

using namespace std;

class TestSkewHeap : public :: testing::Test {
protected:
	SkewHeap<int,int> _vacio;
};

class TestInsert : public :: TestSkewHeap {};

TEST_F(TestInsert, Increasing) {
	for (int i = 0; i <= 10; ++i) {
		_vacio.insert(i, i);
	}

	ASSERT_EQ(_vacio.getMin()->getKey(), 0);
	ASSERT_EQ(_vacio.getMin()->getVal(), 0);
}

TEST_F(TestInsert, Decreasing) {
	for (int i = 10; i >= 0; --i) {
		_vacio.insert(i, i);
	}

	ASSERT_EQ(_vacio.getMin()->getKey(), 0);
	ASSERT_EQ(_vacio.getMin()->getVal(), 0);
}

class TestDelete : public :: TestSkewHeap {};

TEST_F(TestDelete, Increasing) {
	for (int i = 0; i <= 10; ++i) {
		_vacio.insert(i, i);
	}

	for (int i = 0; i <= 10; ++i) {
		ASSERT_EQ(_vacio.getMin()->getKey(), i);
		_vacio.deleteMin();
	}
}

TEST_F(TestDelete, Decreasing) {
	for (int i = 10; i >= 0; i--) {
		_vacio.insert(i, i);
	}

	for (int i = 0; i <= 10; ++i) {
		ASSERT_EQ(_vacio.getMin()->getKey(), i);
		_vacio.deleteMin();
	}
}

int main(int argc, char * argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
