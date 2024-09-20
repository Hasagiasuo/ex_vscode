#ifndef DBMAN_H
#define DBMAN_H

#include <pqxx/pqxx>
#include <string>
#include <iostream>
#include <vector>

class DBControll {
  pqxx::connection* con;
  pqxx::work* curs;
public:
  DBControll() = delete;
  DBControll(std::string connecting_format);
  ~DBControll();
  std::vector<std::vector<std::string>> get_all_offers();
  std::vector<std::vector<std::string>> get_offers(std::string owner);
  void push_offer(std::string owner, std::string path_img, std::string offer_title, std::string offer_desc, std::string offer_note);
  void set_value_users(std::string target, std::string n_value, std::string clue_name, std::string clue);
  void push_user(std::string email, std::string password, std::string name);
  void create_user_table();
  std::vector<std::string> get_user_by_login(std::string email, std::string password);
  void show_table(std::string table_name);
};

#endif