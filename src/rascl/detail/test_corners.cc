#include "rascl/detail/test_corners.hh"
#include <boost/compute/source.hpp>

namespace rascl {
namespace detail {
	
	const std::string kTestCorners::name = std::string("test_corners");
	
	const std::string kTestCorners::source = std::string(
	BOOST_COMPUTE_STRINGIZE_SOURCE(
		
		static float perpdot(const float2 u, const float2 v)
		{
			return dot((float2)(-u.y, u.x),v);
		}
		
		static float trisign(const float2 p1, const float2 p2, const float2 p3)
		{
			// this is equivalent to
			// return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
			return perpdot(p1-p3, p2-p3);
		}
		
		static float inside(constant float2* triangle, const float2 point)
		{
  		 	bool b1 = trisign(point, triangle[0], triangle[1]) < 0.0f;
  		 	bool b2 = trisign(point, triangle[1], triangle[2]) < 0.0f;
  		 	bool b3 = trisign(point, triangle[2], triangle[0]) < 0.0f;
			return ((b1 == b2) & (b2 == b3));
		}
		
		kernel void test_corners(global uint* corners, constant const float2* triangle, const uint2 np, const float2 origin, const float2 pixelSize)
		{
			const uint2 id = {get_global_id(0), get_global_id(1)};
			const uint2 offset = {get_global_offset(0), get_global_offset(1)};
			const uint2 bbid = id - offset;
			if (!all(bbid < np)) {return;}
			
			// Do the calculation.
			const float2 fid = convert_float2(id);
			const float2 pos = (fid * pixelSize) + origin;
			const uint idx = bbid.y*np.x + bbid.x;
			corners[idx] = (uint)inside(triangle, pos);
		}
	)
	);
	
} // namespace detail 
} // namespace rascl