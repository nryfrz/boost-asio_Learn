#pragma once
#include <boost/asio.hpp>
#include <iostream>
using namespace boost;
class Session
{
public:
	Session(asio::io_context& ioc) : sock_(ioc) {
	}
	void Start();
	asio::ip::tcp::socket& sock() {
		return sock_;
	}
private:
	asio::ip::tcp::socket sock_;
	enum
	{
		max_len = 1024
	};
	char data_[max_len];

	void read_hanle(const boost::system::error_code&,
		std::size_t);
	void write_handle(const boost::system::error_code&);
};

