#include "testAvl.h"

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

TEST(AvlTest, Add_and_Search_after_double_rotate_Test) {

    AvlTree tree;

    tree.addValue(20);
    tree.addValue(10);
    tree.addValue(25);
    tree.addValue(5);
    tree.addValue(15);
    tree.addValue(12);

    EXPECT_TRUE(tree.searchValue(12));
    tree.addValue(22);
    EXPECT_TRUE(tree.searchValue(22));

    EXPECT_TRUE(tree.searchValue(20));
    EXPECT_TRUE(tree.searchValue(10));
    EXPECT_TRUE(tree.searchValue(25));
    EXPECT_TRUE(tree.searchValue(5));
    EXPECT_TRUE(tree.searchValue(15));

    EXPECT_FALSE(tree.searchValue(17));
}

TEST(AvlTest, Remove_Simple_Test) {

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

    tree.removeValue(15);
    EXPECT_EQ(tree.print(), "20, 10, 5, 25, \n");
    /*
     *          20
     *         /  \
     *        10    25
     *      /
     *     5
     */

    tree.removeValue(25);
    EXPECT_EQ(tree.print(), "10, 5, 20, \n");
    /*
     *          20
     *         /
     *        10
     *      /
     *     5
     * ->
     *
     *      10
     *     /  \
     *    5    20
     */

}

TEST(AvlTest, Remove_Root_Test) {

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

    tree.removeValue(20);

    EXPECT_EQ(tree.print(), "15, 10, 5, 25, \n");
    /*
     *          15
     *         /  \
     *        10    25
     *      /
     *     5
     */

}

TEST(AvlTest, Remove_Double_RightLeft_Test) {

    AvlTree tree;

    tree.addValue(20);
    tree.addValue(10);
    tree.addValue(25);
    tree.addValue(5);
    tree.addValue(15);
    tree.addValue(28);
    tree.addValue(13);
    EXPECT_EQ(tree.print(), "20, 10, 5, 15, 13, 25, 28, \n");
    /*
     *          20
     *         /  \
     *        10    25
     *      /  \     \
     *     5    15   28
     *         /
     *        13
     */

    tree.removeValue(5);
    EXPECT_EQ(tree.print(), "20, 13, 10, 15, 25, 28, \n");
    /*
     *          20
     *         /  \
     *        10    25
     *         \     \
     *          15   28
     *         /
     *        13
     * ->
     *
     *          20
     *         /  \
     *        10    25
     *         \     \
     *          13   28
     *           \
     *           15
     * ->
     *          20
     *         /  \
     *        13    25
     *       /  \    \
     *     10    15   28
     *
     */
}

TEST(AvlTest, Remove_Rotate_Left_Test) {
    AvlTree tree;

    tree.addValue(20);
    tree.addValue(10);
    tree.addValue(25);
    tree.addValue(5);
    tree.addValue(15);
    tree.addValue(28);
    tree.addValue(18);
    EXPECT_EQ(tree.print(), "20, 10, 5, 15, 18, 25, 28, \n");
    /*
     *          20
     *         /  \
     *        10    25
     *      /  \     \
     *     5    15    28
     *           \
     *           18
     */

    tree.removeValue(5);
    EXPECT_EQ(tree.print(), "20, 15, 10, 18, 25, 28, \n");
    /*
     *          20
     *         /  \
     *        10    25
     *         \     \
     *          15    28
     *           \
     *           18
     * ->
     *
     *          20
     *         /  \
     *        15    25
     *       /  \     \
     *     10    18    28
     */
}


TEST(AvlTest, Remove_Double_LeftRight_Test) {

    AvlTree tree;

    tree.addValue(20);
    tree.addValue(10);
    tree.addValue(25);
    tree.addValue(5);
    tree.addValue(23);
    tree.addValue(28);
    EXPECT_EQ(tree.print(), "20, 10, 5, 25, 23, 28, \n");
    tree.addValue(24);
    EXPECT_EQ(tree.print(), "20, 10, 5, 25, 23, 24, 28, \n");
    /*
     *          20
     *         /  \
     *        10    25
     *      /      /  \
     *     5     23    28
     *             \
     *             24
     */

    tree.removeValue(28);
    EXPECT_EQ(tree.print(), "20, 10, 5, 24, 23, 25, \n");
    /*
     *          20
     *         /  \
     *        10    25
     *      /      /
     *     5     23
     *            \
     *             24
     * ->
     *
     *          20
     *         /  \
     *        10    25
     *      /      /
     *     5     24
     *          /
     *        23
     * ->
     *          20
     *         /  \
     *        10    24
     *      /      /  \
     *     5     23    25
     *
     */
}

TEST(AvlTest, Remove_Rotate_Right_Test) {

    AvlTree tree;

    tree.addValue(20);
    tree.addValue(10);
    tree.addValue(25);
    tree.addValue(5);
    tree.addValue(23);
    tree.addValue(28);
    tree.addValue(21);
    EXPECT_EQ(tree.print(), "20, 10, 5, 25, 23, 21, 28, \n");
    /*
     *          20
     *         /  \
     *        10    25
     *      /      /  \
     *     5     23    28
     *           /
     *          21
     */

    tree.removeValue(28);
    EXPECT_EQ(tree.print(), "20, 10, 5, 23, 21, 25, \n");
    /*
     *          20
     *         /  \
     *        10    25
     *      /      /
     *     5     23
     *          /
     *         21
     * ->
     *
     *          20
     *         /  \
     *        10    23
     *      /      /  \
     *     5     21    25
     */
}

TEST(AvlTest, Remove_Between_Both_1_Test) {

    AvlTree tree;

    tree.addValue(20);
    tree.addValue(10);
    tree.addValue(25);
    tree.addValue(5);
    tree.addValue(23);
    tree.addValue(28);
    tree.addValue(21);
    EXPECT_EQ(tree.print(), "20, 10, 5, 25, 23, 21, 28, \n");
    /*
     *          20
     *         /  \
     *        10    25
     *      /      /  \
     *     5     23    28
     *           /
     *          21
     */

    tree.removeValue(25);

    EXPECT_EQ(tree.print(), "20, 10, 5, 23, 21, 28, \n");
    /*
     *          20
     *         /  \
     *        10    23
     *      /      /  \
     *     5     21    28
     */
}

TEST(AvlTest, Remove_Between_Both_2_Test) {

    AvlTree tree;

    tree.addValue(20);
    tree.addValue(10);
    tree.addValue(25);
    tree.addValue(5);
    tree.addValue(23);
    tree.addValue(28);
    tree.addValue(24);
    EXPECT_EQ(tree.print(), "20, 10, 5, 25, 23, 24, 28, \n");
    /*
     *          20
     *         /  \
     *        10    25
     *      /      /  \
     *     5     23    28
     *             \
     *              24
     */

    tree.removeValue(25);

    EXPECT_EQ(tree.print(), "20, 10, 5, 24, 23, 28, \n");
    /*
     *          20
     *         /  \
     *        10    24
     *      /      /  \
     *     5     23    28
     */
}