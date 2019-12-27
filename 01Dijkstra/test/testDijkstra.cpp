#include "gtest/gtest.h"
#include "dijkstra.h"

using namespace std;

class TestDijkstra : public :: testing::Test {
protected:
    typedef vertex_descriptor vd;
    typedef edge_descriptor ed;

    Graph<unsigned> _g0;
    Graph<unsigned> _g1;

    void SetUp() override {
        add_vertex(_g1, "v1");
        add_vertex(_g1, "v2");
        add_edge(_g1, 1, 2);
    }
};

TEST_F(TestDijkstra, Invalid) {
    EXPECT_THROW(dijkstra(_g0, 0), range_error);
}

TEST_F(TestDijkstra, TwoNodes) {
    auto ret = dijkstra(_g1, _g1[1]); 
    for (int i = 0; i < ret.size(); ++i) {
        printf("W: %d, Path: %d\n", ret[i].first, ret[i].second);
    }
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
