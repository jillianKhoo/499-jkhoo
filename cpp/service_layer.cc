#ifndef ServiceExecutable
#define ServiceExecutable
#include "service_layer_service_impl.h"

// Listens on port 50002 and assembles the server
void RunServer() {
  std::string server_address("0.0.0.0:50002");
  ServiceLayerServiceImpl service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();
  return 0;
}
#endif
