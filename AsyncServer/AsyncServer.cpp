// AsyncServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Server.h"
#include <boost/asio.hpp>

int main()
{
    boost::asio::io_context ioc;
    
    Server server(std::ref(ioc), 5555);
    ioc.run();
}
