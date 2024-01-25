#ifndef NAVA_CORE_INTERPRETERS_PYTHON_V2_INTERPRETER_H
#define NAVA_CORE_INTERPRETERS_PYTHON_V2_INTERPRETER_H

#include <pybind11/embed.h>

#include <iostream>

#include "details/db_module.h"
#include "details/util_module.h"
#include "nvm/logic.h"

namespace nava {
namespace core {
namespace interpreters {
namespace python {

namespace py = pybind11;

PYBIND11_EMBEDDED_MODULE(navascript, m) {
  m.add_object("console", py::module::import("navascript_console"));
  m.add_object("database", py::module::import("navascript_database"));
};

class PythonInterpreter {
 private:
  nvm::logic::FlagOnce flag_once_;
  std::string version_;

 public:
  PythonInterpreter() : flag_once_(), version_(){};

  ~PythonInterpreter(){};

  void RunPythonEmbedded(std::string python_file) {
    py::scoped_interpreter guard{};

    try {
      if (!flag_once_.IsSignaled()) {
        version_ = std::string(
            py::str(py::module::import("sys").attr("version_info")));
        flag_once_.Signal();
      }

      py::object scope = py::module_::import("__main__").attr("__dict__");

      py::eval_file(python_file, scope);

      scope.attr("clear")();
      py::module::import("gc").attr("collect")();
    } catch (py::error_already_set const &e) {
      std::cerr << "Navascript Python error: " << e.what() << std::endl;
    }
  };

  std::string Version() {
    if (!flag_once_.IsSignaled()) {
      py::scoped_interpreter guard{};
      version_ =
          std::string(py::str(py::module::import("sys").attr("version_info")));
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
