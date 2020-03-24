# argparse

[![Build Status](https://travis-ci.com/cwpearson/argparse.svg?branch=master)](https://travis-ci.com/cwpearson/argparse)

Simple single-file header-only CLI option parsing for C++.
No subcommands, grouped commands.

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
- Option Types
  - [x] `int`
  - [x] `size_t`
  - [x] `float`
  - [x] `double`
  - [x] `std::string`

## Roadmap

- [ ] examples
- [ ] Help string output
- [ ] support --long-option=value
- [ ] have the last positional argument fill a vector with remaining
