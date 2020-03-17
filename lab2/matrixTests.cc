#include <cstring> // strlen()

#include <iostream>
#include <sstream> // std::ostringstream
#include <gtest/gtest.h>

#include "matrix.h"

using namespace std;
using namespace ::testing;


namespace
{
constexpr size_t elementsInEachDimentions = 2;
} // namespace


struct MatrixTester : ::testing::Test
{
};

TEST_F(MatrixTester, constructionEmptyMatrix_expectedAllElementsAreZero)
{
    constexpr MatrixElement defaultValue = 0;

    const TwoDimensionMatrix m;
    static_assert (m.getSize() == elementsInEachDimentions, "Expected elements in each dimentions is 2!");

    for (size_t row=0; row<m.getSize(); ++row)
        for (size_t column=0; column<m.getSize(); ++column)
        {
            ASSERT_EQ(defaultValue, m.get(row, column)) << "row:" << row << " column:" << column;
        }
}

TEST_F(MatrixTester, constructionMatrixFromTwoDimensionArray_expectedAllElementsCopied)
{
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    TwoDimensionMatrix m(sourceMatrix);
    for (size_t row=0; row<m.getSize(); ++row)
        for (size_t column=0; column<m.getSize(); ++column)
        {
            ASSERT_EQ(sourceMatrix[row][column], m.get(row, column)) << "row:" << row << " column:" << column;
        }
}

TEST_F(MatrixTester, constructionMatrixFromAnotherMatrix_expectedAllElementsCopied)
{
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    const TwoDimensionMatrix m(sourceMatrix);
    TwoDimensionMatrix m2(m);
    for (size_t row=0; row<m.getSize(); ++row)
        for (size_t column=0; column<m.getSize(); ++column)
        {
            ASSERT_EQ(sourceMatrix[row][column], m2.get(row, column)) << "row:" << row << " column:" << column;
        }
}

TEST_F(MatrixTester, checkingOstreamOperator_expectedAllElementsInStream)
{
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    const TwoDimensionMatrix m(sourceMatrix);

    ostringstream stream;
    stream << m << endl;

    const string textFromStream = stream.str();

    for (size_t row=0; row<m.getSize(); ++row)
        for (size_t column=0; column<m.getSize(); ++column)
        {
            const string expectedElementInText = to_string(sourceMatrix[row][column]);
            const bool textFoundInStream = textFromStream.find(expectedElementInText) != string::npos;
            ASSERT_TRUE(textFoundInStream) << "Element " << expectedElementInText << " not found in stream!";
        }
}

TEST_F(MatrixTester, multiplicationMatrixMultipliedWithNumber_expectedAllElementsOfMatrixMultiplied)
{
    constexpr MatrixElement number2Multiply = 3;

    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    TwoDimensionMatrix m(sourceMatrix);

    m *= number2Multiply;

    for (size_t row=0; row<m.getSize(); ++row)
        for (size_t column=0; column<m.getSize(); ++column)
        {
            const auto expectedNumber = sourceMatrix[row][column] * number2Multiply;
            ASSERT_EQ(expectedNumber, m.get(row, column)) << "row:" << row << " column:" << column;
        }
}

TEST_F(MatrixTester, additionOfTwoMatrixes_expectedMatrixWithSumOfElementsReturned)
{
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };
    const MatrixElement sourceMatrix2[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 5, 6 },
        { 7, 8 }
    };

    const TwoDimensionMatrix m(sourceMatrix);
    const TwoDimensionMatrix m2(sourceMatrix2);
    const TwoDimensionMatrix mResult = m + m2;

    for (size_t row=0; row<m.getSize(); ++row)
        for (size_t column=0; column<m.getSize(); ++column)
        {
            const auto expectedNumber = sourceMatrix[row][column] + sourceMatrix2[row][column];
            EXPECT_EQ(expectedNumber, mResult.get(row, column)) << "row:" << row << " column:" << column;
        }
}

TEST_F(MatrixTester, andOfTwoMatrixes_expectedMatrixWithAllElementsAsResultOfLogicalAndReturned)
{
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 0,  0 },
        { -3, 9 }
    };
    const MatrixElement sourceMatrix2[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 0, 6 },
        { 0, -9 }
    };

    const TwoDimensionMatrix m(sourceMatrix);
    const TwoDimensionMatrix m2(sourceMatrix2);
    const TwoDimensionMatrix mResult = m && m2;

    for (size_t row=0; row<m.getSize(); ++row)
        for (size_t column=0; column<m.getSize(); ++column)
        {
            const auto expectedNumber = sourceMatrix[row][column] && sourceMatrix2[row][column];
            EXPECT_EQ(expectedNumber, mResult.get(row, column)) << "row:" << row << " column:" << column;
        }
}

TEST_F(MatrixTester, accessingMatrixByRowAndColumnWithIndexOperator_expectedSuccesfullAccess)
{
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    constexpr MatrixElement defaultValue = 0;

    TwoDimensionMatrix m;

    for (size_t row=0; row<m.getSize(); ++row)
        for (size_t column=0; column<m.getSize(); ++column)
        {
            ASSERT_EQ(defaultValue, m[row][column]) << "row:" << row << " column:" << column;

            m[row][column] = sourceMatrix[row][column];
            ASSERT_EQ(sourceMatrix[row][column], m[row][column]) << "row:" << row << " column:" << column;
        }
}

TEST_F(MatrixTester, matrixConverseOperatorIntoSizeType_expected2ReturnElementsInEachDimentions)
{
    const TwoDimensionMatrix m;

    const size_t valueFromConversion = static_cast<size_t>(m);

    ASSERT_EQ(elementsInEachDimentions, valueFromConversion);
}