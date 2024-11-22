#ifndef DBMAN_H
#define DBMAN_H

#include <pqxx/pqxx>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

class DBControll {
  pqxx::connection* con;
  pqxx::work* curs;
  std::string decrypt(std::string target);
  std::string encrypt(std::string target);
public:
  DBControll() = delete;
  DBControll(std::string connecting_format); ~DBControll();
  std::vector<int> get_favorite_array_by_name(std::string name);
  void add_favorite(std::string u_name, std::string offer_id);
  std::vector<std::vector<std::string>> get_all_offers(std::string uid);
  std::vector<std::vector<std::string>> get_offers(std::string owner);
  std::vector<std::vector<std::string>> get_favorite(std::string owner);
  void push_offer(std::string owner, std::string path_img, std::string offer_title, std::string offer_desc, std::string offer_note);
  void set_value_users(std::string target, std::string n_value, std::string clue_name, std::string clue);
  void push_user(std::string email, std::string password, std::string name);
  void delete_offer_by_description(std::string description, std::string owner_id);
  void create_user_table();
  std::vector<std::string> get_user_by_login(std::string email, std::string password);
  void show_table(std::string table_name);
  std::string get_id_by_description(std::string description);
  std::string get_id_by_name(std::string name);
  std::vector<std::string> getcard_data_by_title(std::string title);
  void update_card_by_title(std::string title, std::string n_path_img, std::string n_title, std::string n_desc, std::string n_note);
  bool exists_card(std::string title);
};

#endif
