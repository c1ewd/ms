// server.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <boost\asio.hpp>

#include <boost\bind.hpp>
#include <boost\smart_ptr.hpp>
#include <boost\asio.hpp>
#include <boost\thread\thread.hpp>

//#include <common\protocol.hpp>


#include "stdafx.h"

using namespace std;

using boost::asio::ip::tcp;

const int max_length = 1024;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

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

class Server {
public:
	list<boost::asio::ip::address> clients;

	Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint)
			: acceptor_(io_service, endpoint), socket_(io_service) {

		do_accept();
	}

private:
	void do_accept() {
		acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
			if (!ec) {
				cout << "New client!" << endl;
			}
			do_accept();
		});
	}

	tcp::acceptor acceptor_;
	tcp::socket socket_;

};

void session(socket_ptr sock) 
{
	try
	{


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
			//			(*it)->Query();
		}

		for (;;)
		{
			char data[max_length];

			boost::system::error_code error;
			size_t length = sock->read_some(boost::asio::buffer(data), error);
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

//			if ()

			boost::asio::write(*sock, boost::asio::buffer(data, length));
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

void server(boost::asio::io_service& io_service, unsigned short port)
{
	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
	for (;;)
	{
		socket_ptr sock(new tcp::socket(io_service));
		a.accept(*sock);
		boost::thread t(boost::bind(session, sock));
	}
}

int main(int argc, char* argv[]) {

/*
	try {

		if (argc < 2) {
			std::cerr << "Usage: server <port>\n";
			return 1;
		}

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
			//			(*it)->Query();
		}

		// How to use asio whatever boost?
		boost::asio::io_service io_service;
		tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[1]));
		io_service.run();

		while (true) {
			cout << "Sending the classes ..." << endl;
			cout << "Enter q key for exit" << endl;
			if (getchar() == 'q')
				break;
		}

	}

	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	*/


	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
			return 1;
		}



		boost::asio::io_service io_service;

		using namespace std; // For atoi.
		server(io_service, atoi(argv[1]));
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

    return 0;
}

