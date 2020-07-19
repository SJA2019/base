#include <iostream>
#include <memory>
#include <SDL.h>
#include "WarDrive.h"

using namespace std;
int main() {
	std::cout<<"Starting war drive..."<<std::endl;
	shared_ptr<WarDrive> t_pWarDrive(new WarDrive());
	t_pWarDrive->Run();
	std::cout<<"War drive completed."<<std::endl;
}
