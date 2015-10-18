define(function(require, exports, module) {
  "use strict";

  var oop = require("../lib/oop");
  var TextMode = require("./text").Mode;
  var Tokenizer = require("../tokenizer").Tokenizer;
  var MatchingBraceOutdent = require("./matching_brace_outdent").MatchingBraceOutdent;
  var HextHighlightRules = require("./hext_highlight_rules").HextHighlightRules;

  var Mode = function() {
    this.HighlightRules = HextHighlightRules;
    this.$outdent = new MatchingBraceOutdent();
  };
  oop.inherits(Mode, TextMode);

  (function() {
    this.lineCommentStart = "#";

    this.getNextLineIndent = function(state, line, tab) {
      // keep indentation of previous line
      return this.$getIndent(line);
    };

    this.checkOutdent = function(state, line, input) {
      return this.$outdent.checkOutdent(line, input);
    };

    this.autoOutdent = function(state, doc, row) {
      this.$outdent.autoOutdent(doc, row);
    };
  }).call(Mode.prototype);

  exports.Mode = Mode;
});

