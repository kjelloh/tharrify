#include <iostream>
#include <utility>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <memory>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>

// Split C++ source code on only scopes and lists

using In = std::string_view;
struct Node {
  using Childs = std::pair<std::shared_ptr<Node>,std::shared_ptr<Node>>;
  using Value = std::string;
  std::variant<Value,Childs> content;
  Node append(Node const& node) {
    std::cout << "\nDESIGN INSUFFICIENCY - Node::append node not yet implemented";
    return *this;
  }
  Node append(std::shared_ptr<Node> p) {
    std::cout << "\nDESIGN INSUFFICIENCY - Node::append p not yet implemented";
    return *this;
  }
};
using AST = Node;
using ParseResult = std::optional<std::pair<AST,In>>;

class Parser {
public:
  virtual ParseResult operator()(In const& in) const = 0;
};

class ParseList : public Parser {
public:
  virtual ParseResult operator()(In const& in) const;
private:
};

class ParseScope : public Parser {
public:
  virtual ParseResult operator()(In const& in) const;
private:
  std::map<char,char> const close_char{
    {'(',')'}
    ,{'{','}'}
    ,{'[',']'}
    ,{'<','>'}
  };
};

class ParseText : public Parser {
public:
  virtual ParseResult operator()(In const& in) const;
private:
};

ParseResult ParseList::operator()(In const& in) const {
  ParseResult result;
  AST ast{};
  // TODO: Parse text separated by one of the list separators unless a new scope is found
  return result;
}

ParseResult ParseScope::operator()(In const& in) const {
  ParseResult result;
  AST ast{};
  if (close_char.contains(in[0])) {
    std::string_view inx{in.begin()+1,in.end()};
    auto parse_text_result = ParseText{}(inx); // Recurse
    if (parse_text_result) {
      auto [text_ast,out] = parse_text_result.value();
      if (close_char.at(in[0]) == out[0]) {
        // TODO: Update our ast with created ast
        ast.append(text_ast);
        result = std::make_pair(ast,parse_text_result->second);
      }
    }
  }
  return result;
}

ParseResult ParseText::operator()(In const& in) const {
  ParseResult result;
  AST ast{};
  ParseScope parse_scope{};
  ParseList parse_list{};
  std::string text{};
  for (int i=0;i<in.size();i++) {
    auto inx = in.substr(i);
    auto parsed_scope_result = parse_scope(inx);
    if (!parsed_scope_result) {
      auto parsed_list_result = parse_list(inx);
      if (!parsed_list_result) {
        text += inx[0];
      }
      else {
        // TODO: Append text parsed so far to the beginning of the list
        if (text.size()>0) {
          ast.append(std::make_shared<Node>(text));
          text.clear();
        }
        ast.append(parsed_list_result->first);
      }
    }
    else {
      if (text.size()>0) {
        ast.append(std::make_shared<Node>(text));
        text.clear();
      }
      ast.append(parsed_scope_result->first);
    }
  }
  return result;
}

int main(int argc, char *argv[])
{
  std::cout << "\nNOT YET IMPLEMENTED - Initial approach is LL Recursive decent parsing, But...";
  std::cout << "\nWe will probably need to refactor code into doing LR parsing?";
  std::cout << "\nAt least list parsing becomes awkward with Recursive decent as list can't be detected until first separator is found...";
  return 0;
  if (argc>1) {
    std::filesystem::path path(argv[1]);
    std::ifstream inf{path};
    std::string file_content{std::istream_iterator<char>(inf),std::istream_iterator<char>()};
    ParseText parse_text{};
    std::string_view in{file_content};
    auto parse_result = parse_text(in);
  }
  else {
    std::cout << "\nPlease provide a file to parse";
    std::cout << "\n";
  }
  return 0;
}
