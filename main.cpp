#define CURL_STATICLIB
#include "curl/curl.h"
#include "findUrl.hpp"
#include "Regex.hpp"
#include"optionKonsole.hpp"
#include <string>
#include <iostream>
#include <vector>


int main(int argc, char **argv) {
  std::string url = "google.com";
  size_t search_depth_url = 4;
  if (Check_Url(url)) {
    find_url(url);
  } else {
    std::cout << "Not correct input url" << std::endl;
  }
  return 0;
}
