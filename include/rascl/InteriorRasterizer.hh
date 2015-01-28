#ifndef RASCL_INTERIOR_RASTERIZER_HH
#define RASCL_INTERIOR_RASTERIZER_HH

namespace rascl {

class InteriorRasterizer
{
	static const std::string kTestCorners(
	BOOST_COMPUTE_STRINGIZE_SOURCE(
		
		static float2 perp(float2 p)
		{
			p.y *= -1;
			return p
		}
		
		static float trisign(float2 p1, float2 p2, float2 p3)
		{
			float2 u = p1-p3;
			float2 v = p2-p3;
			return dot(perp(u),v);
		}
		
		static float inside(global foat2* triangle, float2 point)
		{
  		 	bool b1 = trisign(p, triangle[0], triangle[1]) < 0.0f;
  		 	bool b2 = trisign(p, triangle[1], triangle[2]) < 0.0f;
  		 	bool b3 = trisign(p, triangle[2], triangle[0]) < 0.0f;
			return ((b1 == b2) & (b2 == b3));
		}
		
		kernel void testCorners(global uint* corners, global float2* triangle, constant uint2 np, constant float2 origin, constant float2 pixelSize, )
		{
			const uint2 id = {get_global_id(0), get_global_id(1)};
			const uint2 offset = {get_global_offset(0), get_global_offset(1)};
			const uint2 bbid = id - offset;
			if (!all(bbid < np)) {return;}
			
			// Do the calculation.
			const float2 pos = (id * pixelSize) + origin;
			const uint idx = bbid.y*np.x + bbid.x;
			corners[idx] = inside(triangle, pos);
		}
	)
	);
	
	static const std::string kFillInterior(
	BOOST_COMPUTE_STRINGIZE_SOURCE(
		
		kernel void fillInterior(global float* image, global uint* corners, constant float value, constant uint2 np)
		{
			const uint2 id = {get_global_id(0), get_global_id(1)};
			const uint2 offset = {get_global_offset(0), get_global_offset(1)};
			const uint2 bbid = id - offset;
			if (!all(bbid < np)) {return;}
			
			// TODO: check if all four corners of pixel inside box, if so add value
			const uint idx = bbid.y*np.x + bbid.x;
			bool interior = (corners[idx] & corners[idx + 1] & corners[idx + np.x] & corners[idx + np.x + 1]);
			// is a branch with a no-op better here than accessing memory? (i.e., which costs more, memory access or branch? I'm guessing memory access and this should be changed)
			image[IMAGE_INDEX] += (interior ? value:0);
			// TODO: Question: how can we move the corners into local memory efficiently and share? Each corner value will be used by four pixels.
		}
	)
	);
		
};

} // namespace rascl 

#endif
