<?php

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

require "hext.php";


$scriptname = basename($argv[0]);
if( $argc < 2 )
{
  echo "Usage: $scriptname <file-hext> <file-html>\n";
  echo "  Applies Hext from <file-hext> to the HTML document in <file-html>\n";
  echo "  and prints the result as JSON, one object per line.\n";
  exit();
}
if( $argc < 3 )
{
  fwrite(STDERR, "$scriptname: Error: missing arguments\n");
  exit(1);
}

foreach(array($argv[1], $argv[2]) as $f)
  if( !is_readable($f) || !is_file($f) )
  {
    fwrite(STDERR, "$scriptname: Error: cannot access '$f'\n");
    exit(1);
  }

$strhext = file_get_contents($argv[1]);
$strhtml = file_get_contents($argv[2]);

$rule;
try
{
  $rule = new HextRule($strhext);
}
catch(Exception $e)
{
  fwrite(STDERR, "$scriptname: In '{$argv[1]}': {$e->getMessage()}\n");
  exit(1);
}

$html = new HextHtml($strhtml);
$result = $rule->extract($html);

foreach($result as $map)
  echo json_encode($map, JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE)."\n";

