#include "test/InteriorKernelTest.hh"

int main()
{
	testCorners();
	return 0;
}

// int main()
// {
// 	npx = 200; npy = 100;
// 	dx = 0.5; dy = 1;
// 	ox = 0; oy = 0;
// 	rascl::Image image(npx, npy, dx, dy, ox, oy)
// 	rascl::Rasterizer r;
// 	rascl::OtherRasterizer r2;
// 	const rascl::Painter& p = image.painter(r);
// 	const rascl::Painter& p2 = image.painter(r2);
//
// 	Point p1 = {10.5, 10.5};
// 	Point p2 = {20, 20};
// 	Point p3 = {30.7, 10};
// 	value = 10.3;
// 	rascl::Triangle triangle(p1, p2, p3);
//
// 	p.draw(triangle, value);
//
//
// }