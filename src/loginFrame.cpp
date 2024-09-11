#include "loginFrame.h"

LoginFrame::~LoginFrame() {
  delete this->bg_image;
  delete this->login;
  delete this->password;
}

LoginFrame::LoginFrame() : wxFrame(nullptr, wxID_ANY, "Login", wxDefaultPosition, wxSize(300, 200)) {
  this->bg_image = new wxBitmap();
  this->bg_image->LoadFile("../assets/bg_login.jpeg", wxBITMAP_TYPE_JPEG);
  wxStaticText* login_l = new wxStaticText(this, wxID_ANY, "Email", wxPoint(32, 30));
  this->login = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(120, 30), wxSize(150, 20));
  wxStaticText* password_l = new wxStaticText(this, wxID_ANY, "Password", wxPoint(22, 70));
  this->password = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(120, 70), wxSize(150, 20));
  wxButton* btn_commit = new wxButton(this, wxID_ANY, "Login", wxPoint(100, 110), wxSize(100, 30));
  Bind(wxEVT_PAINT, &LoginFrame::draw_bg, this);
}

void LoginFrame::draw_bg(wxPaintEvent&) {
  wxPaintDC dc(this);
  dc.DrawBitmap(*this->bg_image, 0, 0, false);
}