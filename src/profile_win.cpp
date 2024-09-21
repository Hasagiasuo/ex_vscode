#include "profile_win.h"

Application::ProfileWindow::~ProfileWindow() {
  delete this->btn_close;

  delete this->_name;
  delete this->name_l;
  delete this->btn_nedit;

  delete this->_email;
  delete this->email_l;

  delete this->_password;
  delete this->password_l;

  delete this->user_cards;
}

Application::ProfileWindow::ProfileWindow(DBControll* db_controller, std::string name, std::string email, std::string password)
: wxFrame(nullptr, wxID_ANY, "", wxPoint(CENTER_DISPLAY_X - 400, CENTER_DISPLAY_Y - 300), wxSize(800, 600), wxBORDER_NONE) {
  this->card_x = 0;
  this->card_y = 0;
  this->db_controller = db_controller;
  this->name = name;
  this->email = email;
  this->password = password;
  this->offers = this->db_controller->get_offers(this->name);

  this->_name = new wxStaticText(this, wxID_ANY, "Імʼя користувача:", wxPoint(20, 20), wxSize(135, 20), wxBORDER_NONE);
  this->_name->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->name_l = new wxStaticText(this, wxID_ANY, this->name, wxPoint(165, 20), wxSize(this->name.length() * 10 - 5, 20));
  this->name_l->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_SLANT, wxFONTWEIGHT_BOLD));
  this->btn_nedit = new wxBitmapButton(this, wxID_ANY, wxBitmap("../assets/edit.png", wxBITMAP_TYPE_PNG), wxPoint(165 + (this->name.length() * 10 - 5), 20), wxSize(15, 15), wxBORDER_NONE);
  this->btn_nedit->Bind(wxEVT_BUTTON, &ProfileWindow::nedit_callback, this);

  this->_email = new wxStaticText(this, wxID_ANY, "Ел. пошта:", wxPoint(20, 40), wxSize(75, 20), wxBORDER_NONE);
  this->_email->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->email_l = new wxStaticText(this, wxID_ANY, this->email, wxPoint(105, 40), wxSize(this->email.length() * 10 - 5, 20));
  this->email_l->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_SLANT, wxFONTWEIGHT_BOLD));
  this->btn_eedit = new wxBitmapButton(this, wxID_ANY, wxBitmap("../assets/edit.png", wxBITMAP_TYPE_PNG), wxPoint(105 + (this->email.length() * 10 - 5), 40), wxSize(15, 15), wxBORDER_NONE);
  this->btn_eedit->Bind(wxEVT_BUTTON, &ProfileWindow::eedit_callback, this);

  this->_password = new wxStaticText(this, wxID_ANY, "Пароль:", wxPoint(20, 60), wxSize(65, 20), wxBORDER_NONE);
  this->_password->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->password_l = new wxStaticText(this, wxID_ANY, this->convert_password(), wxPoint(95, 60), wxSize(password.length() * 10 - 10, 20));
  this->password_l->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_SLANT, wxFONTWEIGHT_BOLD));
  this->btn_pedit = new wxBitmapButton(this, wxID_ANY, wxBitmap("../assets/edit.png", wxBITMAP_TYPE_PNG), wxPoint(95 + (this->password.length() * 10) - 5, 60), wxSize(15, 15), wxBORDER_NONE);
  this->btn_pedit->Bind(wxEVT_BUTTON, &ProfileWindow::pedit_callback, this);

  this->btn_add = new wxButton(this, wxID_ANY, "Додати пропозицію", wxPoint(20, 100), wxSize(200, 20));
  this->btn_add->Bind(wxEVT_BUTTON, &ProfileWindow::add_callback, this);

  this->user_cards = new wxScrolledWindow(this, wxID_ANY, wxPoint(0, 200), wxSize(800, 770), wxBORDER_SUNKEN);
  this->user_cards->SetBackgroundColour(wxColour(54, 53, 51));
  this->user_cards->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
  this->cards_sizer = new wxFlexGridSizer(0, 2, 0, 0);
  this->user_cards->SetScrollRate(10, 10);
  this->user_cards->SetVirtualSize(wxSize(800, 800));
  this->user_cards->SetSizer(this->cards_sizer);
  this->user_cards->Layout();
  this->draw_cards();

  this->btn_close = new wxButton(this, wxID_ANY, "X", wxPoint(775, 5), wxSize(20, 20), wxBORDER_NONE);
  this->btn_close->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->btn_close->Bind(wxEVT_BUTTON, &ProfileWindow::close_callback, this);
}

