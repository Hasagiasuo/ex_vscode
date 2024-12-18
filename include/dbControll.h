#ifndef DBMAN_H
#define DBMAN_H

#include <pqxx/pqxx>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

#include "ads.h"

class DBControll {
  pqxx::connection* con;
  pqxx::work* curs;
  std::string decrypt(std::string target);
  std::string encrypt(std::string target);
public:
  DBControll() = delete;
  DBControll(std::string connecting_format); ~DBControll();
  std::vector<Advertisment*> get_all_offers(std::string uid);
  std::vector<Advertisment*> get_offers(std::string owner);
  void push_offer(std::string owner, std::string category, std::string offer_title, std::string offer_desc, float price, float amount, std::vector<char> img);
  void set_value_users(std::string target, std::string n_value, std::string clue_name, std::string clue);
  void push_user(std::string email, std::string password, std::string name, std::string phone_number, int role_id);
  void delete_offer_by_description(std::string description, std::string owner_id);
  std::vector<std::string> get_user_by_login(std::string email, std::string password);
  std::string get_id_by_description(std::string description);
  std::string get_id_by_name(std::string name);
  Advertisment get_card_data_by_title(std::string title);
  void update_card_by_title(Advertisment* n_ads);
  bool exists_card(std::string title);
};

#endif
