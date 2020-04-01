#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

namespace Shapes
{
class Rectangle : public Shape
{
private:
	Point lower_left;
	Point upper_right;
	
public:
	Rectangle() = delete;
	Rectangle(int x, int y, int t_x, int t_y);
	virtual ~Rectangle() = default;

	int getX() const { return lower_left.first; };
	int getY() const { return lower_left.second; };
	int getXTo() const { return upper_right.first; };
	int getYTo() const { return upper_right.second; };

	virtual bool isIn(int x, int y) const override;
};
} // namespace Shapes

#endif // RECTANGLE_H
