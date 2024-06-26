#include <iostream>
#include <string>
#include <sys/sysinfo.h>

#include "../include/log.h"
#include "../include/rpc/rpc_client.h"

void tcp_client_worker(TcpClient& tcp_client)
{
    tcp_client.connect("127.0.0.1",12345);
    char buf[1024];

    NETCO_LOG()<<"client send ping";
    tcp_client.send("ping",4);
    tcp_client.recv(buf,1024);
    NETCO_LOG()<<("client recv %s",buf);
    /** 问题初步分析是由于rpc客户端销毁造成一直发送0造成的*/
}

void rpc_client_worker(RpcClient& rpc_client,int number)
{
        rpc_client.connect("127.0.0.1",12345);
        for(int i = 0; i < number; ++i)
        {
            NETCO_LOG()<<("-------the %d st client test-----------",i);
            rpc_client.ping();
            TinyJson request;
            TinyJson result;
            request["service"].Set<std::string>("HelloWorld");
            request["method"].Set<std::string>("world");
            rpc_client.call(request,result);
            int errcode = result.Get<int>("err");
            std::string errmsg = result.Get<std::string>("errmsg");
            NETCO_LOG()<<("--------------------------------");
            NETCO_LOG()<<("the result errcode is %d",errcode);
            NETCO_LOG()<<("the result errmsg is %s",errmsg.c_str());
            NETCO_LOG()<<("--------------------------------");

            TinyJson request_two;
            TinyJson result_two;
            request_two["service"].Set<std::string>("HelloWorld");
            request_two["method"].Set<std::string>("hello");
            rpc_client.call(request_two,result_two);
            int errcode_two = result_two.Get<int>("err");
            std::string errmsg_two = result_two.Get<std::string>("errmsg");
            NETCO_LOG()<<("--------------------------------");
            NETCO_LOG()<<("the result errcode is %d",errcode_two);
            NETCO_LOG()<<("the result errmsg is %s",errmsg_two.c_str());
            NETCO_LOG()<<("--------------------------------");
        }
        
    
}

int main()
{
    NETCO_LOG()<<("test: add one rpc client");
    //TcpClient tcp_client_test;
    RpcClient rpc_client_test;
    int loop_time = 100;
    //netco::co_go([&tcp_client_test](){
	//	tcp_client_worker(tcp_client_test);
	//});
	netco::co_go([&rpc_client_test,&loop_time](){
		rpc_client_worker(rpc_client_test,loop_time);
	});
    netco::sche_join();
    return 0;
}