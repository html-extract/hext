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


void PrintResultTreeDot(const hext::ResultTree * rt, std::ostream& out)
{
  out << "digraph result_tree {\n"
      << "    node [fontname=\"Arial\"];\n";
  PrintResultTreeDotNodes(rt, 0, out);
  out << "}\n";
}


void PrintResultTreeDotNodes(const hext::ResultTree * rt,
                             int                      parent_id,
                             std::ostream&            out)
{
  static int node_index = 0;
  int this_node = ++node_index;

  assert(rt);
  if( !rt )
    return;

  std::string label;
  if( rt->values().empty() )
  {
    label = '-';
  }
  else
  {
    for(const auto& p : rt->values())
    {
      label.append(p.first);
      label.append(" ");
    }
  }

  out << "    node_" << this_node << " [label=\"" << label << "\"];\n";
  if( parent_id )
    out << "    node_" << parent_id << " -> node_" << this_node << ";\n";

  for( const auto& child : rt->children() )
  {
    PrintResultTreeDotNodes(child.get(), this_node, out);
  }
}


} // namespace htmlext

