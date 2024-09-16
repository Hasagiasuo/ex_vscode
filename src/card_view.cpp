#include "card_view.h"

void Application::CardViewDialog::draw_image(wxPaintEvent &) {
  wxImage image(this->path_img, wxBITMAP_TYPE_PNG);
  image.Rescale(200, 200);
  this->img = new wxBitmap(image);
  wxPaintDC dc(this);
  if(img)
    dc.DrawBitmap(*img, wxPoint(10, 10), 1);
}

void Application::CardViewDialog::close_callback(wxCommandEvent &) {
  this->Close();
}
 
Application::CardViewDialog::CardViewDialog(wxWindow* parent, std::string path, std::string title, std::string description, std::string note) : wxDialog(parent, wxID_ANY, "", wxPoint((wxDisplay().GetGeometry().GetSize().x / 2 - 250), (wxDisplay().GetGeometry().GetSize().y / 2 - 200)), wxSize(500, 400), wxBORDER_NONE) {
  this->path_img = path;
  this->SetBackgroundColour(wxColor(38, 42, 48));
  this->title = new wxStaticText(this, wxID_ANY, title, wxPoint(220, 30), wxSize(170, 50), wxBORDER_NONE);
  this->title->SetFont(wxFont(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->desc = new wxStaticText(this, wxID_ANY, description, wxPoint(220, 90), wxSize(170, 100), wxBORDER_NONE);
  this->desc->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  this->note = new wxStaticText(this, wxID_ANY, note, wxPoint(20, 220), wxSize(460, 150), wxBORDER_SUNKEN);
  this->note->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  this->btn_close = new wxButton(this, wxID_ANY, "X", wxPoint(470, 5), wxSize(20, 20), wxBORDER_NONE);
  this->btn_close->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->btn_close->Bind(wxEVT_BUTTON, &CardViewDialog::close_callback, this);
  this->Bind(wxEVT_PAINT, &CardViewDialog::draw_image, this);
}

Application::CardViewDialog::~CardViewDialog() {
  delete this->btn_close;
  delete this->img;
  delete this->title;
  delete this->desc;
}
