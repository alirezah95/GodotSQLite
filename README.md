# GodotSQLite
**GodotSQLite** is a C++ wrapper around [**SQLiteCpp**](https://github.com/SRombauts/SQLiteCpp) library to add sqlite support to [**Godot game engine**](https://godotengine.org/).

## About GodotSQLite library:
**GodotSQLite** is a simple C++ wrapper that adds sqlite3 support in Godot through easy to use classes and functions. It is based on a smart yet simple sqlite3 C++ wrapper called [**SQLiteCpp**](https://github.com/SRombauts/SQLiteCpp). **GodotSQLite** makes this library usable in Godot for any target platform.

## Supported platforms:
Developments and tests are done under the following OSs:
* *Fedora 32*
* *Android (armv7 and amr64v8a)*


# Getting Started:
In order to use this library simply download the [latest release](https://github.com/alirezah95/GodotSQLite/releases), uncompress and paste contents of GodotSQLite folder into **`res::Scripts/`** folder.
For special cases you can use [this page](https://github.com/alirezah95/GodotSQLite/blob/main/docs/Compiling.md) to compile the library yourself.

### Documentation:
You can read classes description and API documentation from **[this file](https://github.com/alirezah95/GodotSQLite/blob/main/docs/Documentation.md)**.

### Examples:
Assuming that you are familiar wiht [using GDNative module](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-cpp-example.html#using-the-gdnative-module), in following examples, we use **`GDDatabase.gdns`** and **`GDStatement.gdns`** NativeScripts.
* ##### [First example](https://github.com/alirezah95/GodotSQLite/blob/main/examples/firstExample.gd) demonstrates how to open/create a database, create a table and insert into it.
* ##### [Second example](https://github.com/alirezah95/GodotSQLite/blob/main/examples/secondExample.gd) shows how to use GDStatement class to query statement that expects results and how to get those result.

## See also:
* **[SQLiteC++](https://github.com/SRombauts/SQLiteCpp)**: A smart and easy to use C++ SQLite3 wrapper.
* **[GDNative C++ Example](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-cpp-example.html)**: Complete guild to write C++ modules for Godot or to simply use a compiled one in your project.