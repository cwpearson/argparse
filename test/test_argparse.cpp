#include "catch2/catch.hpp"

#include <iostream>

#include "argparse/argparse.hpp"

TEST_CASE("argparse") {

  SECTION("no args") {
    char ** argv = nullptr;
    int argc = 0;
    argparse::Parser p;
    REQUIRE(p.parse(argc, argv));
  }

  SECTION("null argv[0]") {
    char *argv[] = {nullptr};
    int argc = sizeof(argv) / sizeof(argv[0]);
    argparse::Parser p;
    REQUIRE(p.parse(argc, argv));
  }

  SECTION("types") {
    char *argv[] = {
        "some-exe", "--campi", "--f", "10", "1.7", "1.8",
        "--", // stop looking for options
        "--a string",
        "-6",
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    argparse::Parser p;

    bool campi = false;
    size_t x;
    double d;
    float f;
    int i;
    std::string s;
    p.add_flag(campi, "--campi");
    p.add_positional(x);
    p.add_positional(d);
    p.add_positional(f);
    p.add_positional(s);
    p.add_positional(i);
    REQUIRE(p.parse(argc, argv));

    REQUIRE(campi == true);
    REQUIRE(x == 10);
    REQUIRE(d == 1.7);
    REQUIRE(f == 1.8f);
    REQUIRE(s == "--a string");
    REQUIRE(i == -6);
    REQUIRE(p.need_help() == false);

    REQUIRE(argc == 2); // does not use --f or some-exe
  }


  SECTION("description") {
    char *argv[] = {
        "some-exe",
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    argparse::Parser p("a test program");
    REQUIRE(p.parse(argc, argv));
  }

  SECTION("skip-first") {
    char *argv[] = {"some-exe"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    argparse::Parser p;
    p.no_unrecognized();
    REQUIRE(p.parse(argc, argv));
  }

  SECTION("no-unrecognized") {
    char *argv[] = {"some-exe", "-f"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    argparse::Parser p;
    p.no_unrecognized();
    REQUIRE(false == p.parse(argc, argv));
  }

  SECTION("missing-reqd-posnl") {
    char *argv[] = {"some-exe", "a"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    std::string a;
    std::string b;

    argparse::Parser p;
    p.add_positional(a)->required();
    p.add_positional(b)->required();
    REQUIRE(false == p.parse(argc, argv));
  }

  SECTION("-h") {
    char *argv[] = {"some-exe", "-h"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    argparse::Parser p;
    REQUIRE(true == p.parse(argc, argv));
    REQUIRE(p.need_help());
  }

  SECTION("--help") {
    char *argv[] = {"some-exe", "--help"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    argparse::Parser p;
    REQUIRE(true == p.parse(argc, argv));
    REQUIRE(p.need_help());
  }

  SECTION("--help") {
    char *argv[] = {"some-exe", "--help", "--"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    argparse::Parser p;
    REQUIRE(true == p.parse(argc, argv));
    REQUIRE(p.need_help());
  }

  SECTION("double --") {
    char *argv[] = {"some-exe", "--flag", "--", "--", "aa"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    std::string a,b;
    bool flag = false;

    argparse::Parser p;
    p.add_flag(flag, "--flag");
    p.add_positional(a);
    p.add_positional(b);


    REQUIRE(true == p.parse(argc, argv));
    REQUIRE(!p.need_help());

    REQUIRE(a == "--");
    REQUIRE(b == "aa");
    REQUIRE(flag == true);

  }

  SECTION("-- in option") {
    char *argv[] = {"some-exe", "--option", "--", "--", "aa"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    std::string a, option;

    argparse::Parser p;
    p.add_option(option, "--option");
    p.add_positional(a);


    REQUIRE(true == p.parse(argc, argv));
    REQUIRE(!p.need_help());

    REQUIRE(a == "aa");
    REQUIRE(option == "--");

  }

}
