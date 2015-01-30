#ifndef RASCL_DETAIL_FILL_INTERIOR_HH
#define RASCL_DETAIL_FILL_INTERIOR_HH

#include <boost/compute/core.hpp>

namespace rascl {
namespace detail {
	
	const std::string kFillInterior(
	BOOST_COMPUTE_STRINGIZE_SOURCE(
		
		kernel void fill_interior(global float* image, global uint* corners, constant float value, constant uint2 np)
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
		
} // namespace detail 	
} // namespace rascl 

#endif