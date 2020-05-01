#pragma once
#include "ContentUrl.hpp"
#include "findUrl.hpp"
#include <algorithm>
#include <iterator>
#include <map>
#include <regex>
#include <string>
#include <vector>

bool Check_Url(std::string arg_url) {
  std::regex Ceck_xRegEx("(https://[\\w-.]+)(\.)([a-z]{2,5})");
  if (std::regex_match(arg_url, Ceck_xRegEx)) {
    return true;
  }
  return false;
};

void parseContent(std::string str,
                  std::map<std::string, std::pair<bool, size_t>> &arg_https,
                  std::map<std::string, std::pair<bool, size_t>> &arg_http,
                  size_t depth, size_t &search_depth_url) {
  std::regex reg_safe("(https://[\\w-./]+)");
  std::regex reg_unsafe("(http://[\\w-./]+)");
  std::sregex_iterator currentSafe(str.begin(), str.end(), reg_safe);
  std::sregex_iterator lastSafe;
  while (currentSafe != lastSafe) {
    std::smatch match = *currentSafe;
    if (arg_https.find(match.str()) == arg_https.end()) {
      if (search_depth_url == depth) {
        arg_https[std::move(match.str())] = {true, search_depth_url};
      } else {
        arg_https[std::move(match.str())] = {false, depth + 1};
      }
    }
    currentSafe++;
  }

  std::sregex_iterator currentUnsafe(str.begin(), str.end(), reg_unsafe);
  std::sregex_iterator lastUnsafe;
  while (currentUnsafe != lastUnsafe) {
    std::smatch match = *currentUnsafe;
    if (arg_http.find(match.str()) == arg_http.end()) {
      if (search_depth_url == depth) {
        arg_http[std::move(match.str())] = {true, search_depth_url};
      } else {
        arg_http[std::move(match.str())] = {false, depth + 1};
      }
    }
    currentUnsafe++;
  }
}
