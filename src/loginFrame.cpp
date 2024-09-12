#include "loginFrame.h"

LoginFrame::~LoginFrame() {
  delete this->bg_image;
  delete this->login;
  delete this->password;
  delete this->db_controller;
}

LoginFrame::LoginFrame(DBControll* db_controller) : wxFrame(nullptr, wxID_ANY, "Login", wxDefaultPosition, wxSize(300, 200)) {
  this->db_controller = db_controller;
  this->db_controller->create_user_table();
  // this->db_controller->push_user("admin@gmail.com", "admin1234", "admin");
  this->db_controller->show_table("users");
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
  wxButton* btn_commit = new wxButton(this, wxID_ANY, "Login", wxPoint(100, 110), wxSize(100, 30));
  btn_commit->SetForegroundColour(*wxBLACK);
  btn_commit->SetBackgroundColour(*wxBLACK);
  Bind(wxEVT_PAINT, &LoginFrame::draw_bg, this);
}

void LoginFrame::draw_bg(wxPaintEvent&) {
  wxPaintDC dc(this);
  dc.DrawBitmap(*this->bg_image, 0, 0, false);
}