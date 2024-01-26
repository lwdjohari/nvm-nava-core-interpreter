#ifndef NAVA_CORE_INTERPRETERS_PYTHON_DETAILS_V2_CORE_FUNC_H
#define NAVA_CORE_INTERPRETERS_PYTHON_DETAILS_V2_CORE_FUNC_H

#include <memory>

#include "nava/core/interpreters/python/details/core_obj.h"

namespace nava {
namespace core {
namespace interpreters {
namespace python {
namespace details {

inline std::shared_ptr<CompilerPlugin> LoadCompilerPlugin(
    const std::string &plugin_name, const std::string &path = "") {
  return std::make_shared<CompilerPlugin>(
      std::string(plugin_name),std::string(path), details::PluginTypeOption::Plugin_CompilerPlugin,
      details::PlatformTypeOption::Platform_Backend);
}

// inline std::shared_ptr<RepoPlugin> LoadRepoPlugin(
//     const std::string &plugin_name, const std::string &path = "") {
//   return std::make_shared<RepoPlugin>(
//       plugin_name, path, details::PluginTypeOption::RepoPlugin,
//       details::PlatformTypeOption::Backend);
// }

inline std::shared_ptr<FeatureGroup> CreateFeatures(const std::string &key) {
  return std::make_shared<FeatureGroup>(std::string(key));
};

inline void Terminate(const std::string &message) {
  py::gil_scoped_release release;
  std::string local = std::string(message);
  std::cout << "[TERMINATE] " << local << std::endl;
  Py_FinalizeEx();
};

}  // namespace details
}  // namespace python
}  // namespace interpreters
}  // namespace core
}  // namespace nava

#endif  // NAVA_CORE_INTERPRETERS_PYTHON_DETAILS_V2_CORE_FUNC_H
