define(function(require, exports, module) {
  "use strict";

  var oop = require("../lib/oop");
  var lang = require("../lib/lang");
  var TextHighlightRules = require("./text_highlight_rules").TextHighlightRules;

  var HextHighlightRules = function() {
    var tagRegex = '\\??[_\\*a-z][-_a-z0-9]*';
    var attribRegex = '[@a-z0-9_\\-]+';
    var singleQuoteRegex = "['](?:(?:\\\\.)|(?:[^'\\\\]))*?[']";
    var doubleQuoteRegex = '["](?:(?:\\\\.)|(?:[^"\\\\]))*?["]';
    var regexRegex = '[/](?:(?:\\\\.)|(?:[^/\\\\]))*?[/][ic]*';
    var matchOperatorRegex = /(?:==)|(?:\$=)|(?:\*=)|(?:=)|(?:\^=)/;

    var stringPipes = lang.arrayToMap(
        ("trim|tolower|toupper|collapsews|prepend" +
         "|append|filter|replace").split("|"));
    var stringPipeToken = function(value) {
      if( stringPipes.hasOwnProperty(value.toLowerCase()) )
        return "constant.numeric";
      else
        return "storage";
    };

    var nodeTraits = lang.arrayToMap(
        (":empty|:child-count|:attribute-count|:nth-child|" +
         ":nth-last-child|:nth-of-type|:first-child|:first-of-type|" +
         ":last-child|:last-of-type|:nth-last-of-type|:only-child|" +
         ":only-of-type|:not").split("|"));
    var nodeTraitToken = function(value) {
      if( nodeTraits.hasOwnProperty(value.toLowerCase()) )
        return "entity.name.tag";
      else
        return "text";
    };


    this.$rules = {
      start: [{
        token: "keyword",
        regex: "</" + tagRegex + ">",
      }, {
        token: "keyword",
        regex: "<" + tagRegex,
        next: "node_traits",
      }, {
        token: "comment",
        regex: /#.*$/
      }, {
        defaultToken: "text"
      }],


      "tag_whitespace": [{
        token: "whitespace",
        regex: "\\s+",
      }],


      "node_traits": [{
        token: nodeTraitToken,
        regex: ":[a-z\-]+",
        next: "node_traits",
      }, {
        token: "whitespace",
        regex: " ",
        next: "attributes",
      }, {
        token: "keyword",
        regex: "/?>",
        next: "start",
      }],


      "attributes": [{
        token: "text",
        regex: attribRegex,
      }, {
        token: "entity.name.tag",
        regex: ":",
        next: "extraction",
      }, {
        token: "entity.name.tag",
        regex: "=~",
        next: "regex_match",
      }, {
        token: "entity.name.tag",
        regex: matchOperatorRegex,
        next: "attribute_value",
      }, {
        token: "constant.numeric",
        regex: "\\(",
        next: "arguments",
      }, {
        include: "tag_whitespace",
      }, {
        token: "keyword",
        regex: "/?>",
        next: "start",
      }],


      "regex_match": [{
        token: "string",
        regex: regexRegex,
        next: "attributes",
      }],


      "extraction": [{
        token: stringPipeToken,
        regex: "[a-z_]+",
        next: "attributes",
      }, {
        token: "storage",
        regex: doubleQuoteRegex,
        next: "attributes",
      }, {
        token: "storage",
        regex: singleQuoteRegex,
        next: "attributes",
      }],


      "arguments": [{
        token: "string",
        regex: doubleQuoteRegex,
      }, {
        token: "string",
        regex: singleQuoteRegex,
      }, {
        token: "string",
        regex: regexRegex,
      }, {
        token: "text",
        regex: ',',
      }, {
        include: "tag_whitespace",
      }, {
        token: "constant.numeric",
        regex: "\\)",
        next: "attributes",
      }],


      "attribute_value": [{
        token: "string",
        regex: doubleQuoteRegex,
        next: "attributes",
      }, {
        token: "string",
        regex: singleQuoteRegex,
        next: "attributes",
      }],
    };
  };

  oop.inherits(HextHighlightRules, TextHighlightRules);
  exports.HextHighlightRules = HextHighlightRules;
});

