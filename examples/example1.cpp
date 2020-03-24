#include "argparse/argparse.hpp"

int main(int argc, char **argv) {

  // A parser object
  Parser p;

  // Program data corresponding to flags, options, and positional arguments
  bool verbose = false;
  std::string toPrint;
  std::string maybePrint;
  int repeats = 1;

  // Inform the parser of the program data.
  // It will do type-specific conversion
  p.add_option(repeats, "--repeat");
  p.add_flag(verbose, "--verbose", "-v");
  p.add_positional(toPrint)->required();
  auto psnl = p.add_positional(maybePrint);

  // If there was an error during parsing, report it.
  if (!p.parse(argc, argv)) {
    std::cerr << p.help();
    exit(EXIT_FAILURE);
  }

  // Execute the program logic
  if (verbose) {
    std::cerr << "about to print '" << toPrint << "' " << repeats << " times";
    if (psnl->found()) {
      std::cerr << ", then '" << maybePrint << "'";
    }
    std::cerr << std::endl;
  }

  for (int i = 0; i < repeats; ++i) {
    std::cout << toPrint;
  }
  if (psnl->found()) {
    std::cout << maybePrint;
  }
  std::cout << std::endl;

  return 0;
}