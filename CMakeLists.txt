cmake_minimum_required(VERSION 3.15)
project(helloworld LANGUAGES CXX VERSION 1.0)

include(FetchContent)

message(STATUS "Fetching SignalRClient...")

FetchContent_Declare(
  SignalRClient
  GIT_REPOSITORY "https://github.com/aspnet/SignalR-Client-Cpp"
  GIT_TAG "7e78fd10e50c10751533f3c16c34ebf95ec1ae22"
)
FetchContent_MakeAvailable(SignalRClient)

add_executable(helloworld helloworld.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(helloworld PRIVATE Threads::Threads)
add_compile_definitions(NO_SIGNALRCLIENT_EXPORTS)
include_directories("${CMAKE_SOURCE_DIR}/build/_deps/signalrclient-src/include/")
target_link_libraries(helloworld PRIVATE microsoft-signalr)
