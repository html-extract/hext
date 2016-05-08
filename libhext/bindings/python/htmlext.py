# Copyright 2016 Thomas Trapp
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


import hext
import json
import sys
import os


# Returns value at key if key is unique.
# Else returns array containing all values for key.
def pack_value_for_key(map, key):
    size = map.count(key)
    if( size < 2 ):
        return map[k]
    else:
        begin = map.find(k)
        end = begin + size
        arr = []
        while( begin != end ):
            v = begin.value()
            arr.append(v[1])
            begin.incr()
        return arr


scriptname = os.path.basename(sys.argv[0])
if len(sys.argv) < 2:
    print "Usage: {} <file-hext> <file-html>".format(scriptname)
    print "  Applies Hext from <file-hext> to the HTML document in <file-html>"
    print "  and prints the result as JSON, one object per line."
    sys.exit()
if len(sys.argv) < 3:
    sys.stderr.write("{}: Error: missing arguments\n".format(scriptname))
    sys.exit(1)


strhext = open(sys.argv[1]).read()
strhtml = open(sys.argv[2]).read()

rule = hext.Rule(strhext)
document = hext.Html(strhtml)
result = rule.extract(document)

for map in result:
    obj = dict()
    for k in map:
        obj[k] = pack_value_for_key(map, k)
    print json.dumps(obj, ensure_ascii=False,   # ignore encoding
                          separators=(',',':'), # compact output
                          sort_keys=True)       # predictable output

