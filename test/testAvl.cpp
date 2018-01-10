#include "testAvl.h"
#include <memory>

using namespace std;

TEST(AvlTest, EmptyTree_Test) {

    AvlTree tree;

    EXPECT_TRUE(tree.isEmpty());

    tree.addValue(10);

    EXPECT_FALSE(tree.isEmpty());
}

TEST(AvlTest, Search_and_Double_Rotate_Test) {

    AvlTree tree;

    EXPECT_FALSE(tree.searchValue(10));

    tree.addValue(10);
    tree.addValue(12);
    tree.addValue(17);
    tree.addValue(7);

    EXPECT_FALSE(tree.searchValue(9));
    tree.addValue(9);
    EXPECT_TRUE(tree.searchValue(9));

}

TEST(AvlTest, Add_Same_Test) {

    AvlTree tree;

    tree.addValue(18);
    tree.addValue(20);
    tree.addValue(8);
    tree.addValue(8);
    EXPECT_EQ(tree.print(), "18, 8, 20, \n");
}

TEST(AvlTest, RotateLeft_Test) {

    AvlTree tree;

    tree.addValue(10);
    tree.addValue(7);
    tree.addValue(12);
    tree.addValue(5);
    tree.addValue(8);
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
    EXPECT_EQ(tree.print(), "7, 5, 3, 10, 8, 12, \n");
}

TEST(AvlTest, RotateRight_Test) {

    AvlTree tree;

    tree.addValue(10);
    tree.addValue(12);
    tree.addValue(7);
    tree.addValue(11);
    tree.addValue(17);
    EXPECT_EQ(tree.print(), "10, 7, 12, 11, 17, \n");
    /*
     *          10
     *         /  \
     *        7    12
     *            /  \
     *           11    17
     */

    tree.addValue(20);

    /*
      *          12
      *         /  \
      *       10    17
      *      /  \    \
      *     7    11    20
      */
    EXPECT_EQ(tree.print(), "12, 10, 7, 11, 17, 20, \n");
}

TEST(AvlTest, Rotate_Double_Test) {

    AvlTree tree;

    tree.addValue(20);
    tree.addValue(10);
    tree.addValue(25);
    tree.addValue(5);
    tree.addValue(15);
    EXPECT_EQ(tree.print(), "20, 10, 5, 15, 25, \n");
    /*
     *          20
     *         /  \
     *        10    25
     *      /  \
     *     5    15
     */

    tree.addValue(12);

    /*
     *          20
     *         /  \
     *        10    25
     *      /  \
     *     5    15
     *         /
     *       12
     *
     * is going to be:
     *
     *          15
     *         /  \
     *        10    20
     *      /  \     \
     *     5    12    25
     */
    EXPECT_EQ(tree.print(), "15, 10, 5, 12, 20, 25, \n");
}
