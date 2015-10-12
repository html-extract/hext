// Copyright 2015 Thomas Trapp
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

#include "htmlext/PrintDot.h"


namespace htmlext {


void PrintHtmlDot(const hext::Html& html, std::ostream& out)
{
  out << "digraph html_tree {\n"
      << "    node [fontname=\"Arial\"];\n";
  PrintHtmlDotNodes(html.root(), 0, out);
  out << "}\n";
}


void PrintHtmlDotNodes(const GumboNode * node, int parent_id, std::ostream& out)
{
  static int node_index = 0;
  int this_node = ++node_index;

  assert(node);
  if( !node )
    return;

  std::string label;
  switch( node->type )
  {
    case GUMBO_NODE_ELEMENT:
    {
      label.append(gumbo_normalized_tagname(node->v.element.tag));
      break;
    }
    case GUMBO_NODE_DOCUMENT:   { label.append("DOC");     break; }
    case GUMBO_NODE_TEMPLATE:   { label.append("TPL");     break; }
    case GUMBO_NODE_WHITESPACE: { label.append("WS");      break; }
    case GUMBO_NODE_COMMENT:    { label.append("COMMENT"); break; }
    case GUMBO_NODE_CDATA:      { label.append("CDATA");   break; }
    case GUMBO_NODE_TEXT:       { label.append("TXT");     break; }
  }

  out << "    node_" << this_node << " [label=\"" << label << "\"];\n";
  if( parent_id )
    out << "    node_" << parent_id << " -> node_" << this_node << ";\n";

  if( node->type == GUMBO_NODE_ELEMENT )
  {
    const GumboVector * node_children = &node->v.element.children;
    for(unsigned int i = 0; i < node_children->length; ++i)
    {
      auto child_node = static_cast<const GumboNode *>(node_children->data[i]);
      PrintHtmlDotNodes(child_node, this_node, out);
    }
  }
}


} // namespace htmlext

