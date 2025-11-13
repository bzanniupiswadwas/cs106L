#include "spellcheck.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  Corpus tokens;
  auto spaces = find_all(source.begin(), source.end(), isspace);
  if (spaces.size() > 1) {
    std::transform(spaces.begin(), 
                    spaces.end() - 1, 
                    spaces.begin() + 1, 
                    std::inserter(tokens, tokens.end()),
                    [&source] (auto it1, auto it2) {
                      return Token(source, it1, it2);
                    });
    std::erase_if(tokens,[] (const auto& tokens) {
      return tokens.content.empty();
    });
  }
  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv = std::ranges::views;

  auto views = source 
                    | rv::filter([&dictionary] (auto token) {
                        return !dictionary.contains(token.content);
                      })
                    | rv::transform([&dictionary] (auto token) {
                        auto suggestions = dictionary | rv::filter([&token] (auto word) {
                          return levenshtein(token.content, word) == 1;
                        });
                      return Misspelling{token,std::set<std::string>(suggestions.begin(), suggestions.end())};
                      })
                    | rv::filter([] (auto misspel) {
                        return !(misspel.suggestions.empty());
                      });
  return std::set<Misspelling>(views.begin(), views.end());
};

/* Helper methods */

#include "utils.cpp"