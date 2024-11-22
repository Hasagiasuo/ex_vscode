#include "dbControll.h"

std::string DBControll::decrypt(std::string target) {
  // std::string result;
  // for(char ch : target) {
  //   result.push_back((char)((int)ch + 2));
  // }
  // return result;
  return target;
}

std::string DBControll::encrypt(std::string target) {
  // std::string result;
  // for(char ch : target) {
  //   result.push_back((char)((int)ch - 2));
  // }
  // return result;
  return target;
}

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
    description = this->encrypt(description);
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
    name = this->encrypt(name);
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
    email = this->encrypt(email);
    password = this->encrypt(password);
    name = this->encrypt(name);
    this->curs = new pqxx::work(*this->con);
    this->curs->exec(
      "INSERT INTO users (email, password, name, favorite) VALUES ('" + email + "', '" + password + "', '" + name + "', ARRAY[]::INT[]);"
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
    description = this->encrypt(description);
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
    email = this->encrypt(email);
    password = this->encrypt(password);
    this->curs = new pqxx::work(*this->con);
    pqxx::result search_value = this->curs->exec("SELECT email, password, name FROM users WHERE email='" + email +"';");
    this->curs->commit();
    std::vector<std::string> user_data;
    user_data.push_back(this->decrypt(std::string(search_value.at(0).at(0).c_str()))); // email
    user_data.push_back(this->decrypt(std::string(search_value.at(0).at(1).c_str()))); // password
    user_data.push_back(this->decrypt(std::string(search_value.at(0).at(2).c_str()))); // name
    if(std::string(search_value.at(0).at(1).c_str()) == password) return user_data;
  } catch (const std::exception& ex) {
    std::cout << "ERROR: " << ex.what() << std::endl;
    this->curs->commit();
  }
  return std::vector<std::string>();
}

