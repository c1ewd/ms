// ms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>

using namespace std;

class BaseDevice {
};

class Device1 : public BaseDevice {
};

class Device2 : public BaseDevice {
};

int main()
{
	Device1* d1 = new Device1;
	Device2* d2 = new Device2;

	map<std::string, BaseDevice*> devices;
	devices.insert(make_pair("1", d1));
	devices.insert(make_pair("2", d2));

	getchar();
    return 0;
}

