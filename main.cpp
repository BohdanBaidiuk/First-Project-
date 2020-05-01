#include "ContentUrl.hpp";
#include "optionKonsole.hpp"
#include <iostream>

int main(int argc, const char *argv[]) {
  std::string url = "https://www.google.com";
  size_t search_depth_url = 2;
  std::cout << "Please input --help or -h " << std::endl;
  search_urls(search_depth_url, url);
  // EApplication(argc, argv,url, search_depth_url);

  return 0;
}
