#include "loginWin.h"

Application::LoginWindow::LoginWindow(DBControll* db_controll) : wxFrame(nullptr, wxID_ANY, "Увійти", wxPoint(wxDisplay().GetGeometry().GetSize().x / 2 - 250, wxDisplay().GetGeometry().GetSize().y / 2 - 145), wxSize(500, 250), wxBORDER_NONE), db_controller(db_controll) {
  this->gen_widgets();
  this->Hide();
}

void Application::LoginWindow::gen_widgets() {
  this->panel = new wxPanel(this, wxID_ANY);
  this->sizer = new wxBoxSizer(wxVERTICAL);
  this->btn_close = new wxButton(this->panel, wxID_CLOSE, "X", wxPoint(470, 5), wxSize(25, 20), wxBORDER_NONE);
  this->btn_close->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
  this->btn_close->Bind(wxEVT_BUTTON, &LoginWindow::close_window, this);
  this->email_l = new wxStaticText(this->panel, wxID_ANY, "Ел. пошта", wxPoint(30, 40), wxSize(50, 30), wxTE_CENTRE);
  this->email_l->SetFont(wxFont(20, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->email = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(150, 40), wxSize(300, 30), wxTE_CENTRE);
  this->email->SetFont(wxFont(20, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->password_l = new wxStaticText(this->panel, wxID_ANY, "Пароль", wxPoint(40, 90), wxSize(50, 30), wxTE_CENTRE);
  this->password_l->SetFont(wxFont(20, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->password = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(150, 90), wxSize(300, 30), wxTE_PASSWORD | wxTE_CENTRE);
  this->password->SetFont(wxFont(20, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->btn_commit = new wxButton(this->panel, wxID_ANY, "Увійти", wxPoint(75, 140), wxSize(350, 40));
  this->btn_commit->SetFont(wxFont(18, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_MEDIUM));
  this->btn_commit->Bind(wxEVT_BUTTON, &LoginWindow::check_user_in_system, this);
  this->message_for_signup = new wxStaticText(this->panel, wxID_ANY, "Якщо у вас немає акаунту - ", wxPoint(122, 185), wxSize(100, 17), wxTE_CENTRE | wxTE_CENTER);
  this->message_for_signup->SetFont(wxFont(13, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  this->btn_signup = new wxButton(this->panel, wxID_ANY, "зареєструйтеся", wxPoint(272, 185), wxSize(110, 15), wxBORDER_NONE);
  this->btn_signup->SetFont(wxFont(13, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->btn_signup->Bind(wxEVT_BUTTON, &LoginWindow::go_to_signup, this);
  this->error_message = new wxStaticText(this->panel, wxID_ANY, "", wxPoint(0, 205), wxSize(500, 10), wxTE_CENTRE);
  this->error_message->SetFont(wxFont(14, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT));
  this->error_message->SetForegroundColour(*wxRED);
  this->sizer->Add(this->email);
  this->sizer->Add(this->password);
}

void Application::LoginWindow::check_user_in_system(wxCommandEvent&) {
  std::vector<std::string> user_data = this->db_controller->get_user_by_login(std::string(this->email->GetValue()), std::string(this->password->GetValue()));
  if(!user_data.empty()) {
    std::ofstream file("../data/cu");
    if(file.is_open()) file << user_data[2] << "|" << user_data[0] << "|" << user_data[1] << "|";
    file.close();
    MainFrame* mf = new MainFrame(this->db_controller, user_data[2], user_data[0], user_data[1]);
    this->Close();
    mf->Show();
  } else {
    this->error_message->SetLabel("Невірний пароль або електронна пошта!");
  }
  this->email->SetValue("");
  this->password->SetValue("");
}

void Application::LoginWindow::go_to_signup(wxCommandEvent&) {
  SignWindow* sw = new SignWindow(this->db_controller);
  sw->Show();
  this->Close();
}

void Application::LoginWindow::close_window(wxCommandEvent&) {
  this->Close();
  this->~LoginWindow();
}