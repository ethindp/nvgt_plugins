#include "math/simd.h"
#include "nvgt_plugin.h"

plugin_main(nvgt_plugin_shared* shared) {
  prepare_plugin(shared);
  register_simd_elementary_functions(shared->script_engine);
  return true;
}
