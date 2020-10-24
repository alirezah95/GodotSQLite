## Compiling into a shared-library:
This document if for special cases when you want to compile **GodotSQLite** into a shared-library (.so file) yourself rather than using the precompiled shared-libraries in [releases](https://github.com/alirezah95/GodotSQLite/releases). First you need to use [this tutorial](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-cpp-example.html#building-the-c-bindings) and generate the C++ bindings for your target platform, then use SConstruct to compile the library:
```bash
scons platform=<platform> gd_library_dir=<gd_library_dir>
```

* **platform**: Specify the target platform you're compiling the library for. For now it can only be `linux` or `android`.
* **gd_library_dir**: Specify the directory in which the generated Godot .a bindings are stored.
* **gd_library_name** *(Optional)*: Specify the name of the generated Godot .a bindings. By default it figures it out based on other options like platform, target etc.
* **target** *(Optional)*: Specify realse or debug target.
* **output_dir** *(Optional)*: The directory you want to put your library in.
* **add_includes** *(Optional)*: Adds custom include directories. Seperate directories using `:`.

* #### Compiling for Android:
In order to compile **GodotSQLite** for android, you must download [Android NDK](https://developer.android.com/ndk/downloads) first.
```bash
scons platform=android gd_library_dir=<gd_library_dir> ANDROID_NDK_ROOT=<path_to_android_ndk_root>
```
* **ANDROID_NDK_ROOT** : Path to Android NDK root folder. You can define ANDROID_NDK_ROOT in your envirenmont variables, to avoid including it in every scons call.
* **android_arch** *(Optional)*: Target android architecture, set it to `armv7`, `arm64v8`, `x86`, `x86_64`. Default value is `armv7`.
* **android_api_level** *(Optional)*: Target android api level. By default it is **18** if `android_arch` is `armv7` or `x86`, and **21** if `arm64v8` or `x86_64`.
