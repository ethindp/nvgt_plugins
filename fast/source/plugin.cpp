#include "nvgt_plugin.h"
#include "math/simd.h"

plugin_main(nvgt_plugin_shared* shared) {
	prepare_plugin(shared);
register_simd_elementary_functions(shared->script_engine);
return true;
}
