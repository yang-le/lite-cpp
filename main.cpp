#include <iostream>

#include "antlr4-runtime.h"
#include "grammar/LiteLexer.h"
#include "grammar/LiteParser.h"

using namespace antlr4;
using namespace litecpp;

int main(int argc, const char **argv)
{
  ANTLRInputStream input(u8R"litecode(
  "Demo"{}
  main : (->) {
      print("Hello, world!")
      greetings = get_greetings("love lite!")
      index : value @ greetings {
          index ? 0 {
              print(value)
          } 1 {
              print(value + ", 世界!")
          } _ {
              print(value + ", world!")
          }
      }
  }

  get_greetings : (first str -> result []str) {
      <- first + {"你好", "Hola", "Bonjour",
                  "Ciao", "こんにちは", "안녕하세요",
                  "Cześć", "Olá", "Здравствуйте",
                  "Chào bạn"}
  }
  )litecode");
  LiteLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();
  for (auto token : tokens.getTokens()) {
    std::cout << token->toString() << std::endl;
  }

  LiteParser parser(&tokens);
  tree::ParseTree* tree = parser.program();

  std::cout << tree->toStringTree(&parser) << std::endl;

  return 0;
}
