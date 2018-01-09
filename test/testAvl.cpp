#include "testAvl.h"
#include <memory>

using namespace std;


TEST(AvlTest, RotateLeft_Test) {

    AvlTree tree;

    tree.addValue(10);
    tree.addValue(7);
    tree.addValue(12);
    tree.addValue(5);
    tree.addValue(8);
    //std::cout<<tree.print();
    EXPECT_EQ(tree.print(), "10, 7, 5, 8, 12, \n");
    /*
     *          10
     *         /  \
     *        7    12
     *      /  \
     *     5    8
     */

   tree.addValue(3);

    /*
     *          7
     *         /  \
     *        5    10
     *      /     /  \
     *     3     8    12
     */
    //std::cout<<tree.print();
    EXPECT_EQ(tree.print(), "7, 5, 3, 10, 8, 12, \n");
}
