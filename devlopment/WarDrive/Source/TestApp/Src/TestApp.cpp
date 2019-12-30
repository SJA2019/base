#include <iostream>
#include <memory>
#include "WarDrive.h"

using namespace std;
int main() {
	std::cout<<"HelloWorld"<<std::endl;
	shared_ptr<WarDrive> t_pWarDrive(new WarDrive());
}


