#include "shapecomposite.h"


namespace Shapes{

ShapeComposite::ShapeComposite(std::shared_ptr<Shape> shape1, std::shared_ptr<Shape> shape2, ShapeOperation operation) :
		shape1(shape1),
		shape2(shape2),
		operation(operation){
		
}

bool ShapeComposite::isIn(int x, int y) const{
	switch(operation){
		case ShapeOperation::SUM:
			return shape1->isIn(x, y) || shape2->isIn(x, y);
			break;
		
		case ShapeOperation::INTERSECTION:
			return shape1->isIn(x, y) && shape2->isIn(x, y);
			break;

		case ShapeOperation::DIFFERENCE:
			return shape1->isIn(x, y) && !shape2->isIn(x, y);
			break;
	}

	return false;
}






}