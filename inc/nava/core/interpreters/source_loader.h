#ifndef NAVA_CORE_INTERPRETERS_V2_SOURCE_LOADER_H
#define NAVA_CORE_INTERPRETERS_V2_SOURCE_LOADER_H

#include <codecvt>
#include <fstream>
#include <locale>
#include <stdexcept>

namespace nava {
namespace core {
namespace interpreters {

class SourceLoader {
 private:
  std::wstring fileName;

 public:
  SourceLoader(const std::wstring& fileName) : fileName(fileName) {}

  std::wstring LoadUtf8TextFile() {
    std::wifstream file(fileName, std::: ios::binary);
    if (!file) {
      throw std::runtime_error("Failed to open file: " + fileName);
    }

    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    std::wstringstream buffer;
    buffer << file.rdbuf();

    return std::move(buffer.str());
  }
};
}  // namespace interpreters
}  // namespace core
}  // namespace nava

#endif  // NAVA_CORE_INTERPRETERS_V2_SOURCE_LOADER_H
