#ifndef NAVA_CORE_INTERPRETERS_PYTHON_DETAILS_V2_CORE_MODULE_H
#define NAVA_CORE_INTERPRETERS_PYTHON_DETAILS_V2_CORE_MODULE_H

#include <pybind11/embed.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "nvm/vector_ex.h"

namespace nava {
namespace core {
namespace interpreters {
namespace python {
namespace details {

namespace py = pybind11;

enum PluginTypeOption {
  Plugin_None = 0,
  Plugin_CompilerPlugin = 1,
  Plugin_RepoPlugin = 2,
  Plugin_ServicePlugin = 3,
  Plugin_UIPlugin = 4,
  Plugin_ValidationPlugin = 5
};

enum class PlatformTypeOption {
  Platform_None = 0,
  Platform_Backend = 1,
  Platform_Web = 2,
  Platform_Mobile = 3,
  Platform_Desktop = 4
};

static std::string PluginTypeAsString(const PluginTypeOption &pluginType) {
  switch (pluginType) {
    case PluginTypeOption::Plugin_CompilerPlugin:
      return "Compiler-plugin";
    case PluginTypeOption::Plugin_RepoPlugin:
      return "Repo-plugin";
    case PluginTypeOption::Plugin_ServicePlugin:
      return "Service-plugin";
    case PluginTypeOption::Plugin_UIPlugin:
      return "UI-plugin";
    case PluginTypeOption::Plugin_ValidationPlugin:
      return "Validation-plugin";
    default:
      return "";
  }
};

static std::string PlatformTypeAsString(
    const PlatformTypeOption &platformType) {
  switch (platformType) {
    case PlatformTypeOption::Platform_Backend:
      return "Backend";
    case PlatformTypeOption::Platform_Web:
      return "Web";
    case PlatformTypeOption::Platform_Mobile:
      return "Mobile";
    case PlatformTypeOption::Platform_Desktop:
      return "Desktop";
    default:
      return "";
  }
};

class Plugin {
 private:
  std::string name_;
  std::string path_;
  PluginTypeOption pluginType_;
  PlatformTypeOption platformType_;
  bool is_loaded_;

 protected:
  void SetIsLoaded(bool is_loaded) { is_loaded_ = is_loaded; }

 public:
  Plugin(const std::string &name, const std::string &path,
         PluginTypeOption pluginType, PlatformTypeOption platformType)
      : name_(name),
        path_(path),
        pluginType_(pluginType),
        platformType_(platformType),
        is_loaded_(false){};

  virtual ~Plugin(){};

  std::string Name() const { return name_; }

  std::string Path() const { return path_; }

  PluginTypeOption PluginType() const { return pluginType_; }

  PlatformTypeOption PlatformType() const { return platformType_; }

  bool IsLoaded() const { return is_loaded_; }

  std::string CoreVersion() const { return ""; }

  std::string PluginVersion() const { return ""; }

  void PrintStatus() const {
    if (is_loaded_) {
      std::cout << "- " << Name() << "{ver = " << PluginVersion() << ";"
                << " type = " << PluginTypeAsString(PluginType()) << "; "
                << " platform =" << PlatformTypeAsString(PlatformType()) << "; "
                << " core = " << CoreVersion() << "}" << std::endl;
    } else {
      std::cout << "- " << Name() << " failed to load!" << std::endl;
    }
  }
};

class CompilerPlugin : public Plugin {
 public:
  CompilerPlugin(const std::string &name, const std::string &path,
                 PluginTypeOption pluginType, PlatformTypeOption platformType)
      : Plugin(name, path, pluginType, platformType){};
  ~CompilerPlugin(){};
};

class RepoPlugin : public Plugin {
 public:
  RepoPlugin(const std::string &name, const std::string &path,
             PluginTypeOption pluginType, PlatformTypeOption platformType)
      : Plugin(name, path, pluginType, platformType) {}

  ~RepoPlugin(){};
};

class ServicePlugin : public Plugin {
 public:
  ServicePlugin(const std::string &name, const std::string &path,
                PluginTypeOption pluginType, PlatformTypeOption platformType)
      : Plugin(name, path, pluginType, platformType) {}
  ~ServicePlugin(){};
};

class UIPlugin : public Plugin {
 private:
 public:
  UIPlugin(const std::string &name, const std::string &path,
           PluginTypeOption pluginType, PlatformTypeOption platformType)
      : Plugin(name, path, pluginType, platformType) {}
  ~UIPlugin(){};
};

class ValidationPlugin : public Plugin {
 public:
  ValidationPlugin(const std::string &name, const std::string &path,
                   PluginTypeOption pluginType, PlatformTypeOption platformType)
      : Plugin(name, path, pluginType, platformType) {}

  ~ValidationPlugin(){};
};

class FeatureGroupItem {
  std::vector<std::shared_ptr<Plugin>> plugins_;
  std::string key_;
  std::string caption_;

 public:
  FeatureGroupItem(const std::string &key, const std::string &caption)
      : plugins_(std::vector<std::shared_ptr<Plugin>>()),
        key_(std::string(key)),
        caption_(std::string(caption)){};
  ~FeatureGroupItem(){

  };

  std::string Key() const { return key_; }

  std::string Caption() const { return caption_; }

  void Add(std::shared_ptr<Plugin> plugin) {
    plugins_.emplace_back(std::move(plugin));
  }

  void CleanUp() { plugins_.clear(); }

  void PrintStatus() const {
    std::cout << "\nFeature: " << key_ << " (" << caption_ << ")." << std::endl;
    if (plugins_.size() == 0) {
      std::cout << "- No plugin loaded!" << std::endl;
    } else {
      for (auto &p : plugins_) {
        p->PrintStatus();
      }
    }
  }
};

class FeatureGroup {
 private:
  std::string key_;
  std::vector<std::shared_ptr<FeatureGroupItem>> features_;

 public:
  FeatureGroup(const std::string &key)
      : key_(std::string(key)),
        features_(std::vector<std::shared_ptr<FeatureGroupItem>>()) {}

  ~FeatureGroup() {}

  std::shared_ptr<FeatureGroupItem> Create(const std::string &name,
                                           const std::string &caption) {
    features_.emplace_back(std::make_shared<FeatureGroupItem>(
        std::string(name), std::string(caption)));

    return features_.back();
  }

  std::shared_ptr<FeatureGroupItem> Feature(const std::string &key) {
    // return features_.at(0);
    auto res = nvm::vectorex::FindInVectorPointerByMethodValue(
        features_, key, &FeatureGroupItem::Key);

    if (res.first) {
      return features_.at(res.second);
    } else {
      return nullptr;
    }
  }

  std::vector<std::shared_ptr<FeatureGroupItem>> Features() {
    return features_;
  }
  bool Remove(const std::string &key) { return false; }
  void Clear() {
    for (auto &f : features_) {
      f->CleanUp();
    }

    features_.clear();
  }

  size_t Size() { return features_.size(); }
};

}  // namespace details
}  // namespace python
}  // namespace interpreters
}  // namespace core
}  // namespace nava
#endif