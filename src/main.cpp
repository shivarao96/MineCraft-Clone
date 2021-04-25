#include <iostream>
#include "application/application.h"

//#ifdef __WIN64
//extern "C"
//{
//    //Enable dedicated graphics
//	declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}
//#endif // __WIN64

int main() {
	Application app("MineCraft Clone");
	app.runApp();
	return 0;
}