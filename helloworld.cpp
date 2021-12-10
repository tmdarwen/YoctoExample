#include <iostream>
#include <future>
#include "signalrclient/hub_connection.h"
#include "signalrclient/hub_connection_builder.h"
#include "signalrclient/signalr_value.h"

int main(int argc, char *argv[])
{
    std::promise<void> start_task;
    signalr::hub_connection connection = signalr::hub_connection_builder::create("http://localhost:5000/hub").build();
    
    connection.on("Echo", [](const std::vector<signalr::value>& m)
    {
        std::cout << m[0].as_string() << std::endl;
    });
    
    connection.start([&start_task](std::exception_ptr exception) {
        start_task.set_value();
    });
    
    start_task.get_future().get();
    
    std::promise<void> send_task;
    std::vector<signalr::value> args { "Hello world" };
    connection.invoke("Echo", args, [&send_task](const signalr::value& value, std::exception_ptr exception) {
        send_task.set_value();
    });
    
    send_task.get_future().get();
    
    std::promise<void> stop_task;
    connection.stop([&stop_task](std::exception_ptr exception) {
        stop_task.set_value();
    });
    
    stop_task.get_future().get();

    return 0;
}
