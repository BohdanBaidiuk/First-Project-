#pragma once
#include <regex>

bool Check_Url(std::string arg_url) {
  std::regex Ceck_xRegEx("([\\w-]+)(\.)([a-z]{2,5})");
  if (std::regex_match(arg_url, Ceck_xRegEx)) {
    return true;
  }
  return false;
}

/*bool Search_Url(std::string arg_url) {
        std::regex Searc_Reg("([\\w-]+)(\.)([a-z]{2,5})");
        if (std::regex_search(arg_url, Searc_Reg)) {

        }

        return false;
}*/
