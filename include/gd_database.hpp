#ifndef GD_DATABASE_HPP
#define GD_DATABASE_HPP

#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>

#include <gd_statement.hpp>
#include <godot/Node.hpp>
#include <godot/core/Godot.hpp>
#include <godot/core/Ref.hpp>
#include <memory>
#include <result_enum.hpp>


using std::make_unique;
using std::unique_ptr;

namespace godot
{
extern const int OPEN_READONLY;
extern const int OPEN_READWRITE;
extern const int OPEN_CREATE;

/**
 * @brief   A wrapper around SQLite::Database class.
 *
 * @note    In case of any error (when the return value of a function is a
 * Result::FAILED, member varialbe m_what is set.
 */
class GDDatabase : public Node
{
    GODOT_CLASS(GDDatabase, Node)
    friend class GDStatement;

public:
    /**
     * @brief Function to register all the methods that are meant to be exposed
     * to gdscrtipt.
     */
    static void _register_methods();

    /**
     * @brief _init() function must exist for every class.
     */
    void _init();

    /**
     * @brief Default constructor for GDDatabase class. Note that the m_database
     * field will be null until the user call the open method.
     */
    GDDatabase();

    ~GDDatabase();

    /**
     * @brief Opens a database with the given file name. In case of any error,
     * m_what is set with proper error message.
     *
     * @param[in] fileName  String path to the database.
     * @param[in] flags     Open flag for database (OPEN_CREATE/
     * OPEN_READWRITE/ OPEN_READONLY)
     * @return  Returns Result::OK on success and Result::FAILED in case of any
     * error.
     */
    Result open(const String fileName, const int flags);

    /**
     * @brief Shortcut to execute one or multiple statements with no expected
     * results. In case of any error, m_what is set with proper error message.
     *
     * @see Database::exec
     *
     * @return number of rows modified by the last INSERT, UPDATE or DELETE
     * statement (beware of multiple statements) or Result::FAIL in case of any
     * error.
     */
    int exec(const String statement);

    /**
     * @brief Checks whether table with tableName exists in database or not.
     *
     * @return True if table with tableName exists in database and false
     * otherwise.
     */
    bool tableExists(const String tableName);

    /**
     * @brief Load or save the database content. In case of any error, m_what is
     * set with proper error message.
     *
     * This function is used to load the contents of a database file on disk
     * into the "main" database of open database connection, or to save the
     * current contents of the database into a database file on disk.
     *
     * @return Result::OK on success or an error code for sqlite.
     */
    int backup(const String filename, int type);

    /**
     * @brief Begins a transaction on this database. In case of any error,
     * m_what is set with proper error message.
     *
     * @return Result::OK on success and Result::FAILED in case of any error.
     *
     * @note In order to start a new transaction the last one must be either
     * commited or rollbacked otherwise this function returns Result::FAILED.
     */
    Result beginTransaction();

    /**
     * @brief Commits the last transaction sets the m_transaction member field
     * to nullptr. If no transaction is begun with beginTransaction() function,
     * this method returns Result::FAILED. In case of any error, m_what is set
     * with proper error message.
     *
     * @return Result::OK on success and Result::FAILED in case of any error or
     * if no transaction is begun already.
     */
    Result commitTransaction();

    /**
     * @brief Rollback the begun transaction and sets the m_transaction member
     * field to nullptr. If no transaction is begun already this method simply
     * returns and won't do anything.
     */
    void rollback();


    /**
     * @brief   Returns the last error message stored in m_what.
     *
     * @returns m_what value.
     */
    String what() const;

private:
    unique_ptr<SQLite::Database> m_database;
    unique_ptr<SQLite::Transaction> m_transaction;
    String m_what;
};  // namespace godot
};  // namespace godot

#endif  // GD_DATABASE_HPP