void Application::ProfileWindow::close_callback(wxCommandEvent&) {
  MainFrame* mf = new MainFrame(this->db_controller, this->name, this->email, this->password);
  mf->Show();
  this->Close();
}

std::string Application::ProfileWindow::convert_password() {
  std::string res;
  for(int i = 0; i < this->password.length(); ++i) res.push_back('*');
  return res;
}

// name edit 
void Application::ProfileWindow::nedit_callback(wxCommandEvent&) {
  this->nedit_window = new wxDialog(this, wxID_ANY, "", wxPoint(CENTER_DISPLAY_X - 100, CENTER_DISPLAY_Y - 60), wxSize(250, 120), wxBORDER_NONE);
  this->nedit_window->SetBackgroundColour(wxColor(38, 42, 48));
  wxStaticText* info = new wxStaticText(this->nedit_window, wxID_ANY, "Введіть нове імʼя", wxPoint(10, 10), wxSize(100, 20));
  info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  wxButton* btn_close_nedit = new wxButton(this->nedit_window, wxID_ANY, "X", wxPoint(225, 5), wxSize(20, 20), wxBORDER_NONE);
  btn_close_nedit->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  btn_close_nedit->Bind(wxEVT_BUTTON, &ProfileWindow::close_nedit_window, this);
  this->nedit_entry = new wxTextCtrl(this->nedit_window, wxID_ANY, "", wxPoint(20, 40), wxSize(210, 20));
  this->nedit_entry->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  wxButton* commit = new wxButton(this->nedit_window, wxID_ANY, "Змінити", wxPoint(55, 70), wxSize(140, 30), wxBORDER_SUNKEN);
  commit->Bind(wxEVT_BUTTON, &ProfileWindow::_nedit_callback, this);
  this->error_message_nedit = new wxStaticText(this->nedit_window, wxID_ANY, "", wxPoint(0, 100), wxSize(250, 20), wxTE_CENTRE);
  this->error_message_nedit->SetFont(wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->error_message_nedit->SetForegroundColour(*wxRED);
  this->nedit_window->Show();
}

void Application::ProfileWindow::_nedit_callback(wxCommandEvent&) {
  if(std::string(this->nedit_entry->GetValue()).length() < 3) {
    this->error_message_nedit->SetLabel("Імʼя користувача замале!");
    return;
  }
  this->db_controller->set_value_users("name", std::string(this->nedit_entry->GetValue()), "email", this->email);
  this->name_l->SetLabel(std::string(this->nedit_entry->GetValue()));
  this->name = std::string(this->nedit_entry->GetValue());
  this->btn_nedit->SetPosition(wxPoint(165 + (this->name.length() * 10 - 5), 20));
  this->update_cu();
  delete this->nedit_entry;
  this->nedit_window->Close();
}

void Application::ProfileWindow::close_nedit_window(wxCommandEvent&) {
  delete this->nedit_entry;
  delete this->error_message_nedit;
  this->nedit_window->Close();
}

// email edit
void Application::ProfileWindow::eedit_callback(wxCommandEvent&) {
  this->eedit_window = new wxDialog(this, wxID_ANY, "", wxPoint(CENTER_DISPLAY_X - 100, CENTER_DISPLAY_Y - 60), wxSize(250, 120), wxBORDER_NONE);
  this->eedit_window->SetBackgroundColour(wxColor(38, 42, 48));
  wxStaticText* info = new wxStaticText(this->eedit_window, wxID_ANY, "Введіть нову пошту", wxPoint(10, 10), wxSize(100, 20));
  info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  wxButton* btn_close_eedit = new wxButton(this->eedit_window, wxID_ANY, "X", wxPoint(225, 5), wxSize(20, 20), wxBORDER_NONE);
  btn_close_eedit->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  btn_close_eedit->Bind(wxEVT_BUTTON, &ProfileWindow::close_eedit_window, this);
  this->eedit_entry = new wxTextCtrl(this->eedit_window, wxID_ANY, "", wxPoint(20, 40), wxSize(210, 20));
  this->eedit_entry->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  wxButton* commit = new wxButton(this->eedit_window, wxID_ANY, "Змінити", wxPoint(55, 70), wxSize(140, 30), wxBORDER_SUNKEN);
  commit->Bind(wxEVT_BUTTON, &ProfileWindow::_eedit_callback, this);
  this->error_message_eedit = new wxStaticText(this->eedit_window, wxID_ANY, "", wxPoint(0, 100), wxSize(250, 20), wxTE_CENTRE);
  this->error_message_eedit->SetFont(wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->error_message_eedit->SetForegroundColour(*wxRED);
  this->eedit_window->Show();
}

void Application::ProfileWindow::_eedit_callback(wxCommandEvent&) {
  if(std::string(this->eedit_entry->GetValue()).length() < 8) {
    this->error_message_eedit->SetLabel("Пошта замала!");
    return;
  }
  this->db_controller->set_value_users("email", std::string(this->eedit_entry->GetValue()), "name", this->name);
  this->email_l->SetLabel(std::string(this->eedit_entry->GetValue()));
  this->email = std::string(this->eedit_entry->GetValue());
  this->btn_eedit->SetPosition(wxPoint(105 + (this->email.length() * 10 - 5), 40));
  this->update_cu();
  delete this->eedit_entry;
  this->eedit_window->Close();
}

void Application::ProfileWindow::close_eedit_window(wxCommandEvent&) {
  delete this->eedit_entry;
  delete this->error_message_eedit;
  this->eedit_window->Close();
}

// password edit
void Application::ProfileWindow::pedit_callback(wxCommandEvent&) {
  this->pedit_window = new wxDialog(this, wxID_ANY, "", wxPoint(CENTER_DISPLAY_X - 100, CENTER_DISPLAY_Y - 60), wxSize(250, 120), wxBORDER_NONE);
  this->pedit_window->SetBackgroundColour(wxColor(38, 42, 48));
  wxStaticText* info = new wxStaticText(this->pedit_window, wxID_ANY, "Введіть новий пароль", wxPoint(10, 10), wxSize(100, 20));
  info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  wxButton* btn_close_pedit = new wxButton(this->pedit_window, wxID_ANY, "X", wxPoint(225, 5), wxSize(20, 20), wxBORDER_NONE);
  btn_close_pedit->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  btn_close_pedit->Bind(wxEVT_BUTTON, &ProfileWindow::close_pedit_window, this);
  this->pedit_entry = new wxTextCtrl(this->pedit_window, wxID_ANY, "", wxPoint(20, 40), wxSize(210, 20));
  this->pedit_entry->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  wxButton* commit = new wxButton(this->pedit_window, wxID_ANY, "Змінити", wxPoint(55, 70), wxSize(140, 30), wxBORDER_SUNKEN);
  commit->Bind(wxEVT_BUTTON, &ProfileWindow::_pedit_callback, this);
  this->error_message_pedit = new wxStaticText(this->pedit_window, wxID_ANY, "", wxPoint(0, 100), wxSize(250, 20), wxTE_CENTRE);
  this->error_message_pedit->SetFont(wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->error_message_pedit->SetForegroundColour(*wxRED);
  this->pedit_window->Show();
}

void Application::ProfileWindow::_pedit_callback(wxCommandEvent&) {
  if(std::string(this->pedit_entry->GetValue()).length() < 8) {
    this->error_message_pedit->SetLabel("Пароль замалий!");
    return;
  }
  this->db_controller->set_value_users("password", std::string(this->pedit_entry->GetValue()), "name", this->name);
  this->password = std::string(this->pedit_entry->GetValue());
  this->password_l->SetLabel(this->convert_password());
  this->btn_pedit->SetPosition(wxPoint(95 + (this->password.length() * 10) - 5, 60));
  this->update_cu();
  delete this->pedit_entry;
  this->pedit_window->Close();
}

void Application::ProfileWindow::close_pedit_window(wxCommandEvent&) {
  delete this->pedit_entry;
  delete this->error_message_pedit;
  this->pedit_window->Close();
}


void Application::ProfileWindow::update_cu() {
  std::ofstream file("../data/cu");
  if(file.is_open()) file << this->name << "|" << this->email << "|" << this->password << "|";
  file.close();
}

void Application::ProfileWindow::draw_cards() {
  for(std::vector<std::string> row : offers) {
    if(this->card_x == 400) {
      this->card_y += 400;
      this->card_x = 0;
    } else this->card_x += 400;
    Card* tmp_card = new Card(row[0], row[1], row[2], row[3], this->user_cards, wxPoint(this->card_x, this->card_y));
    this->cards_sizer->Add(tmp_card);
  }
  this->user_cards->SetVirtualSize(wxSize(800, this->offers.size() / 2 * 400));
  this->user_cards->SetSizer(this->cards_sizer);
  this->user_cards->Layout();
}

void Application::ProfileWindow::add_callback(wxCommandEvent&) {
  try {
    OfferWinAdd* ow = new OfferWinAdd(this->db_controller, this->name, this->email, this->password);
    ow->Show();
    this->Close();
  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }
}