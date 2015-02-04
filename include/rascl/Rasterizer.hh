// #ifndef RASCL_RASTERIZER_HH
// #define RASCL_RASTERIZER_HH
//
// function which image can execute on itself
//
// 	here is a rasterizer. Here is a target image.
//
// rasterizer.doFoo(Triangle t, float value)
// {
//
// 	image.execute(foo);
// }
//
// simple_image.execute(foo)
// {
// 	foo(this);
// }
//
// complex_image.execute(foo)
// {
// 	for (auto& image : imageVec)
// 	{
// 		foo(image);
// 	}
// }
//
// #endif