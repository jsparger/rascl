#include "racl/Image.hh"

namespace rascl {

Image::Image(compute::command_queue q, ImageParams p, std::vector<float> initial)
	: queue(q), params(p), hostVec(initial), deviceVec(hostVec.size(), q.get_context()),
{
	push();
}

Image::Image(compute::command_queue queue, ImageParams params)
	: Image(queue, params, std::vector<float>(p.npx*p.npy,0))
{
	// do nothing else
}

void 
Image::push()
{
	compute::copy(
		hostVec.begin(), hostVec.end(), deviceVec.begin(), queue
	);
}

void 
Image::pull()
{
	compute::copy(
		deviceVec.begin(), deviceVec.end(), hostVec.begin(), queue
	);
}

std::vector<float> 
Image::contents()
{
	pull();
	return hostVec;
}

const compute::vector&
deviceVector()
{
	return deviceVec;
}
	
} // namespace rascl 















