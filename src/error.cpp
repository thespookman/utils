#include "spk_utils/error.hpp"

#include <spk_log.hpp>

using std::string;
namespace spk {
namespace err {
using log::log;
Error::Error (string _message) : message {_message} {
    log (string ("Throwing ") + message);
}

const char* Error::what () const noexcept {
    return message.c_str ();
}
}; // namespace err
}; // namespace spk
