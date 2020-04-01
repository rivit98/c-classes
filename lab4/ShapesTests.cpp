#include <cmath>
#include <gtest/gtest.h>

#include "shape.h"
#include "rectangle.h"
#include "circle.h"

#if __has_include("shapecomposite.h")
    #include "shapecomposite.h"
#endif // #if __has_include("shapecomposite.h")

#if __has_include("stage.h")
    #include "stage.h"
    constexpr bool drawindStageImplemented = true;
#else
    constexpr bool drawindStageImplemented = false;
#endif // __has_include("stage.h")


namespace
{
using namespace std;
using namespace ::testing;

using Shapes::Shape;
using Shapes::Circle;
using Shapes::Rectangle;
#if __has_include("shapecomposite.h")
    using Shapes::ShapeComposite;
    using Shapes::ShapeOperation;
#endif // #if __has_include("shapecomposite.h")

typedef std::pair<int,int> Point;

#ifndef M_PI
    constexpr double M_PI = 3.1416926;
#endif

void printShape(const Shapes::Shape* shape, size_t width, size_t heigh)
{
    if constexpr(drawindStageImplemented)
    {
        const Stage stage(width, heigh);
        stage.drawShape2Stream(shape, std::cout);
    }
}
} // namespace


class RectangleTester : public ::testing::Test
{
};

TEST_F(RectangleTester, constructorOfRectangleStartingInBeginningOfCoordinateSystem)
{
    constexpr int xFrom = 0, yFrom = 0, xTo = 10, yTo = 10;
    const Rectangle rectangle(xFrom, yFrom, xTo, yTo);

    ASSERT_EQ(xFrom, rectangle.getX());
    ASSERT_EQ(yFrom, rectangle.getY());
    ASSERT_EQ(xTo, rectangle.getXTo());
    ASSERT_EQ(yTo, rectangle.getYTo());
}

TEST_F(RectangleTester, isInMethodOfRectangleStartingInBeginningOfCoordinateSystem)
{
    constexpr int xFrom = 0, xTo = 10;
    constexpr int yFrom = 0, yTo = 10;
    const Rectangle rectangle(xFrom, yFrom, xTo, yTo);

    ASSERT_TRUE(rectangle.isIn(5, 7));
    ASSERT_TRUE(rectangle.isIn(0, 0));
    ASSERT_TRUE(rectangle.isIn(10, 10));

    ASSERT_FALSE(rectangle.isIn(5, 11));
    ASSERT_FALSE(rectangle.isIn(50, 1));
    ASSERT_FALSE(rectangle.isIn(-1, 13));
}

TEST_F(RectangleTester, isInMethodOfRectangleStartingNotInBeginningOfCoordinateSystem)
{
    constexpr int xFrom = 5,  xTo = 15;
    constexpr int yFrom = 10, yTo = 20;
    const Rectangle rectangle(xFrom, yFrom, xTo, yTo);

    ASSERT_TRUE(rectangle.isIn(7, 17));
    ASSERT_TRUE(rectangle.isIn(5, 10));
    ASSERT_TRUE(rectangle.isIn(10, 20));

    ASSERT_FALSE(rectangle.isIn(6, 9));
    ASSERT_FALSE(rectangle.isIn(14, 21));
    ASSERT_FALSE(rectangle.isIn(-5, -20));
}


class CircleTester : public ::testing::Test
{
};

TEST_F(CircleTester, constructorOfCircleStartingInBeginningOfCoordinateSystem)
{
    constexpr int xCenter = 0, yCenter = 0, radius = 10;
    const Circle circle(xCenter, yCenter, radius);
    /**
     y
    10: ****
     9: ******
     8: *******
     7: ********
     6: *********
     5: **********
     4: **********
     3: ***********
     2: ***********
     1: ***********
     0: ***********
     0: 01234567890 x
     **/

    ASSERT_EQ(xCenter, circle.getX());
    ASSERT_EQ(yCenter, circle.getY());
    ASSERT_EQ(radius,  circle.getRadius());
}