void DBControll::set_value_users(std::string target, std::string n_value, std::string clue_name, std::string clue) {
  try {
    target = this->encrypt(target);
    n_value = this->encrypt(n_value);
    clue_name = this->encrypt(clue_name);
    clue = this->encrypt(clue);
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
    owner = this->encrypt(owner);
    path_img = this->encrypt(path_img);
    offer_title = this->encrypt(offer_title);
    offer_desc = this->encrypt(offer_desc);
    offer_note = this->encrypt(offer_note);
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
    owner = this->encrypt(owner);
    std::vector<std::vector<std::string>> res;
    this->curs = new pqxx::work(*this->con);
    pqxx::result user_id = this->curs->exec("SELECT id FROM users WHERE name = '" + owner +"';");
    pqxx::result offers = this->curs->exec("SELECT user_id, img_path, title, description, note FROM offers WHERE user_id = " + std::string(user_id.at(0).at(0).c_str()) + ";");
    for(auto col : offers) {
      std::vector<std::string> tmp;
      for(auto row : col) {
        tmp.push_back(this->decrypt(std::string(row.c_str())));
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

std::vector<std::string> DBControll::getcard_data_by_title(std::string title) {
  try {
    title = this->encrypt(title);
    this->curs = new pqxx::work(*this->con);
    pqxx::result card_data = this->curs->exec("SELECT img_path, title, description, note FROM offers WHERE title = '" + title + "';");
    std::vector<std::string> result;
    result.push_back(this->decrypt(std::string(card_data[0][0].c_str())));
    result.push_back(this->decrypt(std::string(card_data[0][1].c_str())));
    result.push_back(this->decrypt(std::string(card_data[0][2].c_str())));
    result.push_back(this->decrypt(std::string(card_data[0][3].c_str())));
    this->curs->commit(); 
    return result;
  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
    this->curs->commit();
    return std::vector<std::string>();
  }
}

std::vector<std::vector<std::string>> DBControll::get_all_offers(std::string uid) {
  try {
    std::vector<std::vector<std::string>> res;
    this->curs = new pqxx::work(*this->con);
    pqxx::result offers = this->curs->exec("SELECT user_id, img_path, title, description, note FROM offers WHERE user_id != " + uid + ";");
    for(auto col : offers) {
      std::vector<std::string> tmp;
      for(auto row : col) {
        tmp.push_back(this->decrypt(std::string(row.c_str())));
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

void DBControll::update_card_by_title(std::string title, std::string n_path_img, std::string n_title, std::string n_desc, std::string n_note) {
  try {
    title = this->encrypt(title);
    n_path_img = this->encrypt(n_path_img);
    n_title = this->encrypt(n_title);
    n_desc = this->encrypt(n_desc);
    n_note = this->encrypt(n_note);
    this->curs = new pqxx::work(*this->con);
    this->curs->exec("UPDATE offers SET img_path = '" + n_path_img + "', description = '" + n_desc + "', note = '" + n_note + "' WHERE title = '" + title + "';");
    this->curs->exec("UPDATE offers SET title = '" + n_title + "' WHERE note = '" + n_note + "';");
    this->curs->commit();
  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
    this->curs->commit();
  }
}

bool DBControll::exists_card(std::string title) {
  try {
    title = this->encrypt(title);
    this->curs = new pqxx::work(*this->con);
    pqxx::result res = this->curs->exec("SELECT note FROM offers WHERE title = '" + title + "';");
    this->curs->commit();
    return res.empty();
  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
    this->curs->commit();
    return false;
  }
}


std::vector<int> DBControll::get_favorite_array_by_name(std::string name) {
  try {
    name = decrypt(name);
    this->curs = new pqxx::work(*this->con);
    pqxx::result req = this->curs->exec("SELECT favorite FROM users WHERE name = '" + name + "';");
    std::stringstream ss;
    std::vector<std::string> numbers_str;
    std::string tmp;
    for(char ch : std::string(req.at(0).at(0).c_str())) {
      if(ch == '{' || ch == '}') continue;
      if(ch == ',') {
        numbers_str.push_back(tmp);
        tmp = "";
        continue;
      }
      tmp.push_back(ch);
    }
    std::vector<int> numbers;
    for(std::string str : numbers_str) { numbers.push_back(std::stoi(str)); }
    this->curs->commit();
    return numbers;
  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
    this->curs->commit();
    return std::vector<int>();
  } 
}

std::vector<std::vector<std::string>> DBControll::get_favorite(std::string owner) {
  try {
    std::vector<std::vector<std::string>> result;
    std::vector<int> numbers = this->get_favorite_array_by_name(owner);
    owner = encrypt(owner);
    std::vector<pqxx::result> f_offers;
    for(int oid : numbers) {
      // img_path                  |    title    |    description    |             note
      pqxx::result tmp = this->curs->exec("SELECT img_path, title, description, note FROM offers WHERE id = " + std::to_string(oid) + ";");
      f_offers.push_back(tmp);
    }
    for(auto tmp_res: f_offers) {
      for(auto col : tmp_res) {
        std::vector<std::string> tmp;
        for(auto row : col) {
          tmp.push_back(this->decrypt(std::string(row.c_str())));
        }
        result.push_back(tmp);
      }
    }
    this->curs->commit();
    return result;
  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
    this->curs->commit();
    return std::vector<std::vector<std::string>>();
  }
}

void DBControll::add_favorite(std::string u_name, std::string offer_id) {
  try {
    std::vector<int> favorite = this->get_favorite_array_by_name(u_name);
    int target = std::stoi(offer_id);
    for(int el : favorite) if(el == target) return; 
    std::cout << "NAME: " << encrypt(u_name) << "\nNAME: " << decrypt(u_name) << std::endl;
    this->curs = new pqxx::work(*this->con);
    this->curs->exec("UPDATE users SET favorite = array_append(favorite, " + offer_id + ") WHERE name = " + u_name + ";");
    this->curs->commit();
  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
    this->curs->commit();
  }
}
