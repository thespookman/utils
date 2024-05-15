#pragma once
#include <spk_utils/error.hpp>
#include <string>

namespace spk {
namespace hash {
std::string hash (std::string to_hash);
bool        check_hash (std::string to_check, std::string mcp);

SPK_ERR (Hash_Failed, "Could not create hash");
SPK_ERR (Check_Hash_Failed, "Could not check hash");
}; // namespace hash
}; // namespace spk
