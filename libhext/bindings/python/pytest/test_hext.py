# coding: utf-8

# Copyright 2018 Thomas Trapp
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# Hext python module tests.
# To run more exhaustive tests use htmlext.py in conjunction with blackbox.sh:
# HTMLEXT="python <path-to-hext>/libhext/bindings/python/htmlext.py" \
#   <path-to-hext>/test/blackbox.sh <path-to-hext>/test/case/*hext


import hext
import pytest

def test_html_accepts_unicode_str():
    html = hext.Html(u"<html><body>💩</body></html>");

def test_rule_accepts_unicode_str():
    rule = hext.Rule(u"<body @text='💩' />")

def test_rule_throws_on_syntax_error():
    with pytest.raises(ValueError):
        rule = hext.Rule("deliberate syntax error")

def test_rule_extracts_list_of_dict():
    html = hext.Html("<html><body>💩</body></html>");
    rule = hext.Rule("<body @text:body />")
    result = rule.extract(html)
    assert type(result) is list
    assert len(result) is 1
    assert type(result[0]) is dict
    assert "body" in result[0]
    assert type(result[0]["body"]) is str
    assert result[0]["body"] == "💩"

def test_rule_extracts_empty_list():
    html = hext.Html("<html><body>💩</body></html>");
    rule = hext.Rule("<a @text:nope />")
    result = rule.extract(html)
    assert type(result) is list
    assert len(result) is 0

