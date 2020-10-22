#ifndef GD_STATEMENT_HPP
#define GD_STATEMENT_HPP

#include <SQLiteCpp/Statement.h>

#include <godot/Node.hpp>
#include <godot/core/Godot.hpp>
#include <memory>
#include <result_enum.hpp>


using std::make_unique;
using std::unique_ptr;


namespace godot
{
class GDDatabase;

/**
 * @brief   A wrapper around SQLite::Statement class.
 *
 * @note    In case of any error (when the return value of a function is
 * Result::FAILED), get the GDDatabase::m_what error message for debugging.
 */
class GDStatement : public Node
{
    GODOT_CLASS(GDStatement, Node)
public:
    /**
     * @brief Function to register all the methods that are meant to be
     * exposed to gdscrtipt.
     */
    static void _register_methods();

    /**
     * @brief _init() function must exist for every class.
     */
    void _init();

    /**
     * @brief Construct an empty GDStatement object. Use setStatement function
     * before any data fetching.
     */
    GDStatement();
    ~GDStatement();

    /**
     * @brief Set the statement to to given query. Creates a SQLite::Statement
     * object for the given database with the given query. In case of any error
     * GDDatabase::m_what is set with proper error message.
     *
     * @param[in] database  The database for which the given query will be
     * compiled.
     * @param[in] query     The query to be executed on the database.
     *
     * @return  Last result code.
     */
    Result setStatement(GDDatabase* database, const String query);

    /**
     * @brief Execute a step of the prepared query to fetch one row of results.
     * In case of any error GDDatabase::m_what is set with proper error message.
     *
     * @see SQLite::Statement::executeStep()
     * @return True if the execution was successfull and false otherwise.
     */
    bool executeStep();

    /**
     * @brief Execute a one-step query with no expected result. In case of any
     * error GDDatabase::m_what is set with proper error message.
     *
     * @see SQLite::Statement::exec()
     *
     * @return The number of rows modified by the sql statement set by
     * setStatement funcion and Resutl::FAILED in case of any error.
     */
    int exec();

    /**
     * @brief Return a copy of the column data specified by its index. In case
     * of any error GDDatabase::m_what is set with proper error message.
     *
     * @see SQLite::Statement::getColumn.
     * @return A Variant holding the data of the column or null in case of an
     * error e.g. if index is out of range.
     */
    Variant getColumn(const int index);

private:
    unique_ptr<SQLite::Statement> m_statement;
    GDDatabase* m_database;
    bool m_isDone;
};  // class GDStatement
}  // namespace godot

#endif  // GD_STATEMENT_HPP