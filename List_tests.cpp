#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST(test_size) {
    List<int> list;
    list.push_back(1);
    list.push_back(5);
    list.push_back(10);
    list.push_back(20);

    ASSERT_EQUAL(list.size(), 4);
}

TEST(test_ctor) {
    List<int> emptyList;
    ASSERT_TRUE(emptyList.empty());

    List<int> list;
    list.push_back(1);
    ASSERT_FALSE(list.empty());
}

TEST(test_push_front) {
    List<int> list;
    list.push_front(2);
    list.push_front(4);
    list.push_front(6);
    list.push_front(8);
    list.push_front(10);

    ASSERT_EQUAL(list.front(), 10);
    ASSERT_EQUAL(list.back(), 2);
    ASSERT_EQUAL(list.size(), 5);
}

TEST(test_push_back) {
    List<int> list;
    list.push_back(2);
    list.push_back(4);
    list.push_back(6);
    list.push_back(8);
    list.push_back(10);

    ASSERT_EQUAL(list.front(), 2);
    ASSERT_EQUAL(list.back(), 10);
    ASSERT_EQUAL(list.size(), 5);
}

TEST(test_ront_and_back_1) {
    List<int> list;
    list.push_front(33);
    list.push_back(59);
    list.push_front(16);
    list.push_back(67);

    ASSERT_EQUAL(list.front(), 16);
    ASSERT_EQUAL(list.back(), 67);
    ASSERT_EQUAL(list.size(), 4);
}

TEST(test_pop_front) {
    List<int> list;
    list.push_front(11);
    list.push_back(19);
    list.push_front(23);
    list.push_back(30);
    list.push_front(1);

    list.pop_front();
    ASSERT_EQUAL(list.front(), 23);
    ASSERT_EQUAL(list.back(), 30);
    ASSERT_EQUAL(list.size(), 4);
}

TEST(test_pop_back) {
    List<int> list;
    list.push_front(11);
    list.push_back(19);
    list.push_front(23);
    list.push_back(30);
    list.push_front(1);

    list.pop_back();
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 19);
    ASSERT_EQUAL(list.size(), 4);
}

TEST(test_clear) {
    List<int> list;
    list.push_front(11);
    list.push_back(19);
    list.push_front(23);
    list.push_back(30);
    list.push_front(1);

    list.clear();
    ASSERT_TRUE(list.empty());
}

//for Iterator


TEST_MAIN()
