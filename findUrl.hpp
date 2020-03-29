#pragma once
#include "curl/curl.h"
#include <iostream>
#include <string>

void find_url(std::string url) {
  CURL *curl;
  CURLcode res;
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  static char ErrorBuffer[CURL_ERROR_SIZE];
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, ErrorBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK) {
      std::cout << "Error!" << ErrorBuffer << std::endl;
    }
  }
}
