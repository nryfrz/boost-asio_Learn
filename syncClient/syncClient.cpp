#include <boost/asio.hpp>
#include <iostream>
const int MSG_SIZE = 1024;
int main() {
	//创建上下文
	boost::asio::io_context ioc;
	boost::asio::ip::tcp::endpoint remote_ep(boost::asio::ip::address::from_string("127.0.0.1"), 5555);
	boost::asio::ip::tcp::socket sock(ioc, remote_ep.protocol());

	boost::system::error_code error;

	sock.connect(remote_ep, error);
	if (error) {
		std::cout << "failed to connect server error code :" << error.value() << std::endl;
		return -1;
	}

	std::cout << "input message: ";

	char str[MSG_SIZE];
	std::cin.getline(str, MSG_SIZE);
	size_t strsize = strlen(str);
	boost::asio::write(sock, boost::asio::buffer(str, strsize));
	char reply[MSG_SIZE];

	size_t reply_size = boost::asio::read(sock, boost::asio::buffer(reply, strsize));

	std::cout << "reply str: ";
	std::cout.write(reply, reply_size);
	return 0;


}