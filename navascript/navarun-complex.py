import navascript

# read the cli arguments
arguments = navascript.GetCliArguments()

# load the plugin
navascript.console.Status("Load plugins")

# backend
compiler_plugin = navascript.LoadCompilerPlugin("compiler-plugin-rust-standard")
repo_plugin = navascript.LoadRepoPlugin("repo-plugin-rust-multi-db",compiler_plugin)
service_plugin = navascript.LoadServicePlugin("service-plugin-rust-tonic-grpc",compiler_plugin)

# frontend
fe_compiler_plugin = navascript.LoadCompilerPlugin("compiler-plugin-ts-react")
frontend_service_plugin = navascript.LoadFrontendServicePlugin("frontend-service-plugin-ts-async", fe_compiler_plugin)
frontend_ui_plugin = navascript.LoadFrontendUIPlugin("frontend-ui-plugin-react-mui-async", fe_compiler_plugin)

android_compiler_plugin = navascript.LoadCompilerPlugin("compiler-plugin-android-java-jetpack")
ios_compiler_plugin = navascript.LoadCompilerPlugin("compiler-plugin-ios-swift")

# mobile android
frontend_android_svc_plugin = navascript.LoadFrontendServicePlugin("frontend-service-plugin-android-cns", android_compiler_plugin)
# mobile ios
frontend_ios_svc_plugin = navascript.LoadFrontendServicePlugin("frontend-service-plugin-ios", ios_compiler_plugin)

frontend_ui_flutter_plugin = navascript.LoadFrontendUIPlugin("frontend-ui-plugin-flutter",["ios","android"],[ios_compiler_plugin,android_compiler_plugin])


# build the feature-group

features_g = navascript.CreateFeatures("")

features_g.Create("backend", "Backend Server")
features_g.Create("web", "Responsive Web App")
features_g.Create("android", "Android App")
features_g.Create("ios", "IOS App")

features_g.Group("backend").Add(compiler_plugin)
features_g.Group("backend").Add(repo_plugin)
features_g.Group("backend").Add(service_plugin)

features_g.Group("web").Add(fe_compiler_plugin)
features_g.Group("web").Add(frontend_service_plugin)
features_g.Group("web").Add(frontend_ui_plugin)

features_g.Group("ios").Add(ios_compiler_plugin)
features_g.Group("ios").Add(frontend_ios_svc_plugin)
features_g.Group("ios").Add(frontend_ui_flutter_plugin,"ios")

features_g.Group("android").Add(android_compiler_plugin)
features_g.Group("android").Add(frontend_android_svc_plugin)
features_g.Group("android").Add(frontend_ui_flutter_plugin,"android")

features_g.Group("backend").PrintStatus()
features_g.Group("web").PrintStatus()
features_g.Group("ios").PrintStatus()
features_g.Group("android").PrintStatus()

# check features plugin

is_backend_loaded = features_g.Check("backend",print = 1)
is_web_loaded = features_g.Check("web",print = 1)
is_ios_loaded = features_g.Check("ios",print = 1)
is_android_loaded = features_g.Check("android",print = 1)

if(arguments.features.IsHave("backend")):
    if(not is_backend_loaded):
       navascript.Terminate(features_g.Group("backend").Name() + " have one or more plugins are not loaded!")

if(arguments.features.IsHave("web")):
    if(not is_web_loaded):
       navascript.Terminate(features_g.Group("web").Name() + " have one or more plugins are not loaded!")

if(arguments.features.IsHave("ios")):
    if(not is_ios_loaded):
       navascript.Terminate(features_g.Group("ios").Name() + " have one or more plugins are not loaded!")

if(arguments.features.IsHave("android")):
    if(not is_android_loaded):
       navascript.Terminate(features_g.Group("android").Name() + " have one or more plugins are not loaded!")


# running the default codegen

# datasource info
db_instance = navascript.database.Db("pqsql", "minvx", "minvx_usr", "", "pass.pwd", "127.0.0.1", 5432, 0)
datasource_str =  db_instance.username + ":" + db_instance.db + "@" +  db_instance.host + ":" + str(db_instance.port) + " [driver:" + db_instance.driver + "]"
navascript.console.Status("Datasource")
navascript.console.Status(datasource_str);
navascript.console.Writeln("")
navascript.console.Status("Connecting to Datasource..")





