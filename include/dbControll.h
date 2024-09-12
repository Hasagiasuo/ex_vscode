#ifndef DBMAN_H
#define DBMAN_H

#include <pqxx/pqxx>
#include <string>
#include <iostream>

class DBControll {
  pqxx::connection* con;
  pqxx::work* curs;
public:
  DBControll() = delete;
  DBControll(std::string connecting_format);
  ~DBControll();
  void push_user(std::string email, std::string password, std::string name);
  void create_user_table();
  void show_table(std::string table_name);
};

#endif