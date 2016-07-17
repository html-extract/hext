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

require 'hext'
require 'json'


scriptname = File.basename($0)
if ARGV.length == 0
  puts "Usage: %s <file-hext> <file-html>" % scriptname
  puts "  Applies Hext from <file-hext> to the HTML document in <file-html>"
  puts "  and prints the result as JSON, one object per line."
  exit
elsif ARGV.length < 2
  abort "%s: Error: missing arguments" % scriptname
end

strhext = File.read(ARGV[0])
strhtml = File.read(ARGV[1])

rule = nil
begin
  rule = Hext::Rule.new(strhext)
rescue ArgumentError => e
  abort "%s: In '%s': %s" % [scriptname, ARGV[0], e.message]
end

html = Hext::Html.new(strhtml)
result = rule.extract(html)

result.each do |map|
  puts map.to_json
end

