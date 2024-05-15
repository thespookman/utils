#pragma once
#include <spk_utils/error.hpp>
#include <string>

namespace spk {
namespace uuid {
class UUID {
  private:
    bool        is_set = false;
    std::string data;

  public:
    UUID ();
    UUID (std::string data);

    const std::string get () const;
    const std::string to_string () const;
                      operator bool () const;
    bool              operator!= (const UUID& uuid) const;
    bool              operator== (const UUID& uuid) const;

    static UUID create ();
    static UUID read (std::string text);
};

SPK_ERR (UUID_Error, "Bad UUID");
SPK_ERR (Unset_UUID, "UUID is empty");
}; // namespace uuid
}; // namespace spk
