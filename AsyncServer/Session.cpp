#include "Session.h"
void Session::Start() {
	memset(data_, 0, max_len);
	sock_.async_read_some(asio::buffer(data_, max_len), 
		std::bind(&Session::read_hanle, this, std::placeholders::_1, std::placeholders::_2));

}

void Session::read_hanle(const boost::system::error_code& error,
	std::size_t bytes_transfered) {
	if (!error) {
		std::cout << "msg len: " << bytes_transfered << std::endl;
		std::cout << "receive data is: " << data_ << std::endl;
		sock_.async_write_some(asio::buffer(data_, max_len), std::bind(&Session::write_handle, this, std::placeholders::_1));
	}
	else {
		delete this;
	}
}
void Session::write_handle(const boost::system::error_code& error) {
	if (!error) {
		memset(data_, 0, max_len);
		sock_.async_read_some(asio::buffer(data_, max_len),
			std::bind(&Session::read_hanle, this, std::placeholders::_1, std::placeholders::_2));
	}
	else {
		delete this;
	}
}