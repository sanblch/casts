#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"
using namespace std;

void print_message(std::string& prefix, const google::protobuf::Message& msg) {
  auto desc = msg.GetDescriptor();
  auto refl = msg.GetReflection();

  for(int i = 0; i < desc->field_count(); ++i) {
    auto field = desc->field(i);
    std::cout << prefix << field->type_name() << " " << field->name() << std::endl;
    if(field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE) {
      std::string new_prefix = prefix;
      new_prefix += "    ";
      if(!field->is_repeated())
        print_message(new_prefix, refl->GetMessage(msg, field));
      else
        for(int i = 0; i < refl->FieldSize(msg, field); ++i)
          print_message(new_prefix, refl->GetRepeatedMessage(msg, field, i));
    }
  }
}

int main(int argc, char* argv[]) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  tutorial::AddressBook address_book;

  fstream input("addressbook", ios::in | ios::binary);
  if (!address_book.ParseFromIstream(&input)) {
    cerr << "Failed to parse address book." << endl;
    return -1;
  }

  std::string prefix = "";
  print_message(prefix, address_book);

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
