#include <gdnative/gdnative.h>

#include <core/Godot.hpp>
#include <gd_database.hpp>
#include <gd_statement.hpp>


extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options* op)
{
    godot::Godot::gdnative_init(op);
    return;
}


extern "C" void GDN_EXPORT
godot_gdnative_terminate(godot_gdnative_terminate_options* op)
{
    godot::Godot::gdnative_terminate(op);
    return;
}


extern "C" void GDN_EXPORT godot_nativescript_init(void* handle)
{
    godot::Godot::nativescript_init(handle);

    /* Register classes here. */
    godot::register_class<godot::GDDatabase>();
    godot::register_class<godot::GDStatement>();

    return;
}