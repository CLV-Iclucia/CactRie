//
// Created by creeper on 11/30/24.
//

#ifndef CACTRIE_CACT_FRONT_END_INCLUDE_CACT_FRONT_END_LLVM_IR_FORMATTER_H
#define CACTRIE_CACT_FRONT_END_INCLUDE_CACT_FRONT_END_LLVM_IR_FORMATTER_H
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
namespace cactfrontend {
class LLVMIRFormatter {
public:
  explicit LLVMIRFormatter(int indent_size = 4)
      : indent_size_(indent_size), output_stream_(&std::cout), in_function(false) {}

  void setOutputStream(std::ostream &os) {
    output_stream_ = &os;
  }

  void format(std::istream &input_stream) {
    std::string line;
    while (std::getline(input_stream, line)) {
      line = trim(line);

      if (line.empty())
        continue;

      if (line == "{") {
        in_function = true;
        outputLine(line);
        continue;
      }
      else if (line == "}") {
        in_function = false;
        outputLine(line);
        continue;
      }

      if (line.substr(0, 7) == "declare" || line.substr(0, 5) == "define")
        outputLine("");

      if (line.find(":") != std::string::npos)
        handleLabel(line);
      else if (in_function)
        handleInstruction(line);
      else
        outputLine(line);
    }
  }

private:
  int indent_size_;
  std::ostream *output_stream_;
  bool in_function;

  std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
  }

  void outputLine(const std::string &line, int indent_level = 0) {
    for (int i = 0; i < indent_level; i++)
      *output_stream_ << std::string(indent_size_, ' ');
    *output_stream_ << line << std::endl;
  }

  void handleLabel(const std::string &line) {
    outputLine(line.at(0) == '.' ? line.substr(1) : line, 1);
  }

  void handleInstruction(const std::string &line) {
    std::regex label_pattern(R"(label %\.\w+)");
    std::string new_line = std::regex_replace(line, label_pattern, "label %$1");
    outputLine(new_line, 2);
  }

  void handleEmptyLine() {
    outputLine("");
  }
};

}
#endif //CACTRIE_CACT_FRONT_END_INCLUDE_CACT_FRONT_END_LLVM_IR_FORMATTER_H
