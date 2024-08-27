#include <boost/asio.hpp>
#include <iostream>
#include <thread>

const int MAX_SIZE = 1024;

int workThread(std::shared_ptr<boost::asio::ip::tcp::socket> sock) {
	try {
		while (1) {
			char buf[MAX_SIZE];
			boost::system::error_code error;
			size_t buf_len = sock->read_some(boost::asio::buffer(buf, MAX_SIZE), error);
			if (error == boost::asio::error::eof) {
				std::cout << "connection closed" << std::endl;
				break;
			}
			else if (error) {
				throw boost::system::system_error(error);
			}
			std::cout << "message from: " << sock->remote_endpoint().address().to_string() << std::endl;
			std::cout << "message: " << std::string(buf, buf_len);

			boost::asio::write(*sock, boost::asio::buffer(buf, buf_len), error);
			if (error) {
				throw boost::system::system_error(error);
			}

		}
	}
	catch (boost::system::system_error& err) {
		std::cout << "error mssage: " << err.what() << std::endl;
	}
}

void server(boost::asio::io_context& ioc, unsigned short port) {
	try {
		boost::system::error_code err;
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port);
		boost::asio::ip::tcp::acceptor acc(ioc, ep.protocol());
		acc.bind(ep, err);
		acc.listen(30);
		while (1) {
			std::shared_ptr<boost::asio::ip::tcp::socket> sock = std::make_shared<boost::asio::ip::tcp::socket>(ioc);
			std::cout << "start accept" << std::endl;
			
			acc.accept(*sock);
			std::cout << "accept success" << std::endl;
			std::thread thread(workThread, sock);
			thread.detach();
		}
	}
	catch (boost::system::system_error& err) {
		std::cout << "error mssage: " << err.what() << std::endl;
	}
}
int main() {
	
	boost::asio::io_context ioc;
	unsigned short port = 8888;
	std::cout << "start server" << std::endl;
	server(std::ref(ioc), port);
	ioc.run();
	return 0;
}