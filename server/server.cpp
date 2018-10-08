// server.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <boost\asio.hpp>
#include "stdafx.h"


using namespace std;

class BaseDevice {
private:
	string name;
public:
	inline void setName(string name) {
		this->name = name;
	}

	inline string getName() {
		return this->name;
	}
	
	virtual void Query() {
		//		cout << "BaseDevice::Query" << endl;
	}
};

class Device1 : public BaseDevice {
	void Query(void);
};

void Device1::Query(void) {
	cout << "Device1::Query" << endl;
}

class Device2 : public BaseDevice {
	void Query(void);
};

void Device2::Query(void) {
	cout << "Device2::Query" << endl;
}

int main(int argc, char* argv[]) {

	BaseDevice *d = new BaseDevice;
	Device1 *d1 = new Device1;
	Device2 *d2 = new Device2;

	d1->setName("FAKE DEVICE 1");
	d2->setName("FAKE DEVICE 2");

//	cout << d1->getName() << endl;
//	cout << d2->getName() << endl;

	list<BaseDevice *> devicesList;
	devicesList.push_back(d1);
	devicesList.push_back(d2);

	for (auto it = devicesList.begin(); it != devicesList.end(); it++) {
		cout << (*it)->getName() << endl;
//		(*it)->Query();
	}

	getchar();

    return 0;
}

