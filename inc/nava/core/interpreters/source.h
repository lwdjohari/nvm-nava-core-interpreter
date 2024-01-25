#ifndef NAVA_CORE_INTERPRETERS_V2_SOURCE_H
#define NAVA_CORE_INTERPRETERS_V2_SOURCE_H

#include <utf8.h>

#include <string>

#include "nava/core/interpreters/interpreter_language.h"

namespace nava {
namespace core {
namespace interpreters {

class Source {
 private:
  const std::string filepath_;
  const std::string name_;
  std::string content_;
  const bool is_utf8_;
  const InterpreterLanguage language_;
  std::string hash_;
  const bool is_compiled_;

 public:
  Source()
      : filepath_(""),
        name_(""),
        content_(""),
        is_utf8_(false),
        language_(InterpreterLanguage::Unknown),
        hash_(""),
        is_compiled_(false) {}

  Source(const std::string& filepath, const std::string& name,
         const std::string& content, bool is_utf8 InterpreterLanguage language,
         bool is_compiled)
      : filepath_(std::string(filepath)),
        name_(std::string(name)),
        content_(std::string(content)),
        is_utf8_(is_utf8),
        language_(language),
        hash_(""),
        is_compiled_(is_compiled) {}

  // No Copy constructor, to copy must implement ICloneable
  // This make the code explicit and much more readable when copy the object
  Source(const Source&) = delete;

  Source(Source&&) = default;

  ~Source(){};

  std::string Filename() const { return filepath_; }
  std::string Name() const { return name_; }

  std::string& Content() const { return content_; }
  bool& IsUtf8() const { return encoding_; }
  InterpreterLanguage Language() const { return language_; }
  std::string& Hash() const { return hash_; }
  bool IsCompiled() const { return is_compiled_; }
};

}  // namespace interpreters
}  // namespace core
}  // namespace nava

#endif  // NAVA_CORE_INTERPRETERS_V2_SOURCE_H
