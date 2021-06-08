#include "sources/BinaryTree.hpp"
#include "doctest.h"
#include <iostream>
using namespace std;
using namespace ariel;

TEST_CASE("adding elements")
{
    BinaryTree<int> tri;
    //CHECK_THROWS(tri.add_left(4));
    CHECK_NOTHROW(tri.add_root(0));
    CHECK_NOTHROW(tri.add_root(3).add_root(6));
    CHECK_NOTHROW(tri.add_root(0));
    CHECK_NOTHROW(tri.add_left(0, 3).add_right(0, 6));

    CHECK_THROWS(tri.add_root('x'));
    CHECK_THROWS(tri.add_left(0, 'y'));
    CHECK_THROWS(tri.add_left('x', 3));

}
TEST_CASE("char")
{
    BinaryTree<char> trChar;
    CHECK_NOTHROW(trChar.add_root('m'));
    CHECK_NOTHROW(trChar.add_right('m', 'x'));
    CHECK_NOTHROW(trChar.add_right('x', 'y'));
}
// // TEST_CASE("Check char"){
// //     BinaryTree<char>tr;
// //     CHECK_THROWS(tr.add_right('x')); // dont have root yet
// //     CHECK_THROWS(tr.add_root('a'));
// //     CHECK_THROWS(tr.add_right('a','b'));
// //     CHECK_THROWS(tr.add_left('a','sc');


// // }



TEST_CASE("preorder")
{
    BinaryTree<int> tri_2;
    string res = "";
    CHECK_NOTHROW(tri_2.add_root(0));
    CHECK_NOTHROW(tri_2.add_left(0, 3).add_right(0, 5));
    CHECK_NOTHROW(tri_2.add_left(3, 5).add_right(3, 7));
    CHECK_NOTHROW(tri_2.add_left(5, 9).add_right(5, 6));
    for (auto itr = tri_2.begin_inorder(); itr != tri_2.end_inorder(); ++itr)
    {
        CHECK_NOTHROW(res += to_string(*itr) + " ");
    }
    CHECK(res == "0 3 5 7 5 9 6 ");
}

TEST_CASE("inorder")
{
    BinaryTree<int> tri_3;
    string res = "";
  CHECK_NOTHROW(tri_3.add_root(0));
    CHECK_NOTHROW(tri_3.add_left(0, 3).add_right(0, 5));
    CHECK_NOTHROW(tri_3.add_left(3, 5).add_right(3, 7));
    CHECK_NOTHROW(tri_3.add_left(5, 9).add_right(5, 6));
    for (auto itr = tri_3.begin_inorder(); itr != tri_3.end_inorder(); ++itr)
    {
        CHECK_NOTHROW(res += to_string(*itr) + " ");
    }
    CHECK(res == "5 3 7 0 9 5 6 ");
}

TEST_CASE("postorder")
{
    BinaryTree<int> tri_4;
    string res = "";
    CHECK_NOTHROW(tri_4.add_root(0));
    CHECK_NOTHROW(tri_4.add_left(0, 3).add_right(0, 5));
    CHECK_NOTHROW(tri_4.add_left(3, 5).add_right(3, 7));
    CHECK_NOTHROW(tri_4.add_left(5, 9).add_right(5, 6));
    for (auto itr = tri_4.begin_inorder(); itr != tri_4.end_inorder(); ++itr)
    {
        CHECK_NOTHROW(res += to_string(*itr) + " ");
    }
    CHECK(res == "5 7 3 0 9 6 5 ");
}