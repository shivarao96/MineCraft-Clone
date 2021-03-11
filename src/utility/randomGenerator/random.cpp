#include "random.h"


RandomSingleton& RandomSingleton::get() {
	static RandomSingleton rs;
	return rs;
}

RandomSingleton::RandomSingleton() {
	m_randomEngine.seed(std::time(nullptr));
	for (int i = 0; i < 5; i++) {
		intInRange(i, i * 5);
	}
}