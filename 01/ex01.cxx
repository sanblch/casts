#include <fstream>
#include "ex01.pb.h"

int main() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  Test1 test1;
  test1.set_a(150);
  std::fstream output("ex01",
                      std::ios::out | std::ios::trunc | std::ios::binary);
  test1.SerializeToOstream(&output);
  google::protobuf::ShutdownProtobufLibrary();
}
