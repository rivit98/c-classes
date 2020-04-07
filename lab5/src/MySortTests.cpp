#include <iostream>
#include <vector>
#include <algorithm> // count_if
#include <type_traits> // is_same<>
#include <cctype> // isspace
#include <gtest/gtest.h>
#include "mySorting.h"
#include "mylist.h"

namespace
{
using namespace std;
using namespace ::testing;
} // namespace

class MySortTester : public ::testing::Test
{
};

TEST_F(MySortTester, sortingStaticArray)
{
    int values[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    int sortedValues[std::size(values)];
    std::copy(begin(values), end(values), begin(sortedValues));
    std::sort(begin(sortedValues), end(sortedValues));

    mySort(values);
    for (size_t i=0; i<std::size(values); ++i)
    {
        EXPECT_EQ(sortedValues[i], values[i]) << "i=" << i;
    }
}

TEST_F(MySortTester, sortingContainer)
{
    vector<int> values = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    decltype(values) sortedValues;
    std::copy(begin(values), end(values), back_inserter(sortedValues));
    std::sort(begin(sortedValues), end(sortedValues));

    mySort(values);
    for (size_t i=0; i<std::size(values); ++i)
    {
        EXPECT_EQ(sortedValues[i], values[i]) << "i=" << i;
    }
}

TEST_F(MySortTester, sortingMyList)
{
    const vector<int> sortedValues = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    MyList<int> l;
    std::copy(begin(sortedValues), end(sortedValues), front_inserter(l));

    mySort(l);

    auto it = sortedValues.cbegin();
    for (auto v : l)
    {
        EXPECT_EQ(*it, v) << "index = " << distance(sortedValues.cbegin(), it);
        ++it;
    }
}

TEST_F(MySortTester, sortingConstCharPtrAllUpperCases)
{
    char randomGermanNames[][20] = { "MARLON", "OLAF", "MANFRED", "URS", "THEOPHILUS", "TORSTEN", "UDO", "MORITZ", "VIET", "RAINER", "OLIVER", "OSCAR", "WILBUR", "OLE", "YANNICK", "ZOLTHAR", "OSKAR", "UWE", "XAVER", "WIM", "MALTE", "RUDI", "OLLI", "WILMAR", "PASCAL", "OTTO", "MARTIN", "NOAH", "ULLI", "MIKA", "SVEN", "TORBEN", "WILFRIED", "MATHIS", "WILIBALD", "ROLF", "WILHELM", "MARVIN", "WALTER", "WOLF", "WILLY", "NIELS", "MADS", "MATTHIAS", "TEO", "VOLKER", "ROTGIER" };
    constexpr char sortedGermanNames[][20] = { "MADS", "MALTE", "MANFRED", "MARLON", "MARTIN", "MARVIN", "MATHIS", "MATTHIAS", "MIKA", "MORITZ", "NIELS", "NOAH", "OLAF", "OLE", "OLIVER", "OLLI", "OSCAR", "OSKAR", "OTTO", "PASCAL", "RAINER", "ROLF", "ROTGIER", "RUDI", "SVEN", "TEO", "THEOPHILUS", "TORBEN", "TORSTEN", "UDO", "ULLI", "URS", "UWE", "VIET", "VOLKER", "WALTER", "WILBUR", "WILFRIED", "WILHELM", "WILIBALD", "WILLY", "WILMAR", "WIM", "WOLF", "XAVER", "YANNICK", "ZOLTHAR" };

    mySort(randomGermanNames);

    for (size_t i=0; i<size(randomGermanNames); ++i)
    {
        EXPECT_STREQ(sortedGermanNames[i], randomGermanNames[i]) << "index = " << i;
    }
}

TEST_F(MySortTester, sortingConstCharPtrIgnoreCases)
{
    char words[][20] = { "Bazyli", "lubi", "Malfreda", "ktorego", "poznal", "u", "Stoigniewa", "stojacego", "przy", "barze", "mamy" };
    constexpr char sortedWords[][20] = { "barze", "Bazyli", "ktorego", "lubi", "Malfreda", "mamy", "poznal", "przy", "Stoigniewa", "stojacego", "u" };

    mySort(words);

    for (size_t i=0; i<size(words); ++i)
    {
        EXPECT_STREQ(sortedWords[i], words[i]) << "index = " << i;
    }
}
