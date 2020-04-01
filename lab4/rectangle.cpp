#include "rectangle.h"

namespace Shapes
{

Rectangle::Rectangle(int x, int y, int t_x, int t_y) :
		lower_left(x,y),
		upper_right(t_x, t_y){

}

bool Rectangle::isIn(int x, int y) const {
	if(x < lower_left.first || y < lower_left.second){
		return false;
	}

	if(x > upper_right.first || y > upper_right.second){
		return false;
	}

	return true;
}


} // namespace Shapes