#include "loginFrame.h"

LoginFrame::~LoginFrame() {
  delete this->bg_image;
  delete this->login;
  delete this->password;
}

LoginFrame::LoginFrame() : wxFrame(nullptr, wxID_ANY, "Login", wxDefaultPosition, wxSize(300, 200)) {
  wxImage bg_img("../assets/bg_login.jpeg");
  bg_img.Rescale(300, 200);
  bg_img.Blur(10);
  this->bg_image = new wxBitmap(bg_img);
  wxStaticText* login_l = new wxStaticText(this, wxID_ANY, "Email", wxPoint(32, 30));
  this->login = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(120, 30), wxSize(150, 25), wxTE_CENTRE | wxTE_NO_VSCROLL);
  wxStaticText* password_l = new wxStaticText(this, wxID_ANY, "Password", wxPoint(22, 80));
  this->password = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(120, 80), wxSize(150, 25), wxTE_PASSWORD | wxTE_CENTRE | wxTE_NO_VSCROLL);
  wxButton* btn_commit = new wxButton(this, wxID_ANY, "Login", wxPoint(100, 110), wxSize(100, 30));
  Bind(wxEVT_PAINT, &LoginFrame::draw_bg, this);
}

void LoginFrame::draw_bg(wxPaintEvent&) {
  wxPaintDC dc(this);
  dc.DrawBitmap(*this->bg_image, 0, 0, false);
}