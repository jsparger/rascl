#include "rascl/detail/focus_planes.hh"
#include <boost/compute/source.hpp>

namespace rascl {
namespace detail {
	
	const std::string kFocusPlanes::name = std::string("focus_planes");
	
	const std::string kFocusPlanes::source = std::string(
	BOOST_COMPUTE_STRINGIZE_SOURCE(
		
		kernel void focus_planes(global float* image, constant const float2* triangle, const uint2 np, const float2 origin, const float2 pixelSize, float value)
		{
			// get y coordinate
			const uint ix = get_global_id(0);
			const uint iy = get_global_id(1);
			
			if (ix >= np.x | iy >= np.y)
			{
				return;
			}
			
			uint index = iy*np.x + ix;
			float y = ((float)iy)*pixelSize.y;
			
			float2 tl = triangle[0];
			float2 tb = triangle[1];
			float2 tr = triangle[2];
			
			// calculate left and right pixel edge x-positions
			float leftSide = ((float)ix)*pixelSize.x + origin.x;
			float rightSide = leftSide + pixelSize.x;
			
			// calculate where left and right lines of simplified triangle intersect at this y coordinate.
			float leftPoint = tb.x + (tl.x-tb.x)/(tl.y-tb.y)*y;
			float rightPoint = tb.x + (tr.x-tb.x)/(tr.y-tb.y)*y;
			
			// to be even partially in the simplified triangle, this must be true.
			value = ((leftSide < rightPoint) & (rightSide > leftPoint)) ? value : 0;
			
			// clip the pixel by the triangle intersections.
			leftPoint = (leftSide > leftPoint) ? leftSide : leftPoint;
			rightPoint = (rightSide < rightPoint) ? rightSide : rightPoint;
			
			// assign the value.
			image[index] += value*(rightPoint - leftPoint)/pixelSize.x;
		}
	)
	);
	
} // namespace detail 
} // namespace rascl