#include "ItemStack.h"
#include <algorithm>
#include <iostream>

ItemStack::ItemStack(const Material& material, int numInStack)
	: m_pMaterial(&material)
	,m_numInStack(numInStack)
{}

int ItemStack::add(int count) {
	m_numInStack += count;
	if (m_numInStack > m_pMaterial->maxStack) {
		const int leftover = m_numInStack - m_pMaterial->maxStack;
		m_numInStack = m_pMaterial->maxStack;
		return leftover;
	}	
	else {
		return 0;
	}
}

void ItemStack::remove() {
	m_numInStack--;
	if (m_numInStack < 0) {
		m_numInStack = 0;
	}
}

const Material& ItemStack::getMaterial() const {
	return *m_pMaterial;
}
int ItemStack::getNumInStack() const {
	return m_numInStack;
}