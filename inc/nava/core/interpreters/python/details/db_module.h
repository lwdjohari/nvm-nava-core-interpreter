#ifndef NAVA_CORE_INTERPRETERS_PYTHON_DETAILS_V2_DB_MODULE_H
#define NAVA_CORE_INTERPRETERS_PYTHON_DETAILS_V2_DB_MODULE_H

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

struct Db {
  std::string driver;
  std::string db;
  std::string username;
  std::string password;
  std::string pass_file;
  std::string host;
  std::int16_t port;
  int16_t is_use_pass_file;

  Db(const std::string& driver, const std::string& db,
     const std::string& username, const std::string& password,
     const std::string& pass_file, const std::string& host, std::int16_t port,
     int16_t is_use_pass_file)
      : driver(driver),
        db(db),
        username(username),
        password(password),
        host(host),
        port(port),
        pass_file(pass_file),
        is_use_pass_file(is_use_pass_file) {}
};

PYBIND11_EMBEDDED_MODULE(navascript_database, m) {
  py::class_<Db> db(m, "Db");
  db.def(py::init<const std::string&, const std::string&, const std::string&,
                  const std::string&, const std::string&, const std::string&,
                  std::int16_t, int16_t>())
      .def_readwrite("driver", &Db::driver)
      .def_readwrite("db", &Db::db)
      .def_readwrite("username", &Db::username)
      .def_readwrite("password", &Db::password)
      .def_readwrite("pass_file", &Db::pass_file)
      .def_readwrite("host", &Db::host)
      .def_readwrite("port", &Db::port)
      .def_readwrite("is_use_pass_file", &Db::is_use_pass_file);
}

}  // namespace details
}  // namespace python
}  // namespace interpreters
}  // namespace core
}  // namespace nava

#endif  // NAVA_CORE_INTERPRETERS_PYTHON_DETAILS_V2_DB_MODULE_H
