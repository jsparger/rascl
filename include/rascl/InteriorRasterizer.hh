// #ifndef RASCL_INTERIOR_RASTERIZER_HH
// #define RASCL_INTERIOR_RASTERIZER_HH
//
// #include <boost/compute/core.hpp>
// #include "rascl/boost_compute_alias.hh"
// #include "rascl/Triangle.hh"
//
// namespace rascl {
//
// class InteriorRasterizer : public Painter
// {
// public:
// 	InteriorRasterizer(compute::command_queue queue);
// 	virtual ~InteriorRasterizer() {;}
// 	virtual void draw(Triangle triangle, float value);
// 	// TODO: add copy constructor that avoids recompiling kernels etc.
// protected:
// 	compute::command_queue queue;
// 	compute::program testCornersProgram, fillInteriorProgram;
// 	compute::kernel testCornersKernel, fillInteriorKernel;
//
// };
//
// } // namespace rascl
//
// #endif
