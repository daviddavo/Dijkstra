#include "gtest/gtest.h"
#include "dijkstra.h"

using namespace std;

class TestDijkstra : public :: testing::Test {
protected:
    using tSol = std::vector<std::pair<unsigned, vertex_descriptor>> ; 
    typedef vertex_descriptor vd;
    typedef edge_descriptor ed;

    static const unsigned MAX_W = numeric_limits<unsigned>::max();

    Graph<unsigned> _g0;
    Graph<unsigned> _g1;
    tSol _sol1;
    Graph<unsigned> _g2;
    tSol _sol21;
    tSol _sol23;

    void SetUp() override {
        add_vertex(_g1, "v1");
        add_vertex(_g1, "v2");
        add_edge(_g1, 1, 2, 100u);
        _sol1 = {
            make_pair(MAX_W,0),
            make_pair(0,0),
            make_pair(100, 1)
        };

        add_vertex(_g2, "v1");
        add_vertex(_g2, "v2");
        add_vertex(_g2, "v3");
        add_edge(_g2, 1, 2, 500u);
        add_edge(_g2, 1, 3, 100u);
        add_edge(_g2, 3, 2, 50u);

        _sol21 = {
            make_pair(MAX_W, 0),
            make_pair(0, 0),
            make_pair(150, 3),
            make_pair(100, 1)
        };

        _sol23 = {
            make_pair(MAX_W, 0),
            make_pair(MAX_W, 0),
            make_pair(50, 3),
            make_pair(0, 0)
        };
    }
};

TEST_F(TestDijkstra, Invalid) {
    EXPECT_THROW(dijkstra(_g0, 0), range_error);
}

TEST_F(TestDijkstra, TwoNodes) {
    auto ret = dijkstra(_g1, _g1[1]); 
    for (int i = 0; i < ret.size(); ++i) {
        ASSERT_EQ(ret[i], _sol1[i]);
    }
}

TEST_F(TestDijkstra, ThreeNodes) {
    auto ret = dijkstra(_g2, _g2[1]);
    for (int i = 0; i < ret.size(); ++i) {
        ASSERT_EQ(ret[i], _sol21[i]);
    }

    ret = dijkstra(_g2, _g2[3]);
    for (int i = 0; i < ret.size(); ++i) {
        ASSERT_EQ(ret[i], _sol23[i]);
    }
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
