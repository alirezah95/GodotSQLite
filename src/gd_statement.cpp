#include <SQLiteCpp/Column.h>

#include <gd_database.hpp>
#include <gd_statement.hpp>
#include <result_enum.hpp>

using namespace godot;
using SQLite::Statement;
using std::exception;


void GDStatement::_register_methods()
{
    godot::register_method("setStatement", &GDStatement::setStatement);
    godot::register_method("executeStep", &GDStatement::executeStep);
    godot::register_method("getColumn", &GDStatement::getColumn);
}  // _register_method.


void GDStatement::_init() { return; }


GDStatement::GDStatement() : m_database(nullptr), m_isDone(false) {}


Result GDStatement::setStatement(GDDatabase* database, const String query)
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
}  // setStatement.


bool GDStatement::executeStep()
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
}  // executeStep.


Variant GDStatement::getColumn(const int index)
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
}  // getColumn.


GDStatement::~GDStatement()
{
    m_statement = nullptr;
    m_database = nullptr;
    return;
}  // destructor.
