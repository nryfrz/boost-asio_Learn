#include "Server.h"

void Server::start_accept()
{
	Session* session = new Session(ioc_);
	acc_.async_accept(session->sock(), std::bind(&Server::handle_accept, this, session, std::placeholders::_1));
}

void Server::handle_accept(Session* session, const boost::system::error_code& error)
{
	if (!error) {
		session->Start();
	}
	else {
		delete session;
	}
	start_accept();
}
