import navascript


db_instance = navascript.database.Db("pqsql", "minvx", "minvx_usr", "", "pass.pwd", "127.0.0.1", 5432, 0)
datasource_str =  db_instance.username + ":" + db_instance.db + "@" +  db_instance.host + ":" + str(db_instance.port) + " [driver:" + db_instance.driver + "]"
navascript.console.Writeln("[STATUS] Datasource")
navascript.console.Writeln("[STATUS] " + datasource_str);
navascript.console.Writeln("")
navascript.console.Writeln("[STATUS] Connecting to Datasource..")