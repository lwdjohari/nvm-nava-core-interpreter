#include <iostream>
#include <memory>

#include "nava/core/interpreters/python/interpreter.h"

int main() {
  std::cout << "\nNVM Codegen v2.0.3-dev-c++17." << std::endl;
  std::cout << "-------------------------------" << std::endl;
  

  auto p =
      std::make_shared<nava::core::interpreters::python::PythonInterpreter>();
  std::cout << "Navascript interpreter: " << p->Version() << std::endl;
  std::cout << "" << std::endl;

  try {
    p->RunPythonEmbedded("navascript/navarun.py");
  } catch (const std::exception& e) {
  }

  std::cout << "\nFinished run..." << std::endl;

  return 0;
}