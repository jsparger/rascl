#ifndef RASCL_DETAIL_TEST_CORNERS_HH
#define RASCL_DETAIL_TEST_CORNERS_HH

#include <boost/compute/core.hpp>
#include <boost/compute/source.hpp>

namespace rascl {
namespace detail {
	
	const std::string kTestCorners(
	BOOST_COMPUTE_STRINGIZE_SOURCE(
		
		static float2 perp(float2 p)
		{
			p.y *= -1;
			return p;
		}
		
		static float trisign(float2 p1, float2 p2, float2 p3)
		{
			float2 u = p1-p3;
			float2 v = p2-p3;
			return dot(perp(u),v);
		}
		
		static float inside(global float2* triangle, float2 point)
		{
  		 	bool b1 = trisign(point, triangle[0], triangle[1]) < 0.0f;
  		 	bool b2 = trisign(point, triangle[1], triangle[2]) < 0.0f;
  		 	bool b3 = trisign(point, triangle[2], triangle[0]) < 0.0f;
			return ((b1 == b2) & (b2 == b3));
		}
		
		kernel void test_corners(global uint* corners, global float2* triangle, uint2 np, float2 origin, float2 pixelSize)
		{
			const uint2 id = {get_global_id(0), get_global_id(1)};
			const uint2 offset = {get_global_offset(0), get_global_offset(1)};
			const uint2 bbid = id - offset;
			if (!all(bbid < np)) {return;}
			
			// Do the calculation.
			const float2 pos = ((float2)id * pixelSize) + origin;
			const uint idx = bbid.y*np.x + bbid.x;
			corners[idx] = inside(triangle, pos);
		}
	)
	);
	
} // namespace detail 
} // namespace rascl 

#endif