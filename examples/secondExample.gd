extends Node2D

var database: GDDatabase = load("res://Scripts/Nativescripts/GDDatabase.gdns").new()
var statement: GDStatement = load("res://Scripts/Nativescripts/GDStatement.gdns").new()


func _ready() -> void:
	# Assume that we are connected to the database in firstExample.dg
	if database.open('test.db', 0x02 | 0x04) == -1:
		print(database.what())

	var query: String = "SELECT * FROM Test where column_1=1"
	statement.setStatement(database, query)

	# Following while will execute just once, since only one row of result with
	# column_1=1 exists.
	while statement.executeStep():
		var col_1 = statement.getColumn(0)
		var col_2 = statement.getColumn(1)
		# Output:   1: value_number_1
		print(col_1 + ": " + col_2)

	query = "SELECT * FROM Test"  # Gets all the rows of Test table
	statement.setStatement(database, query)
	while statement.executeStep():
		var col_1 = statement.getColumn(0)
		var col_2 = statement.getColumn(1)
		print(col_1 + ": " + col_2)
		# Output:
		#       1: value_number_1
		#       2: value_number_2
		#       3: value_number_3
		#       4: value_number_4

	return
