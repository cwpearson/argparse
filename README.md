# argparse

[![Build Status](https://travis-ci.com/cwpearson/argparse.svg?branch=master)](https://travis-ci.com/cwpearson/argparse)

Simple single-file header-only CLI option parsing for C++ that does not require a working `std::regex`.

## Getting Started

Download the latest [`argparse.hpp`](https://raw.githubusercontent.com/cwpearson/argparse/latest/include/argparse/argparse.hpp) and include it in your project.

## Example

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

  // Inform the parser of the program data. It will do type-specific conversion
  // from string.

  // An option invoked with `--repeat N`
  p.add_option(repeats, "--repeat");
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

## Adding Options

Options may be `int`, `size_t`, `float`, `double`, or `std::string` and currently support long strings.
They are invoked like `--long-opt value` (not `--long-opt=value`).

```c++
Parser p;
p.add_option(var1, "--long-opt")
```

## Adding Flags

Flags are always `bool`s, and currently support long or short strings.
The boolean variable is ALWAYS set to `true` if the flag is found.
They are invoked like `--long-flag` (not `--long-flag=true` or `--long-flag true`).

```c++
Parser p;
p.add_option(flag1, "--long-flag")
p.add_option(flag2, "--antother-flag", "-s");
```

## Positional Arguments

Positional arguments are added in order.
Positional arguments are optional by default.
Use `required()` to require them.
`add_positional()` returns a `PosnlBase *` that may be queried with `found()` to see if an optional positional argument was found.

```c++
Parser p;
p.add_positional(var1)->required();
auto something = p.add_positional(var2);
if (something->found()) {
  // var2 was set
}
```

## Parsing

```c++
Parser p;
// set up flags, arguments, and options
p.parse(argc, argv);
```

`parse()` returns something falsy if there is an error.

Parsing modifies `argc` and `argv` to remove consumed options by default.
To disable, call `p->no_consume()`.

Parsing will silently skip unrecognized arguments.
To error instead, call `p->no_unrecognized()`.

## Features

- [x] Does not require `std::regex`
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

## Roadmap

- [ ] Reject duplicate flags / options at run time
- [ ] Support short option strings
- [ ] Help string output
- [ ] support --long-option=value
- [ ] have the last positional argument fill a vector with remaining
