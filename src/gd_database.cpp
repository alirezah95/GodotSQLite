#include "gd_database.hpp"


using namespace godot;
using SQLite::Database;
using SQLite::Exception;
using SQLite::Transaction;


/* _register_methods function to register all the mehod in this class.*/
void GDDatabase::_register_methods()
{
    register_method("open", &GDDatabase::open);
    register_method("exec", &GDDatabase::exec);
    register_method("tableExists", &GDDatabase::tableExists);
    register_method("backup", &GDDatabase::backup);
    register_method("beginTransaction", &GDDatabase::beginTransaction);
    register_method("commitTransaction", &GDDatabase::commitTransaction);
    register_method("rollback", &GDDatabase::rollback);
    register_method("what", &GDDatabase::what);


    register_property<GDDatabase, int>("FAILED",
        &GDDatabase::set_flags, &GDDatabase::failed,
        2, GODOT_METHOD_RPC_MODE_DISABLED,
        GODOT_PROPERTY_USAGE_NOEDITOR);
    register_property<GDDatabase, int>("OK",
        &GDDatabase::set_flags, &GDDatabase::ok,
        2, GODOT_METHOD_RPC_MODE_DISABLED,
        GODOT_PROPERTY_USAGE_NOEDITOR);
    register_property<GDDatabase, int>("OPEN_READONLY",
        &GDDatabase::set_flags, &GDDatabase::open_readonly,
        SQLite::OPEN_READONLY,
        GODOT_METHOD_RPC_MODE_DISABLED,
        GODOT_PROPERTY_USAGE_NOEDITOR);
    register_property<GDDatabase, int>("OPEN_READWRITE",
        &GDDatabase::set_flags, &GDDatabase::open_readwrite,
        SQLite::OPEN_READWRITE,
        GODOT_METHOD_RPC_MODE_DISABLED,
        GODOT_PROPERTY_USAGE_NOEDITOR); 
    register_property<GDDatabase, int>("OPEN_CREATE",
        &GDDatabase::set_flags, &GDDatabase::open_create,
        SQLite::OPEN_CREATE,
        GODOT_METHOD_RPC_MODE_DISABLED,
        GODOT_PROPERTY_USAGE_NOEDITOR); 


    return;
}  // _register_methods.

/* _init function, which must exists anyway. */
void GDDatabase::_init() { return; }

GDDatabase::GDDatabase() : m_database(nullptr), m_transaction(nullptr) {}

/* Creates and opens a database with the given fileName*/
Result GDDatabase::open(const String fileName, const int flags)
{
    try {
        m_database = make_unique<Database>(fileName.utf8().get_data(), flags);
    } catch (std::exception& ex) {
        m_what = ex.what();
        return Result::FAILED;
    }

    return Result::OK;
}  // open


/* Execute one or multiple statement with no expected result.*/
int GDDatabase::exec(const String statement)
{
    if (m_database == nullptr) {
        m_what = "No database is opened.";
        return Result::FAILED;
    }

    int rows = -1;
    try {
        rows = m_database->exec(statement.utf8().get_data());
    } catch (std::exception& ex) {
        m_what = ex.what();
        return Result::FAILED;
    }

    return rows;
}  // exec


/* Checks whether a table exists in the database. */
bool GDDatabase::tableExists(const String tableName)
{
    if (m_database == nullptr) {
        m_what = "No database is opened.";
        return false;
    }
    return m_database->tableExists(tableName.utf8().get_data());
}  // tableExists


/* Loads or saves database. */
int GDDatabase::backup(const String filename, int type)
{
    if (type != 0 && type != 1) {
        m_what = "Backup type can only be SAVE (0) or LOAD (1).";
        return Result::FAILED;
    }

    if (m_database == nullptr && type == Database::BackupType::Save) {
        m_what = "No database is opened.";
        return Result::FAILED;
    }

    try {
        m_database->backup(filename.utf8().get_data(),
                           static_cast<SQLite::Database::BackupType>(type));
    } catch (std::exception& ex) {
        m_what = ex.what();
        return Result::FAILED;
    }
    return Result::OK;
}  // backup


Result GDDatabase::beginTransaction()
{
    if (m_database == nullptr) {
        m_what = "No database is opened.";
        return Result::FAILED;
    }

    if (m_transaction != nullptr) {
        /* In this case we are sure that the m_transaction is already started,
        and it's niether commited nor rollbacked.
        */
        m_what =
            "Last transaction must be either commited or rollbacked first.";
        return Result::FAILED;
    }
    try {
        m_transaction = make_unique<Transaction>(*m_database);
        return Result::OK;
    } catch (std::exception& ex) {
        m_what = ex.what();
        return Result::FAILED;
    }
    return Result::FAILED;
}  // beginTransaction.


Result GDDatabase::commitTransaction()
{
    if (m_transaction == nullptr) {
        m_what = "No transaction is begun yet.";
        return Result::FAILED;
    }

    try {
        m_transaction->commit();
        return Result::OK;
    } catch (Exception& ex) {
        m_what = ex.what();
        return Result::FAILED;
    }
}  // commitTransaction.


void GDDatabase::rollback()
{
    /**
     * Simply set the m_transaction to nullptr, the SQLite::Transaction's
     * destructor does the rollbacking.
     */
    m_transaction = nullptr;
}  // rollback.


/* Returns m_what value. */
String GDDatabase::what() const { return m_what; }  // what.


/* Destructor. */
GDDatabase::~GDDatabase()
{
    m_database = nullptr;
    return;
}  // destructor.

