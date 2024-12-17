#ifndef ADS_H
#define ADS_H

#include <string>
#include <vector>

struct Advertisment {
  int uid;
  std::string category;
  std::string title;
  std::string description;
  float price;
  int status_id;
  int amount;
  std::vector<unsigned char> image;
};

#endif
