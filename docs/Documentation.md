# Classes description:
**[GodotSQLite](https://github.com/alirezah95/GodotSQLite)** consists of two classes, **GDDatabase** and **GDStatement**. **GDDatabase**, as inferred from its name, is used to open, create or close databases, executing **one** or **multiple** statements **with no expected results**, dealing with transactions (begin, commit or rollback a transaction), etc. On the other hand **GDStatement** class should be merely used for statements **with expected results** and for getting those results.

## API Reference:
<details> <summary style="font-size:24px;font-weight:bold"> GDDatabase: </summary>
&nbsp

* <details> <summary style="font-weight:bold"> open(fileName: <span style="color:purple">String</span>, flags: <span style="color:purple">int</span>) -> <span style="color:purple">int</span>:</summary> <ul style="list-style-type:none;">

If database with the given  **fileName** exists, opens it otherwise create a new database with the given **fileName**. The **flags** argument holds the open mode of the database. Argument **flags** can be `0x01` as **open_readonly**, `0x02` as **open_readwrite** and `0x04` as **open_create** or the bitwise **OR** of those value. Note that an invalid parameter returns an error an the database won't be opened or created. Returns `0` on success and `-1` in case of an error.
</ul>

* <details> <summary style="font-weight:bold"> exec(statement: <span style="color:purple">String</span></span>) -> <span style="color:purple">int</span>:</summary> <ul style="list-style-type:none;">

A shortcut to execute **one** or **multiple** statement **with no expected resutls**. Returns `0` on success and `-1` in case of an error.
</ul>

* <details> <summary style="font-weight:bold"> tableExists(tableName: <span style="color:purple">String</span></span>) -> <span style="color:purple">bool</span>:</summary> <ul style="list-style-type:none;">

Returns `true` if a table with **tableName** exists in the database and `false` if not.
</ul>

* <details> <summary style="font-weight:bold"> backup(fileName: <span style="color:purple">String</span>, type: <span style="color:purple">int</span>) -> <span style="color:purple">int</span>:</summary> <ul style="list-style-type:none;">

If **type** is `0` saves current database to a fileName as backup, and if **type** is `1` loads an already backedup database from **fileName**. Returns `0` on success and `-1` in case of an error.
</ul>

* <details> <summary style="font-weight:bold"> beginTransaction() -> <span style="color:purple">int</span>:</summary> <ul style="list-style-type:none;">

Begins a new transaction on database if and only if no transaction has been already started, if it has you must commit or rollback last transaction in order to begin a new one. In case no database is opened with **open** method, this function returns `-1` as failed. Returns `0` on success and `-1` in case of an error.
</ul>

* <details> <summary style="font-weight:bold"> commitTransaction() -> <span style="color:purple">int</span>:</summary> <ul style="list-style-type:none;">

Commits an already begun transaction. If no transaction has already been begun or if no database is open, this method retures `-1` as an error. Returns `0` on success and `-1` in case of an error.
</ul>

* <details> <summary style="font-weight:bold"> rollback() -> <span style="color:purple">void</span>:</summary> <ul style="list-style-type:none;">

Rollback the aleady started transaction. If no transaction is already begun of if no database is not open, the method merely returns and does not anything.
</ul>

* <details> <summary style="font-weight:bold"> what() -> <span style="color:purple">String</span>:</summary> <ul style="list-style-type:none;">

Returns the last error message stored in database.
</ul>

</details>


<details> <summary style="font-size:24px;font-weight:bold"> GDStatement: </summary>
&nbsp

* <details> <summary style="font-weight:bold"> setStatement(database: <span style="color:purple">GDDatabase</span>, query: <span style="color:purple">String</span>) -> <span style="color:purple">int</span>:</summary> <ul style="list-style-type:none;">

Sets a new statement query, prepares and compile it, to be executed on the given database. Use this methode for queries **with expected results** and use **GDDatabase::exec()** method for no expected result queries (Though you can use this method too). Returns `0` on success and `-1` in case of an error in **query** or if no database is *Null*.
</ul>

* <details> <summary style="font-weight:bold"> executeStep() -> <span style="color:purple">bool</span>:</summary> <ul style="list-style-type:none;">

Execute one step from the last set statement and stores a row of result if any exists. Use this function in while loop condition for queries with one or multiple results, as long as this method returns `true` it means that a row of result is available to fetch, and if it returns `false`, either the query didn't have any results or it is finished.
</ul>

* <details> <summary style="font-weight:bold"> getColumn(index: <span style="color:purple">int</span>) -> <span style="color:purple">Variant</span>:</summary> <ul style="list-style-type:none;">

Gets the column at the given **index** from the last row of result. Use this function inside a while loop after **GDStatement::executeStep()** method. Returns a *Variant* containing the data at column **index** or an empty *Variant* if no row of result exists of in **index** is out-of-range.
</ul>

</details>
&nbsp

# Notes:
When you're using this library you should make sure that every new object that you make from either **GDDatabase** or **GDStatement**, is ***freed***, otherwise the database won't be closed properly and some issues might occur. If you add those classes as a node's script or as a global script, you are free of this responsibility as **Godot** itself will call the ***free()*** method on nodes and their scripts. But if you use them through ***new()*** method, make sure that you call ***free()*** method after you're done with them.