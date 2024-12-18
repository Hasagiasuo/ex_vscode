#include "signupWin.h"

Application::SignWindow::SignWindow(DBControll* db_controll) : wxFrame(nullptr, wxID_ANY, "Реєстрація", wxPoint(wxDisplay().GetGeometry().GetSize().x / 2 - 250, wxDisplay().GetGeometry().GetSize().y / 2 - 170), wxSize(500, 340), wxBORDER_NONE) {
  this->db_controller = db_controll;
  this->gen_widgets();
}

void Application::SignWindow::gen_widgets() {
  this->panel = new wxPanel(this, wxID_ANY);
  this->sizer = new wxBoxSizer(wxVERTICAL);
  this->btn_close = new wxButton(this->panel, wxID_CLOSE, "X", wxPoint(470, 5), wxSize(25, 20), wxBORDER_NONE);
  this->btn_close->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->btn_close->Bind(wxEVT_BUTTON, &SignWindow::close_window, this);
  wxStaticText* name_l = new wxStaticText(this->panel, wxID_ANY, "Імʼя користувача", wxPoint(10, 40), wxSize(50, 30), wxTE_CENTRE);
  name_l->SetFont(wxFont(20, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->name = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(180, 40), wxSize(300, 30), wxTE_CENTRE);
  this->name->SetFont(wxFont(18, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  wxStaticText* email_l = new wxStaticText(this->panel, wxID_ANY, "Ел. пошта", wxPoint(35, 90), wxSize(50, 30), wxTE_CENTRE);
  email_l->SetFont(wxFont(20, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->email = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(180, 90), wxSize(300, 30), wxTE_CENTRE);
  this->email->SetFont(wxFont(18, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  wxStaticText* password_l = new wxStaticText(this->panel, wxID_ANY, "Пароль", wxPoint(45, 140), wxSize(50, 30), wxTE_CENTRE);
  password_l->SetFont(wxFont(20, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->password = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(180, 140), wxSize(300, 30), wxTE_PASSWORD | wxTE_CENTRE);
  this->password->SetFont(wxFont(18, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  wxStaticText* phone_number_l = new wxStaticText(this->panel, wxID_ANY, "Номер телефону", wxPoint(15, 190), wxSize(100, 30), wxTE_CENTRE);
  phone_number_l->SetFont(wxFont(18, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->phone_number = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(180, 190), wxSize(300, 30), wxTE_CENTRE);
  this->phone_number->SetFont(wxFont(18, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->btn_commit = new wxButton(this->panel, wxID_ANY, "Зареєструватися", wxPoint(75, 240), wxSize(350, 45));
  this->btn_commit->SetFont(wxFont(18, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_MAX));
  this->btn_commit->Bind(wxEVT_BUTTON, &SignWindow::registr_user, this);
  this->error_message = new wxStaticText(this->panel, wxID_ANY, "", wxPoint(0, 290), wxSize(500, 10), wxTE_CENTRE);
  this->error_message->SetFont(wxFont(14, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT));
  this->error_message->SetForegroundColour(*wxRED);
  this->sizer->Add(this->email);
  this->sizer->Add(this->password);
}

void Application::SignWindow::close_window(wxCommandEvent&) {
  this->Close();
}

void Application::SignWindow::registr_user(wxCommandEvent&) {
  if(std::string(this->name->GetValue()).length() < 5) {
    this->error_message->SetLabel("Імʼя занадто коротке!");
    return;
  } else if(std::string(this->password->GetValue()).length() < 8) {
    this->error_message->SetLabel("Пароль має містити понад 8 символів!");
    return;
  } else if(std::string(this->email->GetValue()).length() < 10) {
    this->error_message->SetLabel("Ел. пошта має містити більше символів!");
    return;
  } else if(std::string(this->phone_number->GetValue()).length() < 10) {
    this->error_message->SetLabel("Введіть номер телефону");
    return;
  }
  this->db_controller->push_user(
    std::string(this->email->GetValue()),
    std::string(this->password->GetValue()),
    std::string(this->name->GetValue()),
    std::string(this->phone_number->GetValue()),
    std::string(this->name->GetValue()) == "admin" ? 0 : 1
  );
  this->email->SetValue("");
  this->password->SetValue("");
  this->name->SetValue("");
  this->phone_number->SetValue("");
  wxMessageBox("Успішно зареєстровано! Тепер увійдіть в акаунт!", "info", wxBORDER_NONE);
  LoginWindow* lw = new LoginWindow(this->db_controller);
  this->Close();
  lw->Show();
}
