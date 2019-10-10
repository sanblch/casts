#include <fstream>
#include "ex02.pb.h"

int main() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  Test2 test2;
  test2.set_b("testing");
  std::fstream output("ex02",
                      std::ios::out | std::ios::trunc | std::ios::binary);
  test2.SerializeToOstream(&output);
  google::protobuf::ShutdownProtobufLibrary();
}
