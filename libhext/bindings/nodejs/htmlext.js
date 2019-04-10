#!/usr/bin/env node

// Copyright 2016 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


// Tries to load hext the usual way, and, if failing, tries to load the module
// in the current directory (assuming this script wasn't moved from its location
// within the repository).
function loadHext()
{
  try
  {
    return require('hext');
  }
  catch( e )
  {
    return require('./index.js');
  }
}

var hext = loadHext();
var path = require('path');
var util = require('util');
var file = require('fs');

var args = process.argv.slice(2);
var scriptname = path.basename(__filename);
if( args.length < 1 )
{
  console.log(util.format("Usage: %s <file-hext> <file-html>", scriptname));
  console.log("  Applies Hext from <file-hext> to the HTML document in" +
              " <file-html>");
  console.log("  and prints the result as JSON, one object per line.");
  process.exit();
}
if( args.length < 2 )
{
  console.error(util.format("%s: Error: missing arguments", scriptname));
  process.exit(1);
}

var strhext = file.readFileSync(args[0], "utf-8");
var strhtml = file.readFileSync(args[1], "utf-8");

var rule;
try
{
  rule = new hext.Rule(strhext);
}
catch(e)
{
  console.error(util.format("%s: In %s: %s", scriptname, args[0], e.message));
  process.exit(1);
}

var html = new hext.Html(strhtml);
var result = rule.extract(html);

for(var i in result)
  console.log(JSON.stringify(result[i]));

