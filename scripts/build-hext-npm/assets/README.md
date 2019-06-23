# Hext — Extract Data from HTML

![Hext Logo](https://raw.githubusercontent.com/thomastrapp/hext-website/master/hext-logo-x100.png)

Hext is a domain-specific language for extracting structured data from HTML. It can be thought of as a counterpart to templates, which are typically used by web developers to structure content on the web.


## A Quick Example
The following Hext snippet collects all hyperlinks and extracts the href and the clickable text.
```
<a href:link @text:title />
```
Hext does so by recursively trying to match every HTML element. In the case above, an element is required to have the tag a and an attribute called href. If the element matches, its attribute href and its textual representation are stored as link and title, respectively.

If the above Hext snippet is applied to this piece of HTML:
```
<body>
  <a href="one.html">  Page 1</a>
  <a href="two.html">  Page 2</a>
  <a href="three.html">Page 3</a>
</body>
```
Hext will produce the following values:
```
{ "link": "one.html",   "title": "Page 1" },
{ "link": "two.html",   "title": "Page 2" },
{ "link": "three.html", "title": "Page 3" }
```
You can use this example in [Hext’s live code editor](https://hext.thomastrapp.com/#anchor-tryit-hext).
Visit [Hext’s documentation](https://hext.thomastrapp.com/documentation) and its section “[How Hext Matches Elements](https://hext.thomastrapp.com/documentation#matching-elements)” for a more thorough explanation.

## Compatibility

This binary package is compatible with:
* Node v8, v10, v11, v12
* Linux (GLIBC ≥2.14, basically any distribution built after the year 2012)
* Mac OS X (10.11 El Capitan or later)
* x86_64 only

If you would like to use Hext on a system that is not supported, please raise an issue on github: [https://github.com/html-extract/hext/issues/](https://github.com/html-extract/hext/issues/).


## Using Hext with Node

The module exposes three interfaces:
* `var html = new hext.Html("<html>...</html>")` -> internal object
* `var rule = new hext.Rule("...")` -> internal object
* `var result = rule.extract(html)` -> Array of plain JS-objects

```
const hext = require('hext');
const request = require('request');


// hext.Rule's constructor expects a single argument
// containing a Hext snippet.
// Throws an Error on invalid syntax, with
// Error.message containing the error description.
const rule = new hext.Rule(`
<tr>
  <td><span @text:rank /></td>
  <td><a href:href @text:title /></td>
</tr>
<?tr>
  <td>
    <span @text:score />
    <a @text:user />
    <a:last-child @text:filter(/\\d+/):comment_count />
  </td>
</tr>`)


request('https://news.ycombinator.com/',
        function(error, response, body) {

  // hext.Html's constructor expects a single argument
  // containing a UTF-8 encoded string of HTML.
  const html = new hext.Html(body);

  // hext.Rule.extract expects an argument of type
  // hext.Html. Returns an Array containing Objects
  // which contain key-value pairs of type String.
  const results = rule.extract(html)

  // Print each rule match as JSON
  results.forEach(result => console.log(JSON.stringify(result)));
});

```

## More

Hext is also available for Python:
```
pip install hext
```
The Python distribution also contains the [htmlext command-line utility](https://hext.thomastrapp.com/download#using-htmlext).

In addition to Python and Node, there are language bindings for [PHP](https://hext.thomastrapp.com/download#building-php-hext) and [Ruby](https://hext.thomastrapp.com/download#building-ruby-hext).


## License

[Hext](https://hext.thomastrapp.com/) is released under the terms of the Apache License v2.0. The source code is hosted on [Github](https://github.com/html-extract/hext.git).
This binary package includes content authored by third parties:
* [gumbo-parser](https://github.com/google/gumbo-parser). Copyright 2010 Google Inc. See gumbo.license.

