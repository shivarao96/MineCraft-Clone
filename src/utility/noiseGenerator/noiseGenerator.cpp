#include "noiseGenerator.h"
#include "../../world/worldConstant.h"
#include <cmath>
#include <iostream>

NoiseGenerator::NoiseGenerator(int seed)
	: m_seed(seed)
{
	m_noiseParameter.octaves      = 7;
	m_noiseParameter.amplitude    = 70;
	m_noiseParameter.smoothness   = 235;
	m_noiseParameter.heightOffset = -5;
	m_noiseParameter.roughNess    = 0.53;
}
double NoiseGenerator::getNoise(double x, double z) const {
	return getNoise(x + z * 57);
}
double NoiseGenerator::getNoise(int val) const {
	val += m_seed;
	val = (val << 13) ^ val;
	auto newN = (val * (val * val * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double)newN / 1073741824.0);
}
double NoiseGenerator::lerp(double a, double b, double z) const {
	double mu2 = (1 - std::cos(z * 3.14)) / 2;
	return (a * (1 - mu2) + b * mu2);
}
double NoiseGenerator::noise(double x, double z) const {
	double floorX = (double)((int)x);
	double floorZ = (double)((int)z);

	double s = 0,
		 t = 0,
		 u = 0,
		 v = 0;

	s = getNoise(floorX,         floorZ);
	t = getNoise(floorX + 1,     floorZ);
	u = getNoise(floorX,     floorZ + 1);
	v = getNoise(floorX + 1, floorZ + 1);

	auto rect1 = lerp(s, t,         x - floorX);
	auto rect2 = lerp(u, v,         x - floorX);
	auto rect3 = lerp(rect1, rect2, z - floorZ);

	return rect3;
}
double NoiseGenerator::getHeight(int x, int z, int chunkX, int chunkZ) const {
	auto newX = (x + (chunkX * CHUNK_SIZE));
	auto newZ = (z + (chunkZ * CHUNK_SIZE));
	if (newX < 0 || newZ < 0) {
		return WATER_LEVEL - 1;
	}
	auto totalValue = 0.0;

	for (auto a = 0; a < m_noiseParameter.octaves - 1; a++) {
		auto frequency = pow(2.0, a);
		auto amplitude = pow(m_noiseParameter.roughNess, a);
		totalValue += noise(
						((double)newX) * frequency / m_noiseParameter.smoothness, 
						((double)newZ) * frequency / m_noiseParameter.smoothness
					  ) * amplitude;
	}
	auto val = (((totalValue / 2.1) + 1.2) * m_noiseParameter.amplitude) + m_noiseParameter.heightOffset;
	return val > 0 ? val : 1;
}