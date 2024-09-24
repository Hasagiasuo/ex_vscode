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

std::string DBControll::get_id_by_description(std::string description) {
  try {
    this->curs = new pqxx::work(*this->con);
    pqxx::result uid = this->curs->exec("SELECT user_id FROM offers WHERE description = '" + description + "';");
    this->curs->commit();
    return std::string(uid.at(0).at(0).c_str());
  } catch(const std::exception& ex) {
    std::cout << ex.what() << std::endl;
    this->curs->commit();
    return std::string();
  }
}

std::string DBControll::get_id_by_name(std::string name) {
  try {
    this->curs = new pqxx::work(*this->con);
    pqxx::result uid = this->curs->exec("SELECT id FROM users WHERE name = '" + name + "';");
    this->curs->commit();
    return std::string(uid.at(0).at(0).c_str());
  } catch(const std::exception& er) {
    std::cout << er.what() << std::endl;
    this->curs->commit();
    return std::string();
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

void DBControll::delete_offer_by_description(std::string description, std::string owner_id) {
  try {
    this->curs = new pqxx::work(*this->con);
    this->curs->exec_params("DELETE FROM offers WHERE description = $1 AND user_id = $2;", description, owner_id);
    this->curs->commit();
  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
    this->curs->commit();
  }
}

std::vector<std::string> DBControll::get_user_by_login(std::string email, std::string password) {
  try {
    this->curs = new pqxx::work(*this->con);
    pqxx::result search_value = this->curs->exec("SELECT * FROM users WHERE email='" + email +"';");
    this->curs->commit();
    // 0 0 - get? | 0 1 - email | 0 2 - password | 0 3 - name
    std::vector<std::string> user_data;
    user_data.push_back(std::string(search_value.at(0).at(1).c_str())); // email
    user_data.push_back(std::string(search_value.at(0).at(2).c_str())); // password
    user_data.push_back(std::string(search_value.at(0).at(3).c_str())); // name
    if(std::string(search_value.at(0).at(2).c_str()) == password) return user_data;
  } catch (const std::exception& ex) {
    std::cout << "ERROR: " << ex.what() << std::endl;
    this->curs->commit();
  }
  return std::vector<std::string>();
}

void DBControll::set_value_users(std::string target, std::string n_value, std::string clue_name, std::string clue) {
  try {
    this->curs = new pqxx::work(*this->con);
    this->curs->exec("UPDATE users SET " + target + " = '" + n_value + "' WHERE " + clue_name + " = '" + clue + "';");
    this->curs->commit();
  } catch (const std::exception& er) {
    std::cout << "ERROR: " << er.what() << std::endl;
    this->curs->commit();
  }
}

void DBControll::push_offer(std::string owner, std::string path_img, std::string offer_title, std::string offer_desc, std::string offer_note) {
  try {
    this->curs = new pqxx::work(*this->con);
    pqxx::result user_id = this->curs->exec("SELECT id FROM users WHERE name = '" + owner +"';");
    this->curs->exec("INSERT INTO offers (user_id, img_path, title, description, note) VALUES (" + std::string(user_id.at(0).at(0).c_str()) + ", '" + path_img + "', '" + offer_title + "', '" + offer_desc + "', '" + offer_note + "');");
    this->curs->commit();
  } catch (const std::exception& er) {
    std::cout << "ERROR: " << er.what() << std::endl;
    this->curs->commit();
  }
}

std::vector<std::vector<std::string>> DBControll::get_offers(std::string owner) {
  try {
    std::vector<std::vector<std::string>> res;
    this->curs = new pqxx::work(*this->con);
    pqxx::result user_id = this->curs->exec("SELECT id FROM users WHERE name = '" + owner +"';");
    pqxx::result offers = this->curs->exec("SELECT user_id, img_path, title, description, note FROM offers WHERE user_id = " + std::string(user_id.at(0).at(0).c_str()) + ";");
    for(auto col : offers) {
      std::vector<std::string> tmp;
      for(auto row : col) {
        tmp.push_back(std::string(row.c_str()));
      }
      res.push_back(tmp);
    }
    this->curs->commit();
    return res;
  } catch (const std::exception& er) {
    std::cout << "ERROR: " << er.what() << std::endl;
    this->curs->commit();
    return std::vector<std::vector<std::string>>();
  }
}

std::vector<std::vector<std::string>> DBControll::get_all_offers() {
  try {
    std::vector<std::vector<std::string>> res;
    this->curs = new pqxx::work(*this->con);
    pqxx::result offers = this->curs->exec("SELECT user_id, img_path, title, description, note FROM offers;");
    for(auto col : offers) {
      std::vector<std::string> tmp;
      for(auto row : col) {
        tmp.push_back(std::string(row.c_str()));
      }
      res.push_back(tmp);
    }
    this->curs->commit();
    return res;
  } catch (const std::exception& er) {
    std::cout << "ERROR: " << er.what() << std::endl;
    this->curs->commit();
    return std::vector<std::vector<std::string>>();
  }
}