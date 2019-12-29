#include <iostream>
#include <memory>
#include "WarDrive.h"

using namespace std;
int main() {
	std::cout<<"HelloWorld";
	shared_ptr<WarDrive> t_pWarDrive(new WarDrive());
}


