#include <grpcpp/grpcpp.h>
#include "service.grpc.pb.h"
#include "service.pb.h"
#include <iostream>
#include <gflags/gflags.h>
#include "client.h"

DEFINE_string(register, "", "Register a username");
DEFINE_string(user, "", "Login a user");
DEFINE_string(chirp, "", "Send a chirp");
DEFINE_string(reply, "", "Make a chirp a reply to another chirp");
DEFINE_string(follow, "", "Follow a user");
DEFINE_string(read, "", "Read a chirp");
DEFINE_bool(monitor, false, "Stream chirps from followed users");

// parses command line flags and triggers appropriate action
int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::shared_ptr<grpc::Channel> service_connection_ = grpc::CreateChannel("localhost:50002", grpc::InsecureChannelCredentials());
  std::unique_ptr<chirp::ServiceLayer::Stub> stub_ = chirp::ServiceLayer::NewStub(service_connection_);
  std::string my_username="";
  Client client;
  if (FLAGS_register != "") {
    client.registeruser(FLAGS_register, stub_);
  }
  if (FLAGS_user != "") {
    my_username = FLAGS_user;
  }
  if (FLAGS_chirp != "" && my_username != "") {
    client.sendchirp(my_username, FLAGS_chirp, FLAGS_reply, stub_);
  }
  if (FLAGS_follow != "" && my_username != "") {
    client.follow(my_username, FLAGS_follow, stub_);
  }
  if (FLAGS_read != "") {
    client.read(FLAGS_read, stub_);
  }
  if (FLAGS_monitor && my_username != "") {
    client.monitor(my_username, stub_);
  }

  return 0;
}
