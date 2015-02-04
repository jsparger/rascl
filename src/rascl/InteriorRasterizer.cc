// #include "rascl/InteriorRasterizer.hh"
// #include "rascl/detail/test_corners.hh"
// #include "rascl/detail/fill_interior.hh"
// #include <iostream>
//
// namespace rascl {
//
// InteriorRasterizer::
// InteriorRasterizer(compute::command_queue q)
// 	: queue(q)
// {
// 	// build testCorners kernel.
// 	try
// 	{
// 		testCornersProgram = compute::program::create_with_source(rascl::kTestCorners,queue.get_context());
// 		program.build();
// 		testCornersKernel = boost::compute::kernel(program,"testCorners");
// 	}
// 	catch (boost::compute::opencl_error &e)
// 	{
// 		std::cerr << program.build_log() << "\n";
// 		throw;
// 	}
//
// 	// build fillInterior kernel.
// 	try
// 	{
// 		fillInteriorProgram = compute::program::create_with_source(rascl::kFillInterior,queue.get_context());
// 		program.build();
// 		fillInteriorKernel = boost::compute::kernel(program,"fillInterior");
// 	}
// 	catch (boost::compute::opencl_error &e)
// 	{
// 		std::cerr << program.build_log() << "\n";
// 		throw;
// 	}
// }
//
// void
// InteriorRasterizer::
// draw(Triangle tri, float value)
// {
// 	// clip triangle by image.
// 	// compute bounding box.
// 	// set kernel args for testCorners.
// 	// enqueue nd-range testCorners.
// 	// set kernel args for fillInterior.
// 	// enqueue nd-range fillInterior.
// }
//
//
//
// } // namespace rascl
//
//
//
//
//
//
//
//
