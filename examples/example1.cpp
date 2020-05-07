#include "argparse/argparse.hpp"

int main(int argc, char **argv) {

  // A parser object
  argparse::Parser p;

  // Program data corresponding to flags, options, and positional arguments
  bool verbose = false;
  std::string toPrint;
  std::string maybePrint;
  int repeats = 2;

  // Inform the parser of the program data. It will do type-specific conversion
  // from string.

  // An option invoked with `--repeat N`
  p.add_option(repeats, "--repeat")
      ->help("how many times to repeat first argument");
  // A flag invoked with `--verbose` or `-v`
  p.add_flag(verbose, "--verbose", "-v");
  // a required positional argument (position 1)
  p.add_positional(toPrint)->required();
  // an optional positional argument (position 2)
  auto psnl = p.add_positional(maybePrint);

  // If there was an error during parsing, report it.
  if (!p.parse(argc, argv)) {
    std::cerr << p.help();
    exit(EXIT_FAILURE);
  }

  // If help was requested, print it
  if (p.need_help()) {
    std::cerr << p.help();
    return 0;
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