TEST_F(CircleTester, isInMethodOfCircleStartingInBeginningOfCoordinateSystem)
{
    constexpr int xCenter = 0, yCenter = 0, radius = 10;
    const Circle circle(xCenter, yCenter, radius);
    /** circle:
     y
    10: ****
     9: ******
     8: *******
     7: ********
     6: *********
     5: **********
     4: **********
     3: ***********
     2: ***********
     1: ***********
     0: ***********
      : 01234567890 x **/

    ASSERT_TRUE(circle.isIn(5, 7));
    ASSERT_TRUE(circle.isIn(0, 0));

    constexpr auto angleInDegree = 45;
    constexpr auto angleInRadians = angleInDegree * M_PI / 180;
    const auto xyValueWhenHypothenuseEqualsRadius = floor(std::sin(angleInRadians) * radius);
    ASSERT_TRUE(circle.isIn(xyValueWhenHypothenuseEqualsRadius, xyValueWhenHypothenuseEqualsRadius));

    ASSERT_FALSE(circle.isIn(5,  11));
    ASSERT_FALSE(circle.isIn(11, 1));
    ASSERT_FALSE(circle.isIn(xyValueWhenHypothenuseEqualsRadius+1, xyValueWhenHypothenuseEqualsRadius+1));
}

TEST_F(CircleTester, isInMethodOfCircleStartingNotInBeginningOfCoordinateSystem)
{
    constexpr int xCenter = 6, yCenter = 7, radius = 5;
    const Circle circle(xCenter, yCenter, radius);

    /** circle:
      y
     12:     *****
     11:    *******
     10:   *********
      9:  ***********
      8:  ***********
      7:  ***********
      6:  ***********
      5:  ***********
      4:   *********
      3:    *******
      2:     *****
       : 012345678901 x */

    ASSERT_TRUE(circle.isIn(xCenter, 7));
    ASSERT_TRUE(circle.isIn(xCenter, yCenter+radius));
    ASSERT_TRUE(circle.isIn(xCenter+radius, yCenter));

    ASSERT_FALSE(circle.isIn(xCenter-radius,  yCenter-radius));
    ASSERT_FALSE(circle.isIn(xCenter+radius,  yCenter+radius));
}

#if __has_include("shapecomposite.h")
class ShapeCompositeTester : public ::testing::Test
{
};
TEST_F(ShapeCompositeTester, sumOfSqhareAndCircle)
{
    constexpr int xFrom = 2, xTo = 8;
    constexpr int yFrom = 0, yTo = 6;
    shared_ptr<Shape> rectangle(new Rectangle(xFrom, yFrom, xTo, yTo));
    /** (rectangle)
     y
     6:   *******
     5:   *******
     4:   *******
     3:   *******
     2:   *******
     1:   *******
     0:   *******
      : 012345678 x
     */

    constexpr auto squareXCenter = xFrom+(xTo-xFrom)/2, yCenter = yTo, radius = (xTo-xFrom)/2;
    shared_ptr<Shape> circle(new Circle(squareXCenter, yCenter, radius));
    /** circle:
     y
     9:     ***
     8:    *****
     7:   *******
     6:   *******
     5:   *******
     4:    *****
     3:     ***
     2:
     1:
     0:
      : 012345678
     */

    const ShapeComposite composite(rectangle, circle, ShapeOperation::SUM);
    /** circle + square:
     y
     9:     ***
     8:    *****
     7:   *******
     6:   *******
     5:   *******
     4:   *******
     3:   *******
     2:   *******
     1:   *******
     0:   *******
      : 012345678 x **/
    ASSERT_TRUE(composite.isIn(7, 6));
    ASSERT_TRUE(composite.isIn(squareXCenter, yTo+radius));
}

TEST_F(ShapeCompositeTester, intersectionOfSqhareAndCircle)
{
    constexpr int xFrom = 2, xTo = 8;
    constexpr int yFrom = 0, yTo = 6;
    shared_ptr<Shape> rectangle(new Rectangle(xFrom, yFrom, xTo, yTo));
    /** (rectangle)
     y
     6:   *******
     5:   *******
     4:   *******
     3:   *******
     2:   *******
     1:   *******
     0:   *******
      : 012345678 x
     */

    constexpr auto squareXCenter = xFrom+(xTo-xFrom)/2, yCenter = yTo, radius = (xTo-xFrom)/2;
    shared_ptr<Shape> circle(new Circle(squareXCenter, yCenter, radius));
    /** circle:
     y
     9:     ***
     8:    *****
     7:   *******
     6:   *******
     5:   *******
     4:    *****
     3:     ***
     2:
     1:
     0:
      : 012345678
     */

    const ShapeComposite composite(rectangle, circle, ShapeOperation::INTERSECTION);
    /** circle + square:
     y
     7:
     6:   *******
     5:   *******
     4:    *****
     3:     ***
     2:
     1:
     0:
      : 012345678 x **/
    ASSERT_TRUE(composite.isIn(xFrom, yTo));
    ASSERT_FALSE(composite.isIn(xFrom, yFrom));
}

