# Hext — Extract Data from HTML
Hext is a domain-specific language for extracting structured data from
HTML documents.  

![Hext Logo](https://raw.githubusercontent.com/thomastrapp/hext-website/master/hext-logo-x100.png)

See http://hext.thomastrapp.com for
[documentation](http://hext.thomastrapp.com/documentation), 
[build instructions](http://hext.thomastrapp.com/download) and a live demo.

The Hext project is released under the terms of the Apache License v2.0.

## Example
Suppose you want to extract all hyperlinks from a web page. Hyperlinks have an
anchor tag &lt;a&gt;, an attribute called href and a text that visitors can
click. The following Hext snippet will produce a dictionary for every matched
element. Each dictionary will contain the keys `link` and `title` which refer
to the href attribute and the text content of the matched &lt;a&gt;.

    # Extract links and their text
    <a href:link @text:title />

[&raquo; Load example in editor](http://hext.thomastrapp.com/#attribute)

Visit [Hext's project page](http://hext.thomastrapp.com) to learn more about
Hext. For examples that use the libhext C++ library check out `/libhext/examples`
and the
[main page of the doxygen documentation](http://hext.thomastrapp.com/libhext-documentation).

## Quick Install via Pip

You can install the htmlext command-line utility and the python bindings through pip:

    pip install hext
    htmlext --version

Visit [https://pypi.org/project/hext/](https://pypi.org/project/hext/).

## Components
* `htmlext`: Command line utility that applies Hext snippets to an HTML document
  and produces JSON.
* `libhext`: C++ library that contains a Hext parser but also allows for
  customization.
* `libhext-test`: Unit tests for libhext.
* `Hext bindings`: Bindings for scripting languages. There are extensions for
  Node.js, Python, Ruby and PHP that are able to parse Hext and extract values
  from HTML.

## Project layout
    ├── build             Build directory for htmlext
    ├── cmake             CMake modules used by the project
    ├── htmlext           Source for the htmlext command line tool
    ├── libhext           The libhext project
    │   ├── bindings      Hext bindings for scripting languages
    │   ├── build         Build directory for libhext
    │   ├── doc           Doxygen documentation for libhext
    │   ├── examples      Examples making use of libhext
    │   ├── include       Public libhext API
    │   ├── ragel         Ragel input files
    │   ├── scripts       Helper scripts for libhext
    │   ├── src           libhext implementation files
    │   └── test          The libhext-test project
    │       ├── build     Build directory for libhext-test
    │       └── src       Source for libhext-test
    ├── man               Htmlext man page
    ├── scripts           Scripts for building and testing releases
    ├── syntaxhl          Syntax highlighters for Vim and ACE
    └── test              Blackbox tests for htmlext

## Dependencies for development
* [Ragel](http://www.colm.net/open-source/ragel/) generates the state machine
  that is used to parse Hext
* The unit tests for libhext are written with
  [Google Test](https://github.com/google/googletest)
* libhext's public API documentation is generated by
  [Doxygen](http://www.stack.nl/~dimitri/doxygen/)
* libhext's scripting language bindings are generated by
  [Swig](http://www.swig.org/)

## Tests
There are unit tests for libhext and blackbox tests for Hext as a language,
whose main purpose is to detect unwanted change in syntax or behavior.  
The libhext-test project is located in `/libhext/test` and depends on Google
Test. Nothing fancy, just build the project and run the executable
`libhext-test`. How to write test cases with Google Test is described
[here](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md).  
The blackbox tests are located in `/test`. There you'll find a shell script
called `blackbox.sh`. This script applies Hext snippets to HTML documents and
compares the result to a third file that contains the expected output. For
example, there is a test case `icase-quoted-regex` that consists of three files:
`icase-quoted-regex.hext`, `icase-quoted-regex.html`, and
`icase-quoted-regex.expected`. To run this test case you would do the following:

    $ ./blackbox.sh case/icase-quoted-regex.hext

`blackbox.sh` will then look for the corresponding `.html` and `.expected` files
of the same name in the directory of `icase-quoted-regex.hext`. Then it will
invoke `htmlext` with the given Hext snippet and HTML document and compare the
result to `icase-quoted-regex.expected`. To run all blackbox tests in
succession:

    $ ./blackbox.sh case/*.hext

By default `blackbox.sh` will look for the `htmlext` binary in `$PATH`. Failing
that, it looks for the binary in the default build directory. You can tell
`blackbox.sh` which command to use by setting HTMLEXT. For example, to run all
tests through valgrind you'd run the following:

    $ HTMLEXT="valgrind -q ../build/htmlext" ./blackbox.sh case/*.hext

## Acknowledgements
* [Gumbo](https://github.com/google/gumbo-parser)
  — **An HTML5 parsing library in pure C99**  
  Gumbo is used as the HTML parser behind `hext::Html`. It's fast, easy to
  integrate and even fixes invalid HTML.
* [Ragel](http://www.colm.net/open-source/ragel/)
  — **Ragel State Machine Compiler**  
  The state machine that is used to parse Hext snippets is generated by Ragel.
  You can find the definition of this machine in `/libhext/ragel/hext-machine.rl`.
* [RapidJSON](http://rapidjson.org/)
  — **A fast JSON parser/generator for C++**  
  RapidJSON powers the JSON output of the `htmlext` command line utility.
* [jq](https://stedolan.github.io/jq/)
  — **A lightweight and flexible command-line JSON processor**  
  An indispensable tool when dealing with JSON in the shell.
  Piping the output of `htmlext` into `jq` lets you do all sorts of crazy things.
* [Ace](https://ace.c9.io/) — **A Code Editor for the Web**  
  Used as the code editor in the
  "[Try Hext in your Browser!](http://hext.thomastrapp.com)" section and as a
  highlighter for all code examples. The highlighting rules for Hext are
  included in this project in `/syntaxhl/ace`. Also, there's a script in
  `/libhext/scripts/syntax-hl-ace` that uses Ace to transform a code snippet
  into highlighted HTML.
* [Proxygen](https://github.com/facebook/proxygen)
  — **A collection of C++ HTTP libraries including an easy to use HTTP server**  
  The HTTP server behind the "[Try Hext in your Browser!](http://hext.thomastrapp.com)"
  section is built with proxygen.

## Licensing

All source code of the Hext project is released under the Apache License v2.0,
with the sole exception of `/libhext/doc/doxygen/resources/bootstrap.min.css`,
which was authored by a third party and is included in this project under the
terms of the MIT license. See
`/libhext/doc/doxygen/resources/bootstrap.min.css.LICENSE` for the full license
text. Visit Bootstrap on [Github](https://github.com/twbs/bootstrap).

## About me
I am a freelancing software developer living in Munich. Visit
[thomastrapp.com](http://thomastrapp.com) for my email address and let me know
what you think about Hext!

