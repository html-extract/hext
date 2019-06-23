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

## Components
This package includes:
* The Hext Python module
* The htmlext command-line utility

### Using Hext with Python
The module exposes three interfaces:
* `html = hext.Html("<html>...</html>")` -> object
* `rule = hext.Rule("...")` -> object
* `rule.extract(html)` -> dictionary of {string -> string}
```
import hext
import requests
import json

res = requests.get('https://news.ycombinator.com/')
res.raise_for_status()

# hext.Html's constructor expects a single argument
# containing an UTF-8 encoded string of HTML.
html = hext.Html(res.text)

# hext.Rule's constructor expects a single argument
# containing a Hext snippet.
# Throws an exception of type ValueError on invalid syntax.
rule = hext.Rule("""
<tr>
  <td><span @text:rank /></td>
  <td><a href:href @text:title /></td>
</tr>
<?tr>
  <td>
    <span @text:score />
    <a @text:user />
    <a:last-child @text:filter(/\d+/):comment_count />
  </td>
</tr>""")

# hext.Rule.extract expects an argument of type hext.Html.
# Returns a list of dictionaries.
result = rule.extract(html)

# Print each dictionary as JSON
for map in result:
    print(json.dumps(map, ensure_ascii=False,
                          separators=(',',':')))
```

### Using Hext on the Command Line
Hext ships with a command line utility called htmlext, which applies Hext snippets to HTML documents and outputs JSON.
```
htmlext - Extract structured content from HTML.

Usage:
  htmlext [options] <hext-file> <html-file...>
      Apply extraction rules from <hext-file> to each
      <html-file> and print the captured content as JSON.

Options:
  -x [ --hext ] <file>  Add Hext from file
  -i [ --html ] <file>  Add HTML from file
  -s [ --str ] <string> Add Hext from string
  -c [ --compact ]      Print one JSON object per line
  -p [ --pretty ]       Pretty-print JSON
  -a [ --array ]        Wrap results in a JSON array
  -f [ --filter ] <key> Print values whose name matches <key>
  -l [ --lint ]         Do Hext syntax check
  -h [ --help ]         Print this help message
  -V [ --version ]      Print info and version
```
Ever wanted to watch the submissions on /r/videos in vlc? Well, take a look at this little guy right here:
```
htmlext \
  -i <(wget -O- -o/dev/null "https://old.reddit.com/r/videos/") \
  -s '<a class="title" href:x />' \
  -f x \
  | xargs vlc
```

## License
[Hext](https://hext.thomastrapp.com/) is released under the terms of the Apache License v2.0. The source code is hosted on [Github](https://github.com/html-extract/hext.git).
This binary package includes content authored by third parties:
* [gumbo-parser](https://github.com/google/gumbo-parser). Copyright 2010 Google Inc. See gumbo.license.
* [rapidjson](http://rapidjson.org/). Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip. See rapidjson.license.

