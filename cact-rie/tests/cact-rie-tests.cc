//
// Created by creeper on 7/26/24.
//
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <format>
#include <antlr-runtime/antlr4-runtime.h>
#include <cact-front-end/CactLexer.h>
#include <cact-front-end/CactParser.h>
#include <cact-front-end/cact-syntax-error-listener.h>

struct TestCase {
  std::filesystem::path path;

  // the path points to a filename, which will always be in the following format:
  // <index>_<expected_result>_<test_name>.cact
  int index() const {
    std::string filename = path.filename().string();
    size_t underscore_pos = filename.find('_');
    return std::stoi(std::string(filename.substr(0, underscore_pos)));
  }

  bool expectedResult() const {
    std::string filename = path.filename().string();
    std::string_view filename_view = filename;
    size_t first_underscore = filename_view.find('_');
    size_t second_underscore = filename_view.find('_', first_underscore + 1);
    std::string_view result_view = filename_view.substr(first_underscore + 1, second_underscore - first_underscore - 1);
    return result_view == "true";
  }

  [[nodiscard]] std::string testName() const {
    std::string filename = path.filename().string();
    size_t second_underscore = filename.find('_', filename.find('_') + 1);
    size_t dot_pos = filename.find('.');
    return filename.substr(second_underscore + 1, dot_pos - second_underscore - 1);
  }

  [[nodiscard]]
  std::string testSuiteName() const {
    std::string parent_dir_name = path.parent_path().filename().string();
    size_t underscore_pos = parent_dir_name.find('_');
    return parent_dir_name.substr(underscore_pos + 1);
  }
};

std::optional<std::vector<TestCase>> fetchTestSuite(const std::string &test_suite_name) {
  std::string test_suite_dir_name = std::format("{}/samples_{}", TEST_SUITES_DIR, test_suite_name);
  // run through the directory and fetch all the files
  std::vector<TestCase> test_cases;
  // if cannot open the directory, return an empty optional
  if (!std::filesystem::exists(test_suite_dir_name)) {
    std::cerr << "Warning: Test suite " << test_suite_name << " does not exist. Skip." << std::endl;
    return std::nullopt;
  }
  for (const auto &entry : std::filesystem::directory_iterator(test_suite_dir_name)) {
    if (entry.is_regular_file())
      test_cases.push_back({.path = entry.path()});
    else
      std::cerr << "Warning: skipping non-regular file " << entry.path() << std::endl;
  }
  auto compare = [](const TestCase &lhs, const TestCase &rhs) {
    return lhs.index() < rhs.index();
  };
  std::sort(test_cases.begin(), test_cases.end(), compare);
  return test_cases;
}

bool runCompiler(const std::filesystem::path &test_case_path) {
  std::ifstream stream(test_case_path);
  if (!stream) {
    std::cerr << "Failed to open file: " << test_case_path << std::endl;
    return false;
  }
  antlr4::ANTLRInputStream input(stream);
  cactfrontend::CactLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  cactfrontend::CactParser parser(&tokens);
  lexer.removeErrorListeners();
  parser.removeErrorListeners();
  cactfrontend::CactSyntaxErrorListener cact_error_listener(test_case_path);
  lexer.addErrorListener(&cact_error_listener);
  parser.addErrorListener(&cact_error_listener);
  try {
    antlr4::tree::ParseTree *tree = parser.compilationUnit();
    if (cact_error_listener.hasSyntaxError()) {
      std::cerr << "Syntax error(s) found in the source file. Compilation failed." << std::endl;
      return false;
    }
  } catch (const std::exception &ex) {
    std::cerr << "Parsing failed: " << ex.what() << std::endl;
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> test_suites;
  for (int i = 1; i < argc; i++)
    test_suites.push_back(argv[i]);
  std::vector<TestCase> failed_test_cases;
  int total_test_cases = 0;
  for (const auto &test_suite : test_suites) {
    std::optional<std::vector<TestCase>> test_cases = fetchTestSuite(test_suite);
    bool all_passed = true;
    if (!test_cases.has_value())
      continue;
    total_test_cases += test_cases->size();
    for (const auto &test_case : test_cases.value()) {
      std::cout << "Running test case " << test_case.index() << " " << test_case.testName() << " ... ";
      // run the test case
      bool result = runCompiler(test_case.path);
      std::cout << std::format("Expected: {}, Actual: {}", test_case.expectedResult(), result) << std::endl;
      if (result == test_case.expectedResult())
        std::cout << "PASSED" << std::endl;
      else {
        std::cout << "FAILED" << std::endl;
        failed_test_cases.push_back(test_case);
        all_passed = false;
      }
    }
    if (!all_passed)
      std::cout << std::format("Oops, {} out of {} test cases in test suite {} failed", failed_test_cases.size(), test_cases->size(), test_suite) << std::endl;
    else
      std::cout << std::format("Hooray! All the {} test cases in test suite {} passed!", test_cases->size(), test_suite) << std::endl;
  }
  if (failed_test_cases.empty()){
    std::cout << "Hooray! You passed all the tests!" << std::endl;
    return 0;
  }
  else
    std::cout << "Oops, you failed some test cases. Here are the details:\n" << std::endl;
  std::cout << std::format("In total {} out of {} test cases failed:\n", failed_test_cases.size(), total_test_cases) << std::endl;
  for (const auto &test_case : failed_test_cases)
    std::cout << std::format("Failed test case {}-{} in test suite {}.\n", test_case.index(), test_case.testName(), test_case.testSuiteName());
}