#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

namespace Shapes
{
class Circle : public Shape
{
private:
	Point center;
	int radius;

public:
	Circle() = delete;
	Circle(int x, int y, int r);
	virtual ~Circle() = default;

	int getX() const { return center.first; };
	int getY() const { return center.second; };
	int getRadius() const { return radius; };

	virtual bool isIn(int x, int y) const override;
};
} // namespace Shapes

#endif // CIRCLE_H
