#include <string> // string, to_string()

#include <gtest/gtest.h>

#include "vector.h"


namespace
{
using namespace std;
using namespace ::testing;
}


class VectorTest : public ::testing::Test
{
};

TEST_F(VectorTest, constructor)
{
    {
        Vector v;
        const size_t expectedCapacity = 0;

        ASSERT_EQ(expectedCapacity, v.size());
        ASSERT_EQ(expectedCapacity, v.capacity());
    }

    {
        const size_t expectedSize = 0;
        const size_t expectedCapacity = 10;

        Vector v(expectedCapacity);

        ASSERT_EQ(expectedSize, v.size());
        ASSERT_EQ(expectedCapacity, v.capacity());
    }
}

TEST_F(VectorTest, destructOfNotEmptyVector)
{
    constexpr decltype(MyOwnMemoryManagement::deletions) expectedReallocations = 1;
    MyOwnMemoryManagement::deletions = 0;
    {
        const size_t expectedCapacity = 10;

        Vector v(expectedCapacity);
        ASSERT_EQ(expectedCapacity, v.capacity());
    }
    ASSERT_EQ(expectedReallocations, MyOwnMemoryManagement::deletions);
}

TEST_F(VectorTest, addingMultipleElementsWithoutReallocation)
{
    const Fraction fractions[] = { Fraction{1, 2}, Fraction{3, 4}, Fraction{5, 6} };
    constexpr size_t fractionCount = sizeof(fractions) / sizeof(fractions[0]);

    Vector v(fractionCount);
    for (size_t i=0; i<fractionCount; ++i)
    {
        v.push_back(fractions[i]);
        EXPECT_EQ(i+1, v.size());
        EXPECT_EQ(fractionCount, v.capacity());
    }
}

TEST_F(VectorTest, accessingWithIndexOperator)
{
    const Fraction fractions[] = { Fraction{1, 2}, Fraction{3, 4}, Fraction{5, 6} };
    constexpr size_t fractionCount = sizeof(fractions) / sizeof(fractions[0]);

    Vector v(fractionCount);
    for (size_t i=0; i<fractionCount; ++i)
    {
        v.push_back(fractions[i]);

        EXPECT_EQ(fractions[i].getNumerator(),   v[i].getNumerator());
        EXPECT_EQ(fractions[i].getDenominator(), v[i].getDenominator());
    }
}

TEST_F(VectorTest, copyAndMoveConstructor)
{
    const Fraction fractions[] = { Fraction{1, 2}, Fraction{3, 4}, Fraction{5, 6} };
    constexpr size_t fractionCount = sizeof(fractions) / sizeof(fractions[0]);

    Vector v(fractionCount);
    for (size_t i=0; i<fractionCount; ++i)
    {
        v.push_back(fractions[i]);
    }


    const Vector vCopied = v;
    ASSERT_EQ(fractionCount, vCopied.size());
    ASSERT_EQ(fractionCount, vCopied.capacity());
    for (size_t i=0; i<fractionCount; ++i)
    {
        EXPECT_EQ(fractions[i].getNumerator(),   vCopied[i].getNumerator());
        EXPECT_EQ(fractions[i].getDenominator(), vCopied[i].getDenominator());

        EXPECT_EQ(fractions[i].getNumerator(),   v[i].getNumerator());
        EXPECT_EQ(fractions[i].getDenominator(), v[i].getDenominator());
    }


    const Vector vMoved = std::move(v);
    constexpr size_t expectedCapacityAfterMoving = 0;
    EXPECT_EQ(expectedCapacityAfterMoving, v.size());
    EXPECT_EQ(expectedCapacityAfterMoving, v.capacity());
    ASSERT_EQ(fractionCount, vMoved.size());
    ASSERT_EQ(fractionCount, vMoved.capacity());

    for (size_t i=0; i<fractionCount; ++i)
    {
        EXPECT_EQ(fractions[i].getNumerator(),   vMoved[i].getNumerator());
        EXPECT_EQ(fractions[i].getDenominator(), vMoved[i].getDenominator());
    }
}
TEST_F(VectorTest, assignmentOperatorCopyingAndMoving)
{
    const Fraction fractions[] = { Fraction{1, 2}, Fraction{3, 4}, Fraction{5, 6} };
    constexpr size_t fractionCount = sizeof(fractions) / sizeof(fractions[0]);

    Vector v(fractionCount), v2, v3;
    for (size_t i=0; i<fractionCount; ++i)
    {
        v.push_back(fractions[i]);
    }


    v2 = v;
    ASSERT_EQ(fractionCount, v2.size());
    ASSERT_EQ(fractionCount, v2.capacity());
    for (size_t i=0; i<fractionCount; ++i)
    {
        EXPECT_EQ(fractions[i].getNumerator(),   v2[i].getNumerator());
        EXPECT_EQ(fractions[i].getDenominator(), v2[i].getDenominator());

        EXPECT_EQ(fractions[i].getNumerator(),   v[i].getNumerator());
        EXPECT_EQ(fractions[i].getDenominator(), v[i].getDenominator());
    }


    v3 = std::move(v);
    constexpr size_t expectedCapacityAfterMoving = 0;
    EXPECT_EQ(expectedCapacityAfterMoving, v.size());
    EXPECT_EQ(expectedCapacityAfterMoving, v.capacity());
    ASSERT_EQ(fractionCount, v3.size());
    ASSERT_EQ(fractionCount, v3.capacity());

    for (size_t i=0; i<fractionCount; ++i)
    {
        EXPECT_EQ(fractions[i].getNumerator(),   v3[i].getNumerator());
        EXPECT_EQ(fractions[i].getDenominator(), v3[i].getDenominator());
    }
}

TEST_F(VectorTest, accessingWithIndexOperatorOutOfRange)
{
    Vector v;
    ASSERT_THROW(v[v.size()], std::out_of_range);

    constexpr size_t expectedCapacity = 10;
    const Fraction fraction{1, 2};

    Vector v2(expectedCapacity);
    for (size_t i=0; i<expectedCapacity; ++i)
    {
        v2.push_back(fraction);

        ASSERT_NO_THROW(v2[i]);
    }
    ASSERT_THROW(v2[expectedCapacity+1], std::out_of_range);
}

TEST_F(VectorTest, addingElementsWithReallocationNecessairy)
{
    const Fraction fractions[] = { Fraction{1, 2}, Fraction{3, 4}, Fraction{5, 6} };
    constexpr size_t fractionCount = sizeof(fractions) / sizeof(fractions[0]);

    Vector v;
    for (size_t i=0; i<fractionCount; ++i)
    {
        v.push_back(fractions[i]);
        ASSERT_EQ(i+1, v.size());
        ASSERT_EQ(v.size(), v.capacity());
    }
}
