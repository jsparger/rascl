// #ifndef RASCL_BASIC_IMAGE_HH
// #define RASCL_BASIC_IMAGE_HH
//
// #include "rascl/Image.hh"
//
// namespace rascl {
//
// struct ImageParams
// {
// 	unsigned int npx, npy;
// 	double x0, y0;
// 	double dx, dy;
//
// };
//
// class BasicImage : public Image
// {
// public:
// 	BasicImage(compute::command_queue queue, ImageParams params);
// 	BasicImage(compute::command_queue queue, ImageParams params, std::vector<float> initial);
// 	virtual ~BasicImage() {;}
// 	virtual std::vector<float> contents() override;
// 	virtual const compute::vector<float>& deviceVector() override;
// 	virtual const Painter& painter(Style& r) override;
//
// protected:
// 	virtual void push();
// 	virtual void pull();
//
// 	compute::command_queue queue;
// 	ImageParams params;
// 	std::vector<float> hostVec;
// 	compute::vector<float> deviceVec;
// };
//
// } // namespace rascl
//
// #endif