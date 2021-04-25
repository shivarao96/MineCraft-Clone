#pragma once
#ifndef __ARRAY_2D__
#define __ARRAY_2D__

#include <algorithm>
#include <array>

template<typename T, int WIDTH>
class Array2D
{
	using Array = std::array<T, WIDTH* WIDTH>;
public:
	Array2D() = default;
	T& getValAt(int x, int z);
	const T& getValAt(int x, int z)const noexcept;

	T& getMaxValue();
private:
	Array m_array2D;
};

#endif // !__ARRAY_2D__

template<typename T, int WIDTH>
inline T& Array2D<T, WIDTH>::getValAt(int x, int z)
{
	return m_array2D[x * WIDTH + z];
}

template<typename T, int WIDTH>
const T& Array2D<T, WIDTH>::getValAt(int x, int z) const noexcept
{
	return m_array2D[x * WIDTH + z];
}

template<typename T, int WIDTH>
T& Array2D<T, WIDTH>::getMaxValue()
{
	return *std::max_element(m_array2D.begin(), m_array2D.end());
}
