#include "math/simd.h"
#include "nvgt_plugin.h"
#include <llfio.hpp>
#include <string>
#include <vector>
#include <chrono>
#include <Poco/Path.h>

namespace llfio = LLFIO_V2_NAMESPACE;

std::string read_file(const std::string& file_name) {
const auto absolute_path = Poco::Path(file_name).makeAbsolute().toString();
llfio::file_handle fh = llfio::file({}, absolute_path, llfio::file_handle::mode::read, llfio::file_handle::creation::open_existing, llfio::file_handle::caching::none, llfio::file_handle::flag::disable_safety_barriers | llfio::file_handle::flag::multiplexable).value();
std::vector<llfio::byte> buffer(fh.maximum_extent().value());
llfio::file_handle::size_type bytesread = llfio::read(fh, 0, {{ buffer.data(), buffer.size() }}, std::chrono::minutes(1)).value();
if (bytesread == 0) {
return "";
}
buffer.resize(bytesread);
std::string res;
res.reserve(bytesread);
res.append((char*)buffer.data(), bytesread);
fh.close().value();
return res;
}

void write_file(const std::string& file_name, const std::string& contents) {
const auto absolute_path = Poco::Path(file_name).makeAbsolute().toString();
std::vector<llfio::byte> buffer;
buffer.reserve(contents.size());
for (auto i = 0; i < contents.size(); ++i) {
buffer.emplace_back(static_cast<llfio::byte>(contents[i]));
}
llfio::file_handle fh = llfio::file({}, absolute_path, llfio::file_handle::mode::write, llfio::file_handle::creation::if_needed, llfio::file_handle::caching::reads, llfio::file_handle::flag::disable_safety_barriers | llfio::file_handle::flag::multiplexable).value();
fh.truncate(0).value();
fh.write(0, {{buffer.data(), buffer.size()}}, std::chrono::minutes(1)).value();
fh.close().value();
}

plugin_main(nvgt_plugin_shared* shared) {
  prepare_plugin(shared);
  register_simd_elementary_functions(shared->script_engine);
  shared->script_engine->SetDefaultNamespace("fast");
  shared->script_engine->RegisterGlobalFunction("string read_file(const string &in)", asFUNCTION(read_file), asCALL_CDECL);
  shared->script_engine->RegisterGlobalFunction("void write_file(const string &in, const string &in)", asFUNCTION(write_file), asCALL_CDECL);
  shared->script_engine->SetDefaultNamespace("");
  return true;
}
