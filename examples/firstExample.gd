extends Node2D

var database: GDDatabase = load("res://Scripts/Nativescripts/GDDatabase.gdns").new()


func _ready() -> void:
	var res = database.open('test.db', 0x02 | 0x04)

	if res == -1:
		print(database.what())
		return
	
	# You can pass a string containing multiple database statements with no 
	# expected results to GDDatabase::exec().
	if not database.tableExists("Test"):
		res = database.exec("""CREATE TABLE Test (
			column_1 INT NOT NULL,
			column_2 CHAR(30) NOT NULL,
			PRIMARY KEY(column_1)
			);
			INSERT INTO Test 
			VALUES(1, 'value_number_1');
			INSERT INTO Test 
			VALUES(2, 'value_number_2');
			INSERT INTO Test 
			VALUES(3, 'value_number_3');
			INSERT INTO Test 
			VALUES(4, 'value_number_4');"""
			)
		if res == -1:
			print(database.what())


	return
