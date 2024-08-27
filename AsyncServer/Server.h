#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include "Session.h"
using namespace boost;


class Server
{
public:
	Server(asio::io_context& ioc, unsigned short port) : ioc_(ioc), acc_(ioc, asio::ip::tcp::endpoint(asio::ip::address_v4::any(), port)) {
		start_accept();
	}
private:
	asio::ip::tcp::acceptor acc_;
	asio::io_context& ioc_;
private:
	void start_accept();
	void handle_accept(Session* session, const boost::system::error_code& );

};

