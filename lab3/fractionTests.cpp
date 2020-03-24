#include <iostream>
#include <gtest/gtest.h>

#include "fraction.h"

using namespace std;
using namespace ::testing;


struct FractionTester : ::testing::Test
{
};

TEST_F(FractionTester, constructionAndGettersSettersFunctions)
{
    { /// 1/2
        constexpr int numerator   = 1;
        constexpr int denominator = 2;

        const Fraction fraction(numerator, denominator);
        ASSERT_EQ(numerator, fraction.getNumerator());
        ASSERT_EQ(denominator, fraction.getDenominator());
    }

    { /// 4/1
        constexpr int numerator   = 4;
        constexpr int defaultDenominator = 1;

        const Fraction fraction(numerator);
        ASSERT_EQ(numerator, fraction.getNumerator());
        ASSERT_EQ(defaultDenominator, fraction.getDenominator());
    }

    { /// 3/4 -> 2/5
        constexpr int numerator1   = 3, numerator2   = 2;
        constexpr int denominator1 = 3, denominator2 = 5;

        Fraction fraction(numerator1, denominator1);
        ASSERT_EQ(numerator1, fraction.getNumerator());
        ASSERT_EQ(denominator1, fraction.getDenominator());

        fraction.setNumerator(numerator2);
        fraction.setDenominator(denominator2);
        ASSERT_EQ(numerator2, fraction.getNumerator());
        ASSERT_EQ(denominator2, fraction.getDenominator());
    }
}

TEST_F(FractionTester, fractionMultiplyWithoutReduction)
{
    constexpr int numerator1 = 1, denominator1 = 2;
    constexpr int numerator2 = 1, denominator2 = 3;
    constexpr int numeratorResult = 1, denominatorResult = 6;

    const Fraction fraction = Fraction(numerator1, denominator1) * Fraction(numerator2, denominator2);
    ASSERT_EQ(numeratorResult, fraction.getNumerator());
    ASSERT_EQ(denominatorResult, fraction.getDenominator());
}

TEST_F(FractionTester, fractionAdditionWithoutReduction)
{
    constexpr int numerator1 = 1, denominator1 = 2;
    constexpr int numerator2 = 1, denominator2 = 3;
    constexpr int numeratorResult = 5, denominatorResult = 6;

    const Fraction fraction = Fraction(numerator1, denominator1) + Fraction(numerator2, denominator2);
    ASSERT_EQ(numeratorResult, fraction.getNumerator());
    ASSERT_EQ(denominatorResult, fraction.getDenominator());
}

TEST_F(FractionTester, fractionThrowingWhenInvalidDenominator)
{
    constexpr int numerator = 1;
    constexpr int invalidDenominator = 0;

    ASSERT_THROW(Fraction(numerator, invalidDenominator), std::invalid_argument);

    Fraction fraction = Fraction(numerator);
    ASSERT_THROW(fraction.setDenominator(invalidDenominator), std::invalid_argument);
}

TEST_F(FractionTester, fractionReductionInArithmeticOperations)
{
    constexpr int numerator1 = 1, denominator1 = 3;
    constexpr int numerator2 = 2, denominator2 = 3;
    constexpr int numeratorResult = 1, denominatorResult = 1;

    const Fraction fraction = Fraction(numerator1, denominator1) + Fraction(numerator2, denominator2);
    ASSERT_EQ(numeratorResult, fraction.getNumerator());
    ASSERT_EQ(denominatorResult, fraction.getDenominator());
}
