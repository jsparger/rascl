#ifndef RASCL_COORDINATE_HH
#define RASCL_COORDINATE_HH

namespace rascl {
	
template <typename T>
struct Coordinate
{
public:
	Coordinate(T xVal, T yVal)
	: 	x(xVal), y(yVal) {;}
	
	bool operator==(const Coordinate<T>& other)
	{
		bool value = ((x == other.x) && (y == other.y));
		return value;
	}
	
	bool operator!=(const Coordinate<T>& other)
	{
		return !(*this==other);
	}	
	
	T x;
	T y;
};

} // namespace rascl 


#endif