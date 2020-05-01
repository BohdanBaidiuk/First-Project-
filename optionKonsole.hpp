#pragma once
#include "ContentUrl.hpp"
#include "Regex.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>
namespace po = boost::program_options;

void EApplication(int argc, const char **argv, std::string &url,
                  size_t &depth_url) {
  po::options_description desc("short description");
  desc.add_options()("help,h", "help me")("depth,d", po::value<size_t>(),
                                          " search depth")(
      "url,u", po::value<std::string>(), " url for find");
  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
  } catch (po::error &e) {
    std::cout << e.what() << std::endl;
    std::cout << desc << std::endl;
    return;
  }
  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return;
  }
  if (vm.count("depth")) {
    std::cout << "You entered = " << vm["depth"].as<size_t>() << std::endl;
    // depth_url = vm["depth"].as<size_t>();
  }
  if (vm.count("url")) {
    std::cout << "You entered = " << vm["url"].as<std::string>() << std::endl;
    /*url = vm["url"].as<std::string>();
    if (Check_Url(url)) {
            search_urls(depth_url, url);
    }
    else {
            std::cout << "Erorr name url" << std::endl;
    }*/
  }
}
