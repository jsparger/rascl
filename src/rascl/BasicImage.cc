// #include "racl/BasicImage.hh"
//
// namespace rascl {
//
// BasicImage::BasicImage(compute::command_queue q, BasicImageParams p, std::vector<float> initial)
// 	: queue(q), params(p), hostVec(initial), deviceVec(hostVec.size(), q.get_context()),
// {
// 	push();
// }
//
// BasicImage::BasicImage(compute::command_queue queue, BasicImageParams params)
// 	: BasicImage(queue, params, std::vector<float>(p.npx*p.npy,0))
// {
// 	// do nothing else
// }
//
// void
// BasicImage::push()
// {
// 	compute::copy(
// 		hostVec.begin(), hostVec.end(), deviceVec.begin(), queue
// 	);
// }
//
// void
// BasicImage::pull()
// {
// 	compute::copy(
// 		deviceVec.begin(), deviceVec.end(), hostVec.begin(), queue
// 	);
// }
//
// std::vector<float> &
// BasicImage::contents()
// {
// 	pull();
// 	return hostVec;
// }
//
// const compute::vector&
// BasicImage::deviceVector()
// {
// 	return deviceVec;
// }
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
//
//
//
//
//
//
//
