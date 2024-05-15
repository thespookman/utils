#pragma once
#include <stdexcept>
#include <string>

namespace spk {
namespace err {
class Error : public std::exception {
  private:
    std::string message;

  public:
    Error (std::string message);
    const char* what () const noexcept override;
};
}; // namespace err
}; // namespace spk

#define SPK_ERR(name, message)                                     \
    struct name : public spk::err::Error {                         \
        name () : spk::err::Error (message) {}                     \
    };
