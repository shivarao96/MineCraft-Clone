#pragma once

struct NoiseParameters {
	int octaves;
	int amplitude;
	int smoothness;
	int heightOffset;
	double roughNess;
};

class NoiseGenerator
{
public:
	NoiseGenerator(int seed);
	double getHeight(int x, int z, int chunkX, int chunkZ) const;
	void setNoiseParameter(const NoiseParameters& noiseParameters);
private:
	double getNoise(double x, double z) const;
	double getNoise(int val) const;
	double lerp(double a, double b, double z) const;
	double noise(double x, double z) const;

	NoiseParameters m_noiseParameter;
	int m_seed;
};

