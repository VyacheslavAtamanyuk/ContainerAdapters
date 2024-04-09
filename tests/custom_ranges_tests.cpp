#include "lib/custom_ranges.h"
#include <gtest/gtest.h>
#include <vector>
#include <forward_list>
#include <list>
#include <map>
#include <set>

TEST(CustomRangesSuite, DropTest) {
    std::vector<int> object{1, 56, 52, 228, 57};

    bool is_empty = true;
    for (auto i: object | drop(1) | drop(1) | drop(1) | drop(2)) {
        is_empty = false;
    }

    int last_el;
    for (auto i: object | drop(2) | reverse() | drop(2)) {
        last_el = i;
    }

    ASSERT_TRUE(is_empty);
    ASSERT_EQ(last_el, 52);
}

TEST(CustomRangesSuite, TakeTest) {
    std::forward_list<int> object{2, 56, 23, 34, 239};

    int last_el;
    for (auto i: object | take(4) | take(3) | take(2) | take(1)) {
        last_el = i;
    }

    int transformed_el;
    for (auto i: object | transform([] (int i) {return i*i;}) | take(1)) {
        transformed_el = i;
    }

    ASSERT_EQ(last_el, 2);
    ASSERT_EQ(transformed_el, 4);
}

TEST(CustomRangesSuite, ReverseTest) {
    std::list<int> object{1, 23, 52, 26, 423};

    int filtered_el;
    for (auto i: object | reverse() | filter([] (int i) {return i % 2 == 0;}) | take(1)) {
        filtered_el = i;
    }

    int reversed_twice_el;
    for (auto i: object | reverse() | reverse() | take(1)) {
        reversed_twice_el = i;
    }

    ASSERT_EQ(filtered_el, 26);
    ASSERT_EQ(reversed_twice_el, 1);
}

TEST(CustomRangesSuite, FilterTest) {
    const std::vector<int> object1{1, 56, 2346, 123, 279, 59, 7, 9};

    std::vector<int> nums_divisible_by_9;
    for (auto i: object1 | filter ([] (int i) {return i % 9 == 0;})) {
        nums_divisible_by_9.push_back(i);
    }

    std::list<int> object2{1, -1, 2, -2, 3, -3};

    std::set<int> unique_elements;
    for (auto i: object2 | filter([&unique_elements] (int i) {return unique_elements.find(abs(i)) == unique_elements.end();})) {
        unique_elements.insert(i);
    }

    ASSERT_EQ(nums_divisible_by_9[0], 279);
    ASSERT_EQ(nums_divisible_by_9[1], 9);
    ASSERT_EQ(unique_elements.size(), 3);
    ASSERT_TRUE(unique_elements.find(1) != unique_elements.end());
    ASSERT_TRUE(unique_elements.find(2) != unique_elements.end());
    ASSERT_TRUE(unique_elements.find(3) != unique_elements.end());
}

TEST(CustomRangesSuite, TransformTest) {
    const std::vector<int> object1{1, 2, 3};

    std::vector<int> negative_numbers;
    for (auto i: object1 | transform([] (int i) {return -i;})) {
        negative_numbers.push_back(i);
    }

    std::vector<int> object2{23, 52, 228, 239, 447};

    int scalar_multiplication = 0;
    int counter = 0;
    for (auto i: object2 | filter([] (int i) {return i % 2 == 1;}) | transform([&] (int i) {return object1[counter++] * i;})) {
        scalar_multiplication += i;
    }

    ASSERT_EQ(negative_numbers[0], -1);
    ASSERT_EQ(negative_numbers[1], -2);
    ASSERT_EQ(negative_numbers[2], -3);
    ASSERT_EQ(scalar_multiplication, 23*1 + 239*2 + 447*3);
}

TEST(CustomRangesSuite, KeyValuesTest) {
    std::map<int, int> object1{{2, 5}, {5, 2}, {77, 35}, {456, 457}};

    std::vector<int> map_keys;
    for (auto i: object1 | keys()) {
        map_keys.push_back(i);
    }

    std::vector<int> map_values;
    for (auto i: object1 | values()) {
        map_values.push_back(i);
    }

    std::vector<int> filtered_keys;
    for (auto i: object1 | keys() | reverse() | filter([] (int i) {return i >= 77;})) {
        filtered_keys.push_back(i);
    }

    int counter = 0;
    int scalar_multiplication = 0;
    for (auto i: object1 | values() | transform([&] (int i) {return map_keys[counter++] * i;})) {
        scalar_multiplication += i;
    }

    ASSERT_EQ(map_keys[0], 2);
    ASSERT_EQ(map_keys[1], 5);
    ASSERT_EQ(map_keys[2], 77);
    ASSERT_EQ(map_keys[3], 456);
    ASSERT_EQ(map_values[0], 5);
    ASSERT_EQ(map_values[1], 2);
    ASSERT_EQ(map_values[2], 35);
    ASSERT_EQ(map_values[3], 457);
    ASSERT_EQ(filtered_keys[0], 456);
    ASSERT_EQ(filtered_keys[1], 77);
    ASSERT_EQ(scalar_multiplication, 2*5 + 5*2 + 77*35 + 456*457);
}