#include "test/InteriorKernelTest.hh"

#include "rascl/detail/test_corners.hh"
#include <boost/compute/core.hpp>
#include <boost/compute/container.hpp>
#include <chrono>

namespace compute = boost::compute;

typedef std::array<cl_float2, 3> Triangle;

Triangle make_triangle(cl_float2 a, cl_float2 b, cl_float2 c)
{
	return Triangle{{a,b,c}};
}

void testCorners()
{
	// some parameters
	std::string kernelSource = rascl::detail::kTestCorners::source;
	std::string kernelName = rascl::detail::kTestCorners::name;
	cl_uint initialValue = 7;
	// Triangle hostTriangle = make_triangle({0,0},{12.5,25},{25,0});
	Triangle hostTriangle = make_triangle({1,5},{10,1},{5,10});
	unsigned int npx = 25;
	unsigned int npy = 25;
	compute::uint2_ np = {npx,npy};
	compute::float2_ origin = {0,0};
	compute::float2_ pixelSize = {1.0,1.0};
	
	// get the device and set up context and command queue
	auto deviceList = boost::compute::system::devices();
	compute::device device  = deviceList[1];
	std::cout << "device name = " << device.name() << "\n";
	auto context = compute::context(device);
	auto queue = compute::command_queue(context,device);
	
	// create the host and device vectors.
	auto hostVec = std::vector<cl_uint>(npx*npy, 0);
	auto deviceVec =  compute::vector<cl_uint>(hostVec.size(), initialValue, queue);
	auto deviceTriangle = compute::vector<cl_float2>(hostTriangle.begin(),hostTriangle.end(),queue);
	
	// compile the kernel
	compute::program program;
	compute::kernel kernel;
	try
	{
		program = compute::program::create_with_source(kernelSource.c_str(), context);
		program.build("-w");
		kernel = compute::kernel(program,kernelName.c_str());
	}
	catch (...)
	{
		// build failed, print build log.
		std::cerr << "build failed! \n" << program.build_log() << std::endl;
		throw;
	}

	
	// set the kernel args
	kernel.set_arg(0, deviceVec);
	kernel.set_arg(1, deviceTriangle);
	kernel.set_arg(2, np);
	kernel.set_arg(3, origin);
	kernel.set_arg(4, pixelSize);

	// enqueue a kernel
	size_t nDims = 2;
	size_t globalWorkOffset[2] = {0,0};
	size_t globalWorkSize[2] = {npx,npy};
	size_t* localWorkSize = nullptr;
	
	using std::chrono::duration_cast;
	using std::chrono::nanoseconds;
	typedef std::chrono::high_resolution_clock clock;

	auto start = clock::now();
	
	int num = 1e6;
	for (int i = 0; i < num; ++i) {
	queue.enqueue_nd_range_kernel(
		kernel, nDims, globalWorkOffset, globalWorkSize, localWorkSize);
		if(i%1000 == 0) queue.finish(); 
	}

	queue.finish();
	
	auto end = clock::now();
	std::cout << duration_cast<nanoseconds>(end-start).count()/1e6 << "ms\n";
	std::cout << duration_cast<nanoseconds>(end-start).count()/1e3/num << "us per triangle\n";
	
	
	// copy device vector into host vector
	compute::copy(deviceVec.begin(), deviceVec.end(), hostVec.begin(), queue);

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