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
  void push_user(std::string email, std::string password, std::string name);
  void create_user_table();
  std::vector<std::string> get_user_by_login(std::string email, std::string password);
  void show_table(std::string table_name);
};

#endif