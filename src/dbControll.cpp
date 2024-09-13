#include "dbControll.h"

DBControll::~DBControll() {
  delete this->con;
  delete this->curs;
}

DBControll::DBControll(std::string connecting_format) {
  this->con = new pqxx::connection(connecting_format);
  if(!this->con->is_open()) std::cout << "ERROR: Database not connection!" << std::endl;
  else std::cout << "INFO: Database connection!" << std::endl;
}

void DBControll::show_table(std::string table_name) {
  try {
    this->curs = new pqxx::work(*this->con);
    pqxx::result all_db = this->curs->exec("SELECT * FROM " + table_name);
    this->curs->commit();
    std::cout << "INFO TABLE: " << std::endl;
    for(int i = 0; i < all_db.columns(); ++i) 
      std::cout << "| " << all_db.column_name(i) << " |\t\t";
    std::cout << std::endl;
    for(auto const& row : all_db) {
      for(auto const& val : row) {
        std::cout << "| " << val.c_str() << " |\t\t";
      }
      std::cout << std::endl;
    }
  } catch (const std::exception& ex) {
    std::cout << "ERROR: " << ex.what() << std::endl;
    this->curs->commit();
  }
}

void DBControll::create_user_table() {
  try {
    this->curs = new pqxx::work(*this->con);
    this->curs->exec(
      "CREATE TABLE IF NOT EXISTS users ("
      "id SERIAL PRIMARY KEY, "
      "email VARCHAR(30), "
      "password VARCHAR(30), "
      "name VARCHAR(30)"
      ");"
    );
    this->curs->commit();
    std::cout << "INFO: Table created!" << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "ERROR: " << ex.what() << std::endl;
    this->curs->commit();
  }
}

void DBControll::push_user(std::string email, std::string password, std::string name) {
  try {
    this->curs = new pqxx::work(*this->con);
    this->curs->exec(
      "INSERT INTO users (email, password, name) VALUES ('" + email + "', '" + password + "', '" + name + "');"
    );
    this->curs->commit();
    std::cout << "INFO: User (" << email << "|" << password << "|" << name << ") append!" << std::endl;
  } catch (const std::exception& ex) {
    std::cout << "ERROR: " << ex.what() << std::endl;
    this->curs->commit();
  }
}

std::vector<std::string> DBControll::get_user_by_login(std::string email, std::string password) {
  try {
    this->curs = new pqxx::work(*this->con);
    pqxx::result search_value = this->curs->exec("SELECT * FROM users WHERE email='" + email +"';");
    // 0 0 - get? | 0 1 - email | 0 2 - password | 0 3 - name
    std::vector<std::string> user_data;
    user_data.push_back(std::string(search_value.at(0).at(1).c_str())); // email
    user_data.push_back(std::string(search_value.at(0).at(2).c_str())); // password
    user_data.push_back(std::string(search_value.at(0).at(3).c_str())); // name
    if(std::string(search_value.at(0).at(2).c_str()) == password) return user_data;
    this->curs->commit();
  } catch (const std::exception& ex) {
    std::cout << "ERROR: " << ex.what() << std::endl;
    this->curs->commit();
  }
  return std::vector<std::string>();
}