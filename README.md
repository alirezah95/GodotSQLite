# GodotSQLite
**GodotSQLite** is a C++ wrapper around [**SQLiteCpp**](https://github.com/SRombauts/SQLiteCpp) library to add sqlite support to [**Godot game engine**](https://godotengine.org/).

## About GodotSQLite library:
**GodotSQLite** is a simple C++ wrapper that adds sqlite3 support in Godot through easy to use classes and functions. It is based on a smart yet simple sqlite3 C++ wrapper called [**SQLiteCpp**](https://github.com/SRombauts/SQLiteCpp). **GodotSQLite** makes this library usable in Godot for any target platform.

## Supported platforms:
Developments and tests are done under the following OSs:
* *Fedora 32*
* *Android (armv7 and amr64v8a)*


# Getting Started:
## Compiling into a shared-library:
In order to use this library you need to compile it into a shared-library (.so file). First you need to use [this tutorial](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-cpp-example.html#building-the-c-bindings) and generate the C++ bindings for your target platform, then use SConstruct to compile the library:
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


# Getting started

### Documentation:
You can read classes description and API documentation from **[this file](https://github.com/alirezah95/GodotSQLite/blob/main/docs/Documentation.md)**.

### Examples:
Assuming that you are familiar wiht [using GDNative module](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-cpp-example.html#using-the-gdnative-module), in following examples, we use **`GDDatabase.gdns`** and **`GDStatement.gdns`** NativeScripts.
* ##### [First example](https://github.com/alirezah95/GodotSQLite/blob/main/examples/firstExample.gd) demonstrates how to open/create a database, create a table and insert into it.
* ##### [Second example](https://github.com/alirezah95/GodotSQLite/blob/main/examples/secondExample.gd) shows how to use GDStatement class to query statement that expects results and how to get those result.

## See also:
* **[SQLiteC++](https://github.com/SRombauts/SQLiteCpp)**: A smart and easy to use C++ SQLite3 wrapper.
* **[GDNative C++ Example](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-cpp-example.html)**: Complete guild to write C++ modules for Godot or to simply use a compiled one in your project.