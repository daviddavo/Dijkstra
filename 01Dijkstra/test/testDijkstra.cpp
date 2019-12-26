#include "gtest/gtest.h"
#include "dijkstra.h"

using namespace std;
using namespace dijkstra;

class TestDijkstra : public :: testing::Test {
protected:
    Graph _g0;
    Graph _g1;
    vertex_descriptor _v1[2];

    void SetUp() override {
        /* GRAPH _g1
         * v1 -(10)-> v2
         */
        _v1[0] = add_vertex(_g1);
        _v1[1] = add_vertex(_g1);
        add_edge(_v1[0], _v1[1], 10, _g1);
    }
};

TEST_F(TestDijkstra, OneEdge) {
    dijkstra_shortest(_g1, _v1[0]);
    hw();
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
