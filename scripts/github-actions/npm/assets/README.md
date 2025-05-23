# Hext — Extract Data from HTML

![Hext Logo](https://raw.githubusercontent.com/html-extract/html-extract.github.io/master/hext-logo-x100.png)

Hext is a domain-specific language for extracting structured data from HTML. It can be thought of as a counterpart to templates, which are typically used by web developers to structure content on the web.


## A Quick Example
The following Hext template collects all hyperlinks and extracts the href and the clickable text.
```
<a href:link @text:title />
```
Hext does so by recursively trying to match every HTML element. In the case above, an element is required to have the tag a and an attribute called href. If the element matches, its attribute href and its textual representation are stored as link and title, respectively.

If the above Hext template is applied to this piece of HTML:
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
* Node v20, v22, v23, v24
* Linux x86_64, arm64
* macOS x86_64, arm64

If you would like to use Hext on a system that is not supported, please raise an issue on github: [https://github.com/html-extract/hext/issues/](https://github.com/html-extract/hext/issues/).


## Using Hext with Node

The module exposes three interfaces:
* `var html = new hext.Html("<html>...</html>")` -> internal object
* `var rule = new hext.Rule("...")` -> internal object
* `var result = rule.extract(html)` -> Array of plain JS-objects
* `rule.extract` has a second optional parameter `max_searches` which is of type unsigned int. The search for matching elements is aborted after this limit is reached. The default is 0, which never aborts.

```
const hext = require('hext');
const request = require('request');


// hext.Rule's constructor expects a single argument
// containing a Hext template.
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
The Python distribution also contains the [htmlext command-line utility](https://hext.thomastrapp.com/download#htmlext).

In addition to Python and Node, there are language bindings for [JavaScript](https://hext.thomastrapp.com/download#hext-for-javascript), [PHP](https://hext.thomastrapp.com/download#hext-for-php) and [Ruby](https://hext.thomastrapp.com/download#hext-for-ruby).


## License

[Hext](https://hext.thomastrapp.com/) is released under the terms of the Apache License v2.0. The source code is hosted on [Github](https://github.com/html-extract/hext.git).
This binary package includes content authored by third parties:
* [gumbo-parser](https://github.com/google/gumbo-parser). Copyright 2010 Google Inc. See gumbo.license.

