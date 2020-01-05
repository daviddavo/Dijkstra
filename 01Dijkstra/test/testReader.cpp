#include <sstream>
#include "gtest/gtest.h"
#include "graphReader.h"

using namespace std;

class TestReader : public :: testing::Test {
    protected:
        const char * _testnet1 = 
            "*vertices 3\n"
            "1 coso 0.3 0.2 1\n"
            "*arcs\n"
            "1 3 20\n"
            "1 2 50\n";
        const char * _testnet2 =
            "*vertices 3\n"
            "*arcs\n"
            "*edges\n"
            "1 3 20\n"
            "1 2 50";

        const char * _testnetlist1 =
            "*vertices 3\n"
            "*arcslist\n"
            "1 2 3\n";
            
        Graph<unsigned> _g1;
        Graph<unsigned> _g2;

        const char * _testcsv = 
            " ; 3; 2; 1\n"
            "3; 0; 0; 0\n"
            "2; 0; 0; 0\n"
            "1;20;50; 0\n";

        void SetUp() override {
            add_vertices(_g1, 3);
            add_edge(_g1, 1, 3, 20u);
            add_edge(_g1, 1, 2, 50u);

            add_vertices(_g2, 3);
            add_edge(_g2, 1, 2, 1u);
            add_edge(_g2, 1, 3, 1u);
        }
};

TEST_F(TestReader, NET1) {
    istringstream ss (_testnet1);
    unsigned cnt = 0;
    Graph<unsigned> g1;
    readNETGraph(ss, g1, cnt);
    ASSERT_FALSE(ss.fail());
    ASSERT_EQ(g1, _g1);
    ASSERT_EQ(cnt, 2);
}

TEST_F(TestReader, NET2) {
    istringstream ss (_testnet2);
    Graph<unsigned> g1;
    unsigned cnt = 0;
    readNETGraph(ss, g1, cnt);
    ASSERT_FALSE(ss.fail());
    ASSERT_EQ(g1, _g1);
    ASSERT_EQ(cnt, 2);
}

TEST_F(TestReader, CSV1) {
    stringstream ss (_testcsv);
    Graph<unsigned> g1;
    unsigned cnt = 0;
    readCSVGraph(ss, g1, cnt);
    ASSERT_EQ(g1, _g1);
    ASSERT_FALSE(ss.fail());
    ASSERT_EQ(cnt, 2);
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
