#pragma once

#include"../material/Material.h"

class ItemStack
{
public:
	ItemStack(const Material& material, int numInStack);
	int add(int count);
	void remove();
	const Material& getMaterial() const;
	int getNumInStack() const;
private:
	const Material* m_pMaterial = &Material::NOTHING;
	int m_numInStack = 0;
};

