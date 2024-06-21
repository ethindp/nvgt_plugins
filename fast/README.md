# Fast plugin

This plugin offers faster versions of many of NVGT's built-in functions, as well as functionality not present in the engine proper. This plugin is primarily useful for processing large amounts of data. Though performance gains may be exhibited on smaller inputs, it may not be as much as expected, and is holy dependent on far too many characteristics to fully enumerate (ie. operating system, whether your on an HDD, SSD, or NVMe, whether your on a network share, etc). The plugin offers low-level, fast functions when you've got that need for speed, while trying to make the interfaces simpler than what your operating system or libc/glibc may provide.

This plugin uses [sleef](https://github.com/shibatch/sleef) and [llfio](https://ned14.github.io/llfio) internally. Some of the documentation (e.g. for fast IO) is duplicated here for easier reference and understanding in the context of NVGT. In particular, the fast IO functions can be used by individuals unfamiliar with OS caching, disk controllers, etc., as long as they don't modify any of the modes or flags. This library deliberately does not perform checks that normally would be performed for performance reasons (i.e., you are expected to validate the input yourself).

This plugin is still in early alpha. If something breaks, feel free to file an issue, and don't hesitate to contribute! The code for this plugin is placed into the public domain, though the libraries it uses may not be.

## Build instructions

This plugin uses cmake, cpm.cmake, and vcpkg. It can pretty much build itself. First, clone this repository with the --recursive flag. Then, go into the `fast` directory, create a `build` directory (in-source tree builds are NOT supported), and then:

* On windows, if you want static linking, specify `-DVCPKG_TARGET_TRIPLET="x64-windows-static"` on the cmake command line before you specify a generator or path.
* Otherwise, you can omit this flag.

### WARNING

If your version of NVGT is a release binary, you must also build this plugin in release mode. If your version of NVGT is a debug binary, this plugin must also be built in debug mode. Mixing these two modes is strongly discouraged and will most likely exhibit undefined behavior and weird crashes and other bugs, as data will be migrated between heaps that are not designed for such migrations, and the internal layout of data structures will be different. The `RelWithDebInfo` build type is not supported and the build will fail if it is attempted.

After you've executed the configure step (which can take some time while vcpkg builds the dependencies for itself), run the generator you chose. Once it finishes, you should have a `fast.dll`/`libfast.so`/`fast.dylib` binary in your build directory!

