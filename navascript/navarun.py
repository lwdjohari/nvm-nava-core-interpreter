import navascript

# read the cli arguments
# arguments = navascript.GetCliArguments()

# load the plugin
navascript.console.Status("Load plugins")

# backend
compiler_plugin = navascript.LoadCompilerPlugin("compiler-plugin-rust-std","")
repo_plugin = navascript.LoadCompilerPlugin("repo-plugin-rust-std","")
service_plugin = navascript.LoadCompilerPlugin("service-plugin-rust-std","")

# build the feature-group

features = navascript.CreateFeatures("minvx")

features.Create("backend", "Backend Server")
features.Create("web", "Web")

features.Feature("backend").Add(compiler_plugin)
features.Feature("backend").Add(repo_plugin)
features.Feature("backend").Add(service_plugin)

features.Feature("backend").PrintStatus()
features.Feature("web").PrintStatus()
navascript.console.Writeln("")


# check features plugin

# is_backend_loaded = features_g.Check("backend",print = 1)

# if(arguments.features.IsHave("backend")):
#     if(not is_backend_loaded):
#        navascript.Terminate(features_g.Feature("backend").Name() + " have one or more plugins are not loaded!")


# running the default codegen

# datasource info
db_instance = navascript.database.Db("pqsql", "minvx", "minvx_usr", "", "pass.pwd", "127.0.0.1", 5432, 0)
datasource_str =  db_instance.username + ":" + db_instance.db + "@" +  db_instance.host + ":" + str(db_instance.port) + " [driver:" + db_instance.driver + "]"
navascript.console.Status("Datasource")
navascript.console.Status(datasource_str);
navascript.console.Writeln("")
navascript.console.Status("Connecting to Datasource..")







