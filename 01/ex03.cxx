#include <fstream>
#include "ex01.pb.h"
#include "ex03.pb.h"

int main() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  Test3 test3;
  test3.mutable_c()->set_a(150);
  std::fstream output("ex03",
                      std::ios::out | std::ios::trunc | std::ios::binary);
  test3.SerializeToOstream(&output);
  google::protobuf::ShutdownProtobufLibrary();
}
