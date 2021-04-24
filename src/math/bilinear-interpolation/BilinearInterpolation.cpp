#include "BilinearInterpolation.h"

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
) {
	float width = xMax - xMin;
	float height = zMax - zMin;

	float xDistanceToMaxValue = xMax - x;
	float zDistanceToMaxValue = zMax - z;
	float xDistanceToMinValue = x - xMin;
	float zDistanceToMinValue = z - zMin;

	return 1.0f / (width * height) *
		(
			bottomLeft * xDistanceToMaxValue * zDistanceToMaxValue +
			bottomRight * xDistanceToMinValue * zDistanceToMaxValue +
			topLeft * xDistanceToMaxValue * zDistanceToMinValue +
			topRight * xDistanceToMinValue * zDistanceToMinValue
		);
}