TEST_F(ShapeCompositeTester, differenceOfSqhareAndCircle)
{
    constexpr int xFrom = 2, xTo = 8;
    constexpr int yFrom = 0, yTo = 6;
    shared_ptr<Shape> rectangle(new Rectangle(xFrom, yFrom, xTo, yTo));
    /** (rectangle)
     y
     6:   *******
     5:   *******
     4:   *******
     3:   *******
     2:   *******
     1:   *******
     0:   *******
      : 012345678 x
     */

    constexpr auto squareXCenter = xFrom+(xTo-xFrom)/2, yCenter = yTo, radius = (xTo-xFrom)/2;
    shared_ptr<Shape> circle(new Circle(squareXCenter, yCenter, radius));
    /** circle:
     y
     9:     ***
     8:    *****
     7:   *******
     6:   *******
     5:   *******
     4:    *****
     3:     ***
     2:
     1:
     0:
      : 012345678
     */

    const ShapeComposite composite(rectangle, circle, ShapeOperation::DIFFERENCE);
    /** circle + square:
     y
     5:
     4:   *     *
     3:   **   **
     2:   *******
     1:   *******
     0:   *******
      : 012345678 x **/
    ASSERT_FALSE(composite.isIn(xFrom, yTo));
    ASSERT_TRUE(composite.isIn(xFrom, yFrom));
}

TEST_F(ShapeCompositeTester, drawingHouse)
{
    constexpr int homeWidth = 20, homeHeigh = 10;
    constexpr int homeXFrom = 4, homeXTo = homeXFrom+homeWidth, homeYFrom = 1, homeYTo = homeYFrom + homeHeigh;
    shared_ptr<Shape> home(new Rectangle(homeXFrom, homeYFrom, homeXTo, homeYTo));

    constexpr int homeXCenter = homeXFrom + homeWidth/2, roofHeigh = homeWidth/2;
    shared_ptr<Shape> roof(new Circle(homeXCenter, homeYTo, roofHeigh));

    shared_ptr<Shape> homeWithRoof(new ShapeComposite(home, roof, ShapeOperation::SUM));

    constexpr int doorXFrom = homeXFrom + homeWidth/6, doorXTo = doorXFrom + homeWidth/4;
    constexpr int doorYFrom = homeYFrom + 1, doorYTo = doorYFrom + homeHeigh/2 + homeHeigh/3 + homeHeigh/4;
    shared_ptr<Shape> door(new Rectangle(doorXFrom, doorYFrom, doorXTo, doorYTo));

    shared_ptr<Shape> homeWithDoor(new ShapeComposite(homeWithRoof, door, ShapeOperation::DIFFERENCE));

    constexpr int doorWidth = doorXTo - doorXFrom, doorHeigh = doorYTo - doorYFrom;
    constexpr int windowXFrom = homeXTo - homeWidth/2 + doorWidth/2;
    constexpr int windowXTo = windowXFrom + doorWidth;
    constexpr int windowYFrom = doorYFrom + doorHeigh/2;
    constexpr int windowYTo = doorYTo;
    shared_ptr<Shape> window(new Rectangle(windowXFrom, windowYFrom, windowXTo, windowYTo));
    shared_ptr<Shape> homeWithDoorAndWindow(new ShapeComposite(homeWithDoor, window, ShapeOperation::DIFFERENCE));
//    printShape(homeWithDoorAndWindow.get(), homeXTo, homeYTo+roofHeigh);
    /** entire home:
     y
     21:            *******
     20:          ***********
     19:         *************
     18:        ***************
     17:       *****************
     16:      *******************
     15:      *******************
     14:     *********************
     13:     *********************
     12:     ***      ***      ***
     11:     ***      ***      ***
     10:     ***      ***      ***
      9:     ***      ***      ***
      8:     ***      ***      ***
      7:     ***      ***      ***
      6:     ***      ************
      5:     ***      ************
      4:     ***      ************
      3:     ***      ************
      2:     ***      ************
      1:     *********************
      0:
       : 0123456789012345678901234 x **/

    ASSERT_FALSE(homeWithDoorAndWindow->isIn(doorXFrom, doorYFrom));
    ASSERT_FALSE(homeWithDoorAndWindow->isIn(doorXTo, doorYTo));
    ASSERT_FALSE(homeWithDoorAndWindow->isIn(windowXFrom, windowYFrom));
    ASSERT_FALSE(homeWithDoorAndWindow->isIn(windowXTo, windowYTo));

    ASSERT_TRUE(homeWithDoorAndWindow->isIn(homeXFrom, homeYFrom));
    ASSERT_TRUE(homeWithDoorAndWindow->isIn(homeXTo, homeYTo));
}
#endif // #if __has_include("shapecomposite.h")
