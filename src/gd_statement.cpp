#include <SQLiteCpp/Column.h>

#include <gd_database.hpp>
#include <gd_statement.hpp>
#include <result_enum.hpp>

using namespace godot;
using SQLite::Statement;
using std::exception;


void GDStatement::_register_methods()
{
    godot::register_method("set_statement", &GDStatement::set_statement);
    godot::register_method("execute_step", &GDStatement::execute_step);
    godot::register_method("get_column", &GDStatement::get_column);
}  // _register_method.


void GDStatement::_init() { return; }


GDStatement::GDStatement() : m_database(nullptr), m_isDone(false) {}


Result GDStatement::set_statement(GDDatabase* database, const String query)
{
    if (database == nullptr || database->m_database == nullptr) {
        return Result::FAILED;
    }
    try {
        m_statement = nullptr;
        m_statement = make_unique<Statement>(*(database->m_database),
                                             query.utf8().get_data());
        m_isDone = false;
    } catch (std::exception& ex) {
        database->m_what = ex.what();
        return Result::FAILED;
    }
    m_database = database;

    return Result::OK;
}  // set_statement.


bool GDStatement::execute_step()
{
    if (m_statement == nullptr) {
        m_database->m_what = "Statement is empty.";
        return false;
    }

    bool result = false;

    try {
        result = m_statement->executeStep();
    } catch (exception& ex) {
        m_database->m_what = ex.what();
        return false;
    }

    m_isDone = !result;

    return result;
}  // execute_step.


Variant GDStatement::get_column(const int index)
{
    if (m_statement == nullptr) {
        m_database->m_what = "Statement is empty.";
        return Result::FAILED;
    }

    try {
        auto column = m_statement->getColumn(index);
        Variant res;
        if (column.isNull()) {
            ;
        } else if (column.isInteger()) {
            res = column.getInt();
        } else if (column.isFloat()) {
            res = column.getDouble();
        } else if (column.isText()) {
            res = column.getText();
        } else if (column.isBlob()) {
            ;
        }
        return res;
    } catch (std::exception& ex) {
        return Variant();
    }
}  // get_column.


GDStatement::~GDStatement()
{
    m_statement = nullptr;
    m_database = nullptr;
    return;
}  // destructor.
