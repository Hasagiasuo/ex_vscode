#include "dbControll.h"
#include "ads.h"

std::string DBControll::decrypt(std::string target) {
 return target;
}

std::string DBControll::encrypt(std::string target) {
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

std::string DBControll::get_id_by_description(std::string description) {
  try {
    description = this->encrypt(description);
    this->curs = new pqxx::work(*this->con);
    pqxx::result uid = this->curs->exec("SELECT user_id FROM ads WHERE description = '" + description + "';");
    this->curs->commit();
    return std::string(uid.at(0).at(0).c_str());
  } catch(const std::exception& ex) {
    std::cout << "get_id_by_description: " << ex.what() << std::endl;
    this->curs->commit();
    return std::string();
  }
}

std::string DBControll::get_id_by_name(std::string name) {
  try {
    name = this->encrypt(name);
    this->curs = new pqxx::work(*this->con);
    pqxx::result uid = this->curs->exec("SELECT id FROM users WHERE username = '" + name + "';");
    this->curs->commit();
    return std::string(uid.at(0).at(0).c_str());
  } catch(const std::exception& er) {
    std::cout << "get_id_by_name: " << er.what() << std::endl;
    this->curs->commit();
    return std::string();
  }
}

void DBControll::push_user(std::string email, std::string password, std::string name, std::string phone_number, int role_id) {
  try {
    email = this->encrypt(email);
    password = this->encrypt(password);
    name = this->encrypt(name);
    this->curs = new pqxx::work(*this->con);
    this->curs->exec(
      "INSERT INTO users (username, email, password, phone_number, role_id) VALUES ('" + name + "', '" + email + "', '" + password + "', '" + phone_number + "', " + std::to_string(role_id) + ");"
    );
    this->curs->commit();
  } catch (const std::exception& ex) {
    std::cout << "push_user: " << "ERROR: " << ex.what() << std::endl;
    this->curs->commit();
  }
}

void DBControll::delete_offer_by_description(std::string description, std::string owner_id) {
  try {
    description = this->encrypt(description);
    this->curs = new pqxx::work(*this->con);
    this->curs->exec_params("DELETE FROM ads WHERE description = $1 AND user_id = $2;", description, owner_id);
    this->curs->commit();
  } catch (const std::exception& ex) {
    std::cout << "delete_offer_by_description: " << ex.what() << std::endl;
    this->curs->commit();
  }
}

std::vector<std::string> DBControll::get_user_by_login(std::string email, std::string password) {
  try {
    email = this->encrypt(email);
    password = this->encrypt(password);
    this->curs = new pqxx::work(*this->con);
    pqxx::result search_value = this->curs->exec("SELECT email, password, username FROM users WHERE email='" + email +"';");
    this->curs->commit();
    std::vector<std::string> user_data;
    user_data.push_back(this->decrypt(std::string(search_value.at(0).at(0).c_str()))); // email
    user_data.push_back(this->decrypt(std::string(search_value.at(0).at(1).c_str()))); // password
    user_data.push_back(this->decrypt(std::string(search_value.at(0).at(2).c_str()))); // username
    if(std::string(search_value.at(0).at(1).c_str()) == password) return user_data;
  } catch (const std::exception& ex) {
    std::cout << "get_user_by_login: " << "ERROR: " << ex.what() << std::endl;
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
    std::cout << "set_value_users: " << "ERROR: " << er.what() << std::endl;
    this->curs->commit();
  }
}

void DBControll::push_offer(std::string owner, std::string category, std::string offer_title, std::string offer_desc, float price, float amount, std::vector<char> img) {
  try {
    this->curs = new pqxx::work(*this->con);
    pqxx::result user_id = this->curs->exec("SELECT id FROM users WHERE username = '" + owner +"';");
    std::string uid = std::string(user_id.at(0).at(0).c_str());
    this->curs->exec_params("INSERT INTO ads (user_id, category, title, description, price, status_id, amount, img) VALUES ($1, $2, $3, $4, $5, $6, $7, $8)",
      uid,
      category,
      offer_title,
      offer_desc,
      price,
      0,
      amount,
      pqxx::binarystring(img.data(), img.size())
    );
    this->curs->commit();
  } catch (const std::exception& er) {
    std::cout << "push_offer: " << "ERROR: " << er.what() << std::endl;
    this->curs->commit();
  }
}

std::vector<Advertisment*> DBControll::get_offers(std::string owner) {
  try {
    owner = this->encrypt(owner);
    std::vector<Advertisment*> res;
    this->curs = new pqxx::work(*this->con);
    pqxx::result user_id = this->curs->exec("SELECT id FROM users WHERE username = '" + owner +"';");
    pqxx::result offers = this->curs->exec("SELECT user_id, category, title, description, price, status_id, amount, img FROM ads WHERE user_id = " + std::string(user_id.at(0).at(0).c_str()) + ";");
    for(auto col : offers) {
      Advertisment* tmp = new Advertisment;
      tmp->uid = std::stoi(col.at(0).c_str());
      tmp->category = std::string(col.at(1).c_str());
      tmp->title = std::string(col.at(2).c_str());
      tmp->description = std::string(col.at(3).c_str());
      tmp->price = std::stof(col.at(4).c_str());
      tmp->status_id = std::stoi(col.at(5).c_str());
      tmp->amount = std::stof(col.at(6).c_str());
      std::string bytea = col.at(7).as<std::string>();
      if (bytea.size() >= 2 && bytea[0] == '\\' && bytea[1] == 'x') {
        bytea = bytea.substr(2); // Відкидаємо "\\x"
      }
      std::vector<unsigned char> image_data;
      for (size_t i = 0; i < bytea.size(); i += 2) {
        std::string byte_str = bytea.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(std::stoi(byte_str, nullptr, 16));
        image_data.push_back(byte);
      }
      tmp->image = image_data;
      res.push_back(tmp);
    }
    this->curs->commit();
    return res;
  } catch (const std::exception& er) {
    std::cout << "get_offers: " << "ERROR: " << er.what() << std::endl;
    this->curs->commit();
    return std::vector<Advertisment*>();
  }
}

Advertisment* DBControll::get_card_data_by_title(std::string title) {
  try {
    title = this->encrypt(title);
    this->curs = new pqxx::work(*this->con);
    pqxx::result card_data = this->curs->exec("SELECT user_id, category, description, price, status_id, amount, img FROM ads WHERE title = '" + title + "';");
    pqxx::binarystring image_data(card_data.at(0).at(6));
    Advertisment* result = new Advertisment;
    result->uid = std::stoi(card_data.at(0).at(0).c_str());
    result->category = card_data.at(0).at(1).c_str();
    result->title = title;
    result->description = card_data.at(0).at(2).c_str();
    result->price = std::stof(card_data.at(0).at(3).c_str());
    result->status_id = std::stoi(card_data.at(0).at(4).c_str());
    result->amount = std::stoi(card_data.at(0).at(5).c_str());
    result->image = std::vector<unsigned char>(image_data.begin(), image_data.end());
    this->curs->commit();
    return result;
  } catch (const std::exception& ex) {
    std::cout << "get_card_data_by_title: " << ex.what() << std::endl;
    this->curs->commit();
    return new Advertisment;
  }
}

std::vector<Advertisment*> DBControll::get_all_offers(std::string uid) {
  try {
    std::vector<Advertisment*> res;
    this->curs = new pqxx::work(*this->con);
    pqxx::result offers = this->curs->exec("SELECT user_id, category, title, description, price, status_id, amount, img FROM ads WHERE user_id != " + uid + ";");
    for(auto col : offers) {
      Advertisment* tmp = new Advertisment;
      tmp->uid = std::stoi(col.at(0).c_str());
      tmp->category = std::string(col.at(1).c_str());
      tmp->title = std::string(col.at(2).c_str());
      tmp->description = std::string(col.at(3).c_str());
      tmp->price = std::stof(col.at(4).c_str());
      tmp->status_id = std::stoi(col.at(5).c_str());
      tmp->amount = std::stof(col.at(6).c_str());
      std::string bytea = col.at(7).as<std::string>();
      if (bytea.size() >= 2 && bytea[0] == '\\' && bytea[1] == 'x') {
        bytea = bytea.substr(2);
      }
      std::vector<unsigned char> image_data;
      for (size_t i = 0; i < bytea.size(); i += 2) {
        std::string byte_str = bytea.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(std::stoi(byte_str, nullptr, 16));
        image_data.push_back(byte);
      }
      tmp->image = image_data;
      res.push_back(tmp);
    }
    this->curs->commit();
    return res;
  } catch (const std::exception& er) {
    std::cout << "get_all_offers: " << "ERROR: " << er.what() << std::endl;
    this->curs->commit();
    return std::vector<Advertisment*>();
  }
}

void DBControll::update_card_by_title(Advertisment* n_ads) {
  try {
    // title = this->encrypt(title);
    // n_path_img = this->encrypt(n_path_img);
    // n_title = this->encrypt(n_title);
    // n_desc = this->encrypt(n_desc);
    // n_note = this->encrypt(n_note);
    this->curs = new pqxx::work(*this->con);
    this->curs->exec("UPDATE ads SET category = '" + n_ads->category + "', description = '" + n_ads->description + "', price = " + std::to_string(n_ads->price) + ", status_id = " + std::to_string(n_ads->status_id) + ", amount = " + std::to_string(n_ads->amount) + " WHERE title = '" + n_ads->title + "';");
    if(n_ads->image.size() > 0) {
      this->curs->exec_params("UPDATE ads SET img = $1 WHERE title = $2;",
        pqxx::binarystring(n_ads->image.data(), n_ads->image.size()),
        n_ads->title
      );
    }
    this->curs->exec("UPDATE ads SET title = '" + n_ads->title + "' WHERE description = '" + n_ads->description + "';");
    this->curs->commit();
  } catch (const std::exception& ex) {
    std::cout << "update_card_by_title: " << ex.what() << std::endl;
    this->curs->commit();
  }
}

bool DBControll::exists_card(std::string title) {
  try {
    title = this->encrypt(title);
    this->curs = new pqxx::work(*this->con);
    pqxx::result res = this->curs->exec("SELECT description FROM ads WHERE title = '" + title + "';");
    this->curs->commit();
    return res.empty();
  } catch (const std::exception& ex) {
    std::cout << "exists_card: " << ex.what() << std::endl;
    this->curs->commit();
    return false;
  }
}

void DBControll::udpate_state_by_title(std::string title, int state_code) {
  try {
    this->curs = new pqxx::work(*this->con);
    this->curs->exec("UPDATE ads SET status_id = " + std::to_string(state_code) + " WHERE title = '" + title + "';");
    this->curs->commit();
  } catch (const std::exception& ex) {
    std::cout << "udpate_state_by_title: " << ex.what() << std::endl;
    this->curs->commit();
  }
}
