#ifndef SHAPECOMPOSITE_H
#define SHAPECOMPOSITE_H

#include <memory>

#include "shape.h"

namespace Shapes
{
enum class ShapeOperation
{
    INTERSECTION,
    SUM,
    DIFFERENCE
};

class ShapeComposite : public Shape
{
    std::shared_ptr<Shape> shape1, shape2;
    ShapeOperation operation;

public:
    ShapeComposite(std::shared_ptr<Shape> shape1, std::shared_ptr<Shape> shape2, ShapeOperation operation);
	virtual ~ShapeComposite() = default;

    bool isIn(int x, int y) const override;
};
} // namespace Shapes

#endif // SHAPECOMPOSITE_H
