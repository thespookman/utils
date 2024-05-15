#include "spk_utils/hash.hpp"

#include <libscrypt.h>

using std::string;
namespace spk {
namespace hash {
string hash (string to_hash) {
    string dst (SCRYPT_MCF_LEN, 0);
    if (libscrypt_hash (dst.data (), to_hash.c_str (), SCRYPT_N,
                        SCRYPT_r, SCRYPT_p) <= 0)
        throw Hash_Failed ();
    return dst;
}

bool check_hash (string to_check, string mcf) {
    int ret = libscrypt_check (mcf.data (), to_check.c_str ());
    if (ret < 0) throw Check_Hash_Failed ();
    if (ret == 0) return false;
    return true;
}
}; // namespace hash
}; // namespace spk
