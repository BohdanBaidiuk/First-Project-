#pragma once
#include "ThreadPool.hpp"
#include "findUrl.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <thread>
#include <utility>

std::map<std::string, std::pair<bool, size_t>> https;
std::map<std::string, std::pair<bool, size_t>> http;

void print_content(
    const std::map<std::string, std::pair<bool, size_t>> &content) {
  std::for_each(content.begin(), content.end(), [](const auto &p) {
    std::cout << p.first << " --depth-- = " << p.second.second << std::endl;
  });
};

void search_urls(size_t search_depth_url, std::string arg_url) {
  std::string content;
  ThreadPool pool{4};

  decltype(https.begin()) it;
  https[arg_url] = {false, 0};

  /*
  if (search_depth_url>0) {
          while ((it = std::find_if(https.begin(), https.end(),
                  [](auto& p) {return p.second.first == false; })) !=
  https.end()) { it->second.first = true; content = find_url(it->first);
                  parseContent(content, https, http, it->second.second,
  search_depth_url);
          }
  }*/
  print_content(https);
  print_content(http);
}
