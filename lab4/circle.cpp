#include "circle.h"

namespace Shapes
{

Circle::Circle(int x, int y, int r) :
		center(x, y),
		radius(r){

}

bool Circle::isIn(int x, int y) const{
	#define POW2(a) ((a)*(a)) //yeah, i know...
	return POW2(x - center.first) + POW2(y - center.second) <= POW2(radius);
	#undef POW2
}


}