#ifndef TEST_RASCL_INTERIOR_KERNEL_TEST
#define TEST_RASCL_INTERIOR_KERNEL_TEST

#include "rascl/detail/test_corners.hh"
#include <boost/compute/core.hpp>
#include <boost/compute/container.hpp>

namespace compute = boost::compute;

typedef std::array<cl_float2, 3> Triangle;

Triangle make_triangle(cl_float2 a, cl_float2 b, cl_float2 c)
{
	return Triangle{{a,b,c}};
}

void testCorners()
{
	// some parameters
	std::string source = rascl::detail::kTestCorners;
	cl_float initialValue = 0;
	Triangle hostTriangle = make_triangle({0,0},{35.6,50.2},{10.1,8});
	size_t npx = 50;
	size_t npy = 50;
	
	// get the device and set up context and command queue
	auto deviceList = boost::compute::system::devices();
	compute::device device  = deviceList[1];
	std::cout << "device name = " << device.name() << "\n";
	auto context = compute::context(device);
	auto queue = compute::command_queue(context,device);
	
	// create the host and device vectors.
	auto hostVec = std::vector<cl_float>(npx*npy, initialValue);
	auto deviceVec =  compute::vector<cl_float>(hostVec.size(), initialValue, queue);
	auto deviceTriangle = compute::vector<cl_float2>(hostTriangle.begin(),hostTriangle.end(),queue);
	
	// compile the kernel
	compute::program program;
	compute::kernel kernel;
	try
	{
		std::cerr << "got here \n";
		program = compute::program::create_with_source(source.c_str(), queue.get_context());
		std::cerr << "got here \n";
		program.build();
		std::cerr << "got here \n";
		kernel = compute::kernel(program,"test_corners");
	}
	catch (...)
	{
		// build failed, print build log.
		std::cerr << "build failed! \n" << program.build_log() << std::endl;
		throw;
	}

	// set the kernel args
	kernel.set_arg(0,deviceVec);
	kernel.set_arg(1,deviceTriangle);

	// enqueue a kernel
	size_t nDims = 2;
	size_t* globalWorkOffset = nullptr;
	size_t globalWorkSize[2] = {npx,npy};
	size_t* localWorkSize = nullptr;
	queue.enqueue_nd_range_kernel(
		kernel, nDims, globalWorkOffset, globalWorkSize, localWorkSize);

	// copy device vector into host vector
	compute::copy(deviceVec.begin(), deviceVec.end(), hostVec.begin());

	// print out image.
	for (size_t i = 0; i < npy; ++i)
	{
		for (size_t j = 0; j < npx; ++j)
		{
			std::cout << hostVec[i*npx+j] << " ";
		}
		std::cout << "\n";
	}
}



#endif