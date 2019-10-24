#include <iostream>
#include <memory>

class Base {
public:
  Base() {
    std::cout << "Base: constructor." << std::endl;
  }
  virtual ~Base() {
    std::cout << "Base: destructor." << std::endl;
  }
};

class Func : public Base {
public:
  Func() {
    std::cout << "Func: constructor." << std::endl;
  }
  ~Func() override {
    std::cout << "Func: destructor." << std::endl;
  }
  virtual void print() {
    std::cout << "Func: print." << std::endl;
  }
};

class Class : public Func, public std::enable_shared_from_this<Class> {
public:
  Class() : std::enable_shared_from_this<Class>() {
    std::cout << "Class: constructor." << std::endl;
  }
  ~Class() override {
    std::cout << "Class: destructor." << std::endl;
  }
  void print() override {
    std::cout << "Class: print." << std::endl;
  }
};

static std::shared_ptr<Base> get_ptr() {
  std::shared_ptr<Base> ret = nullptr;
  ret = std::make_shared<Class>();
  return ret;
}

int main() {
  auto ptr = get_ptr();
  dynamic_cast<Func*>(ptr.get())->print();
}
