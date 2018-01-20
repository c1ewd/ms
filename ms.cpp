// ms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <map>

#using namespace std;

class BaseConfig {

public:
	virtual void Config(int id, char *key, char *buf) {};
};

class BaseDevice {
public:
	virtual unsigned char *Query(unsigned char *buf, int *, int *) { return 0; };
	virtual void Request(unsigned char *, int) {};
};

class dse7320 : BaseDevice, BaseConfig {
public:
	void Config(int id, char *key, char *buf);
	int x;
};

void
dse7320::Config(int id, char *key, char *buf) {

}

class atysm6e : BaseDevice, BaseConfig {
public:
	void Config(int id, char *key, char *buf);
	int x;
};

void
atysm6e::Config(int id, char *key, char *buf) {

}

int main()
{
	BaseDevice* d = new BaseDevice;
//	device d;
	dse7320 *dse7320_obj = new dse7320;
//	dse7320 dse7320_obj;

	std::list<BaseDevice *> devices;
	devices.push_back(d);
	devices.push_back(d);
	
	map<std::string, BaseDevice*> devices;
	devices.i

	getchar();
    return 0;
}

