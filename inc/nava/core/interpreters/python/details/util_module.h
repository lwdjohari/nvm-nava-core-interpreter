#ifndef NAVA_CORE_INTERPRETERS_PYTHON_DETAILS_V2_UTIL_MODULE_H
#define NAVA_CORE_INTERPRETERS_PYTHON_DETAILS_V2_UTIL_MODULE_H

#include <pybind11/embed.h>

#include <cstddef>
#include <cstdint>
#include <string>

namespace nava {
namespace core {
namespace interpreters {
namespace python {
namespace details {

namespace py = pybind11;

void Writeln(const std::string& val) { 
    py::gil_scoped_release release;

    std::string v = std::string(val);
    std::cout << v << std::endl; 
    
    py::gil_scoped_acquire acquire;
    };

PYBIND11_EMBEDDED_MODULE(navascript_console, m) {
  m.def("Writeln", &Writeln);
}

}  // namespace details
}  // namespace python
}  // namespace interpreters
}  // namespace core
}  // namespace nava
#endif