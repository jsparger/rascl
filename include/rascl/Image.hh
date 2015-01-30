#ifndef RASCL_IMAGE_HH
#define RASCL_IMAGE_HH

#include <boost/compute/core.hpp>
#include "rascl/boost_compute_alias.hh"
#include <vector>

namespace rascl {

struct ImageParams
{
	unsigned int npx, npy;
	double x0, y0;
	double dx, dy;
	
};

class Image
{
public:
	Image(compute::command_queue queue, ImageParams params);
	Image(compute::command_queue queue, ImageParams params, std::vector<float> initial);
	virtual ~Image() {;}
	virtual std::vector<float> contents();
	virtual const compute::vector<float>& deviceVector():
		
protected:
	virtual void push();
	virtual void pull();
	
	compute::command_queue queue;
	ImageParams params;
	std::vector<float> hostVec;
	compute::vector<float> deviceVec;
};
	
} // namespace rascl 


#endif