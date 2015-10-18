#!/usr/bin/env node

// Uses ACE to add syntax highlighting to snippets.
// The language is chosen by the input's file extension.
// See ./readme.md on how to get this running.

var fs = require("fs");
var process = require("process");
var path = require("path");

var printErrorAndAbort = function(error_message) {
  console.error(error_message);
  process.exit(1);
}

// Expect the Ace project directory to be reachable via ./ace/ by default.
var acePath = __dirname + "/ace";

process.argv.length == 4 || printErrorAndAbort(
    "Usage: " + path.basename(__filename) + " <file-input> <file-output>\n\n" +
    "Reads content from <file-input>, adds syntax highlighting and " +
    "writes output to <file-output>.\n" +
    "Expects the Ace project directory to be located at " + acePath + ".");

require("amd-loader");
var highlighter = require(acePath + "/lib/ace/ext/static_highlight");
var theme = require(acePath + "/lib/ace/theme/clouds");

var fileInput = process.argv[2];
var fileOutput = process.argv[3];

fs.readFile(fileInput, "utf8", function(err, data) {
  err && printErrorAndAbort(err);

  // Remove the last newline, if it exists.
  // Editors usually insert a newline at the end of a file, and the easiest
  // way to get rid of it is here. Annotated empty lines are nonsense in my
  // use case.
  if( data.slice(-1) == '\n' ) data = data.slice(0, -1);

  var mode = fileInput.split('.').pop();
  var ModeByFext = require(acePath + "/lib/ace/mode/" + mode).Mode;

  var highlighted = highlighter.render(
    data,
    new ModeByFext(),
    theme,
    /* lineStart: */ 1,
    /* disableGutter: */ true
  );

  fs.writeFile(fileOutput, highlighted.html, function(err) {
    err && printErrorAndAbort(err);
  });
});

