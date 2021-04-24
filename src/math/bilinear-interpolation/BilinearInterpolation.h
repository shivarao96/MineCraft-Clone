#pragma once


#ifndef __BILINEAR_INTERPOLATION__
#define __BILINEAR_INTERPOLATION__

float bilinearInterpolation(
	float bottomLeft,
	float bottomRight,
	float topLeft,
	float topRight,
	float xMax,
	float xMin,
	float zMax,
	float zMin,
	float x,
	float z
);

#endif // !__BILINEAR_INTERPOLATION__
