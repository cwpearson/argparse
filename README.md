# argparse

[![Build Status](https://travis-ci.com/cwpearson/argparse.svg?branch=master)](https://travis-ci.com/cwpearson/argparse)

Simple single-file header-only CLI option parsing for C++ that does not require a working `std::regex`.

## Getting Started

Download the latest [`argparse.hpp`](https://raw.githubusercontent.com/cwpearson/argparse/master/include/argparse/argparse.hpp) and include it in your project.

## Example

```c++
#include "argparse/argparse.hpp"

int main(int argc, char **argv) {

  // A parser object
  argparse::Parser p;

  // Program data corresponding to flags, options, and positional arguments
  bool verbose = false;
  std::string toPrint;
  std::string maybePrint;
  int repeats = 2;

  // Inform the parser of the program data. It will do type-specific conversionfrom string.

  // An option invoked with `--repeat N`
  p.add_option(repeats, "--repeat")->help("how many times to repeat first argument");
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
```

## Adding Options

Options may be `int32_t`, `int64_t`, `size_t`, `float`, `double`, or `std::string`.
They are invoked like `--long-opt value` (not `--long-opt=value`) or `-s value`, if provided.
If they are not present, the value is not modified.

```c++
int var1 = 3; // a default value for var1
argparse::Parser p;
p.add_option(var1, "--long-opt");
p.add_option(var2, "--long-opt, -s");
p.add_option(var3, "--long-opt, -s")->help("a demo option");
```

## Adding Flags

Flags are always `bool`s, and currently support long or short strings.
The boolean variable is ALWAYS set to `true` if the flag is found.
They are invoked like `--long-flag` (not `--long-flag=true` or `--long-flag true`) or `-s`, if provided.

```c++
argparse::Parser p;
p.add_option(flag1, "--long-flag")
p.add_option(flag2, "--another-flag", "-s");
p.add_option(flag3, "--another-flag", "-s")->help("a demo flag");
```

## Positional Arguments

Positional arguments are added in order.
Positional arguments are optional by default.
Use `required()` to require them.
`add_positional()` returns a `PosnlBase *` that may be queried with `found()` to see if an optional positional argument was found.

```c++
argparse::Parser p;
p.add_positional(var1)->required();
auto something = p.add_positional(var2);
if (something->found()) {
  // var2 was set
}
```

Anything after `--` is considered a positional argument, unless `--` follows an option.
Here, the first `--` is the value for `--option` and will be in `s1`.
The second `--` marks the beginning of positional arguments. and the string `aa` will be in `s2`.

```c++
argparse::Parser p;
std::string s1, s2;
p.add_option(s1, "--option");
p.add_positional(s2);
std::cerr << s1;
std::cerr << s2;
```

```bash
$ ./myexe --option -- -- aa
--aa
```

## Parsing
```c++
argparse::Parser p;
// set up flags, arguments, and options
p.parse(argc, argv);
```

`parse()` returns something falsy if there is an error.
Parsing modifies `argc` and `argv` to remove consumed options by default.
To disable, call `p->no_consume()`.
Parsing will silently skip unrecognized arguments.
To error instead, call `p->no_unrecognized()`.

`Parser` provides a constructor that takes a string description.
This description will be added to the usage string.
```c++
argparse::Parser p("a demo argparse CLI app");
// set up flags, arguments, and options
p.parse(argc, argv);
```

## Useage Strings
A `--help` and `-h` flag are automatically added.
`parser::need_help()` returns true if either of those flags are provided.
`parser::help()` returns a string that contains the help output.

```c++
argparse::Parser p;
if (p.need_help()) {
  std::cout << p.help();
}
```

## Features

- [x] Does not require `std::regex`
- [x] allow (default) / disallow (`Parser::no_unrecognized()`) unrecognized options and flags
- [x] optional/required (`PosnlBase::required()`) positional arguments
- [x] flags with `-s`, `--long-flag` formats
- [x] options with `--long-opt val` format
- [x] positional arguments
- [x] `--` to stop parsing options and flags
- [x] modify `argc`/`argv` (disable with `Parser::no_consume()`)
- Option/Positional Argument Types
  - [x] `int32_t`
  - [x] `int64_t`
  - [x] `size_t`
  - [x] `float`
  - [x] `double`
  - [x] `std::string`
- [x] Support short option strings
- [x] Help string output

## Roadmap

- [ ] Runtime error if duplicate flags or options are defined
- [ ] support `--long-option=value`
- [ ] allow the last positional argument to fill an `std::vector`
- [ ] improve help formatting

## License and Copyright

Copyright Carl Pearson 2022

Licensed under Apache 2.0 (see LICENSE for details).