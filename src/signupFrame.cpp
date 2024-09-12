#include "signupFrame.h"

SignupFrame::~SignupFrame() {
  delete this->bg_image;
  delete this->login;
  delete this->password;
  delete this->db_controller;
}

SignupFrame::SignupFrame(DBControll* db_controller) : wxFrame(nullptr, wxID_ANY, "SignUp", wxDefaultPosition, wxSize(300, 300)) {
  this->db_controller = db_controller;
  this->db_controller->create_user_table();
  wxImage bg_img("../assets/bg_login.jpeg");
  bg_img.Rescale(300, 200);
  bg_img.Blur(10);
  this->bg_image = new wxBitmap(bg_img);
  wxStaticText* login_l = new wxStaticText(this, wxID_ANY, "Email", wxPoint(32, 30));
  login_l->SetForegroundColour(*wxWHITE);
  this->login = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(120, 30), wxSize(150, 25), wxTE_CENTRE | wxTE_NO_VSCROLL);
  this->login->SetBackgroundColour(*wxBLACK);
  this->login->SetForegroundColour(*wxWHITE);
  wxStaticText* password_l = new wxStaticText(this, wxID_ANY, "Password", wxPoint(22, 80));
  password_l->SetForegroundColour(*wxWHITE);
  this->password = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(120, 80), wxSize(150, 25), wxTE_PASSWORD | wxTE_CENTRE | wxTE_NO_VSCROLL);
  this->password->SetBackgroundColour(*wxBLACK);
  this->password->SetForegroundColour(*wxWHITE);
  wxStaticText* name_l = new wxStaticText(this, wxID_ANY, "Name", wxPoint(32, 110));
  this->name = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(120, 110), wxSize(150, 25), wxTE_CENTRE);
  wxButton* btn_commit = new wxButton(this, wxID_ANY, "SignUp", wxPoint(100, 210), wxSize(100, 30));
  btn_commit->Bind(wxEVT_BUTTON, &SignupFrame::signup, this);
  Bind(wxEVT_PAINT, &SignupFrame::draw_bg, this);
}

void SignupFrame::draw_bg(wxPaintEvent&) {
  wxPaintDC dc(this);
  dc.DrawBitmap(*this->bg_image, 0, 0, false);
}

void SignupFrame::signup(wxCommandEvent &) {
  this->db_controller->push_user(std::string(this->login->GetValue()), std::string(this->password->GetValue()), std::string(this->name->GetValue()));
  this->login->SetValue("");
  this->password->SetValue("");
  this->name->SetValue("");
  wxMessageBox("User created!");
}
