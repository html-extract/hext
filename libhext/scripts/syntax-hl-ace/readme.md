syntax-hl-ace.js
================

Applies ACE Code Editor's syntax highlighting.
Consumes files containing code snippets, uses the file extension
to determine the edit mode, writes HTML containing syntax
highlighted code.


#### Install dependencies

    npm install


#### Clone ace

    git clone https://github.com/ajaxorg/ace.git


#### Copy the hext edit mode from /syntaxhl/ace into ace

    cp ../../../syntaxhl/ace/*.js ace/lib/ace/mode/


#### Build ace

    cd ace
    npm install
    node ./Makefile.dryice.js
    cd ..


#### Test hext edit mode

    ./hext-syntax-hl-ace.js ../../../test/case/doxygen-annotated-class-list.hext /tmp/hext-test
    cat /tmp/hext-test

