#include <sstream>
#include "gtest/gtest.h"
#include "graphReader.h"

using namespace std;

class TestReader : public :: testing::Test {
    protected:
        const char * _test1 = 
            "*vertices 2\n"
            "*arcs\n"
            "1 2 50\n";
        Graph<unsigned> _g1;

        const char * _testcsv = 
            ";2;1\n"
            "2;0;0\n"
            "1;50;0\n";

        void SetUp() override {
            add_vertex(_g1);
            add_vertex(_g1);
            add_edge(_g1, 1, 2, 50u);
        }
};

TEST_F(TestReader, Simple1) {
    stringstream ss (_test1);
    Graph<unsigned> g1;
    readGraph(ss, g1);
    ASSERT_EQ(g1, _g1);
}

TEST_F(TestReader, CSV1) {
    stringstream ss (_testcsv);
    Graph<unsigned> g1;
    readCSVGraph(ss, g1);
    ASSERT_EQ(g1, _g1);
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
