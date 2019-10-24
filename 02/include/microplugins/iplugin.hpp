#include <iostream>
#include <memory>

class QWidget;

namespace micro {
  inline int is_le() noexcept { static const std::uint32_t i = 0x04030201; return (*((std::uint8_t*)(&i)) == 1); }
  inline int make_version(int Major, int Minor) noexcept { return ((Major << 8) | Minor); }
  inline int get_major(int Version) noexcept { return (Version >> 8); }
  inline int get_minor(int Version) noexcept { return (is_le() ? Version & 0xff : Version & 0xff000000); }

class iplugin {
  int version_;
  std::string name_;
public:
  explicit iplugin(int v = micro::make_version(1, 0),
                   const std::string &nm = {})
      : version_(v), name_(nm) {}
  virtual ~iplugin() {
    std::cout << "~iplugin();" << std::endl;
  }

  /** \returns Version of storage. */
  int version() const noexcept { return version_; }

  /** \returns Major version of storage. */
  int major() const noexcept { return micro::get_major(version_); }

  /** \returns Minor version of storage. */
  int minor() const noexcept { return micro::get_minor(version_); }

  /** \returns Name of storage. */
  const std::string& name() const noexcept { return name_; }
};

class math_plugin : public iplugin {
public:
  explicit math_plugin(int v,
                       const std::string &nm) : iplugin(v, nm) {}
  ~math_plugin() override {
    std::cout << "~math_plugin();" << std::endl;
  }

  virtual int add(int a, int b) = 0;
};

class widget_plugin : public iplugin {
public:
  explicit widget_plugin(int v,
                       const std::string &nm) : iplugin(v, nm) {}
  ~widget_plugin() override {}

  virtual QWidget* widget() = 0;
};
} // namespace micro

/** Signature of "C" function for loading plugin from dll. \see import_plugin() */
using import_plugin_cb_t = std::unique_ptr<micro::iplugin>();

extern "C" {
  /** \returns Shared pointer to newly created instance of a plugin from dll. */
  extern std::unique_ptr<micro::iplugin> import_plugin();
}


