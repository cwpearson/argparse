# argparse

[![Build Status](https://travis-ci.com/cwpearson/argparse.svg?branch=master)](https://travis-ci.com/cwpearson/argparse)

Simple single-file header-only CLI option parsing for C++.
No subcommands or grouped commands.
Only supports `-s value`/`--long-option value` style for options.
Only supports `--long-flag` style for flags.

## Getting Started

Download the latest [`argparse.hpp`](www.google.com) and include it in your project.

## Features

- [x] allow (default) / disallow (`Parser::no_unrecognize()`) unrecognized options and flags
- [x] optional/required (`PosnlBase::required()`) positional arguments
- [x] flags with `-s`, `--long-flag` formats
- [x] options with `--long-opt val` format
- [x] positional arguments
- [x] `--` to stop parsing options and flags
- [x] modify `argc`/`argv` (disable with `Parser::no_consume()`)
- Option/Positional Argument Types
  - [x] `int`
  - [x] `size_t`
  - [x] `float`
  - [x] `double`
  - [x] `std::string`

## Examples

```c++
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
```

## Roadmap

- [ ] Reject duplicate flags / options
- [ ] Help string output
- [ ] support --long-option=value
- [ ] have the last positional argument fill a vector with remaining
