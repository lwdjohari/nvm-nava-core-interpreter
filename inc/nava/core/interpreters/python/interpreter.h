#ifndef NAVA_CORE_INTERPRETERS_PYTHON_V2_INTERPRETER_H
#define NAVA_CORE_INTERPRETERS_PYTHON_V2_INTERPRETER_H

#include <pybind11/embed.h>

#include <iostream>

#include "nava/core/interpreters/python/details/core_func.h"
#include "nava/core/interpreters/python/details/db_module.h"
#include "nava/core/interpreters/python/details/util_module.h"
#include "nvm/logic.h"

namespace nava {
namespace core {
namespace interpreters {
namespace python {

namespace py = pybind11;

PYBIND11_EMBEDDED_MODULE(navascript, m) {
  m.add_object("console", py::module::import("navascript_console"));
  m.add_object("database", py::module::import("navascript_database"));

  py::enum_<details::PluginTypeOption> pluginType(m, "PluginTypeOption");
  pluginType.value("None", details::PluginTypeOption::Plugin_None)
      .value("PLUGIN_COMPILER_PLUGIN",
             details::PluginTypeOption::Plugin_CompilerPlugin)
      .value("PLUGIN_REPO_PLUGIN", details::PluginTypeOption::Plugin_RepoPlugin)
      .value("PLUGIN_SERVICE_PLUGIN",
             details::PluginTypeOption::Plugin_ServicePlugin)
      .value("PLUGIN_UI_PLUGIN", details::PluginTypeOption::Plugin_UIPlugin)
      .export_values();

  py::enum_<details::PlatformTypeOption> platformType(m, "PlatformTypeOption");
  platformType.value("None", details::PlatformTypeOption::Platform_None)
      .value("PLATFORM_BACKEND", details::PlatformTypeOption::Platform_Backend)
      .value("PLATFORM_WEB", details::PlatformTypeOption::Platform_Web)
      .value("PLATFORM_MOBILE", details::PlatformTypeOption::Platform_Mobile)
      .value("PLATFORM_DESKTOP", details::PlatformTypeOption::Platform_Desktop)
      .export_values();

  py::class_<details::Plugin, std::shared_ptr<details::Plugin>> plugin(
      m, "Plugin");

  plugin
      .def(py::init<const std::string &, const std::string &,
                    details::PluginTypeOption, details::PlatformTypeOption>())
      .def("Name", &details::Plugin::Name)
      .def("Path", &details::Plugin::Path)
      .def("PluginType", &details::Plugin::PluginType)
      .def("PlatformType", &details::Plugin::PlatformType)
      .def("IsLoaded", &details::Plugin::IsLoaded)
      .def("CoreVersion", &details::Plugin::CoreVersion)
      .def("PluginVersion", &details::Plugin::PluginVersion)
      .def("PrintStatus", &details::Plugin::PrintStatus);

  py::class_<details::CompilerPlugin, details::Plugin,
             std::shared_ptr<details::CompilerPlugin>>(m, "CompilerPlugin")
      .def(py::init<const std::string &, const std::string &,
                    details::PluginTypeOption, details::PlatformTypeOption>());

  py::class_<details::FeatureGroupItem,std::shared_ptr<details::FeatureGroupItem>> fgi(m, "FeatureGroupItem");
  fgi.def(py::init<const std::string &, const std::string &>())
      .def("Add", &details::FeatureGroupItem::Add)
      .def("PrintStatus", &details::FeatureGroupItem::PrintStatus);

  py::class_<details::FeatureGroup,std::shared_ptr<details::FeatureGroup>> fg(m, "FeatureGroup");
  fg.def(py::init<const std::string &>())
      .def("Create", &details::FeatureGroup::Create )
      .def("Feature", &details::FeatureGroup::Feature)
      .def("Features", &details::FeatureGroup::Features)
      .def("Remove", &details::FeatureGroup::Remove)
      .def("Clear", &details::FeatureGroup::Clear)
      .def("Size", &details::FeatureGroup::Size);

  m.def("Terminate", &details::Terminate);
  m.def("CreateFeatures", &details::CreateFeatures);
  m.def("LoadCompilerPlugin", &details::LoadCompilerPlugin);
};

class PythonInterpreter {
 private:
  nvm::logic::FlagOnce flag_once_;
  std::string version_;

  void RunPythonGetVersion() {
    pybind11::object sys = pybind11::module::import("sys");
    pybind11::object version_info = sys.attr("version_info");
    int major = version_info.attr("major").cast<int>();
    int minor = version_info.attr("minor").cast<int>();
    int micro = version_info.attr("micro").cast<int>();
    version_ = "Python " + std::to_string(major) + "." + std::to_string(minor) +
               "." + std::to_string(micro);
  }

 public:
  PythonInterpreter() : flag_once_(), version_(){};

  ~PythonInterpreter(){};

  void RunPythonEmbedded(std::string python_file) {
    try {
      py::scoped_interpreter guard{};
      if (!flag_once_.IsSignaled()) {
        RunPythonGetVersion();
        flag_once_.Signal();
      }

      py::object scope = py::module_::import("__main__").attr("__dict__");
      py::eval_file(python_file, scope);

    //   scope.attr("clear")();
    //   py::module::import("gc").attr("collect")();
    } catch (py::error_already_set const &e) {
      std::cerr << "Navascript Python error: " << e.what() << std::endl;
    } catch (const std::exception &e) {
    }
  };

  std::string Version() {
    if (!flag_once_.IsSignaled()) {
      py::scoped_interpreter guard{};
      RunPythonGetVersion();
      flag_once_.Signal();
    }

    return version_;
  }
};

}  // namespace python
}  // namespace interpreters
}  // namespace core
}  // namespace nava

#endif  // NVM_CORE_INTERPRETERS_PYTHON_V2_INTERPRETER_H
