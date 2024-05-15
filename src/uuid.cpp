#include "spk_utils/uuid.hpp"

#include <uuid/uuid.h>

namespace spk {
namespace uuid {
UUID::UUID () : is_set {false} {}
using std::string;
UUID::UUID (string _data) : data {_data}, is_set {true} {
    if (data.size () != 16) throw UUID_Error ();
}

const string UUID::get () const {
    if (!is_set) throw Unset_UUID ();
    return data;
}

const string UUID::to_string () const {
    if (!is_set) throw Unset_UUID ();
    char* str = new char[37];
    uuid_unparse_lower ((const unsigned char*) data.c_str (), str);
    return string (str);
}
UUID::operator bool () const { return is_set; }
bool UUID::operator!= (const UUID& uuid) const {
    return data != uuid.data;
}
bool UUID::operator== (const UUID& uuid) const {
    return data == uuid.data;
}

UUID UUID::create () {
    string str (16, 0);
    uuid_generate_random ((unsigned char*) str.data ());
    return UUID (str);
}

UUID UUID::read (string text) {
    string str (16, 0);
    if (uuid_parse (text.c_str (), (unsigned char*) str.data ()))
        throw UUID_Error ();
    return UUID (str);
}
}; // namespace uuid
}; // namespace spk
