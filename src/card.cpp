#include "card.h"

Application::Card::Card(DBControll* db_controller, Advertisment& ads, wxWindow* parent, wxPoint position) : wxPanel(parent, wxID_ANY, position, wxSize(400, 210), wxBORDER_MASK) {
  this->db_controller = db_controller;
  this->ads = ads;
  this->card_title = new wxStaticText(this, wxID_ANY, ads.title, wxPoint(210, 5), wxSize(180, 80), wxBORDER_NONE | wxTE_CENTRE);
  this->card_title->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->card_description = new wxStaticText(this, wxID_ANY, ads.description, wxPoint(210, 85), wxSize(180, 110), wxBORDER_NONE);
  this->card_description->SetFont(wxFont(11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->Bind(wxEVT_PAINT, &Card::draw_image, this);
  this->Bind(wxEVT_LEFT_DOWN, &Card::press_callback, this);
}

void Application::Card::draw_image(wxPaintEvent& ev) {
  wxPaintDC dc(this);
  wxMemoryInputStream stream(this->ads.image.data(), this->ads.image.size());
  wxImage img;
  if (img.LoadFile(stream, wxBITMAP_TYPE_PNG)) {
    img.Rescale(180, 180);
    wxBitmap bitimg(img);
    dc.DrawBitmap(bitimg, wxPoint(25, 25), true);
  } else {
    std::cerr << "Failed to load image from data." << std::endl;
  }
}

void Application::Card::press_callback(wxMouseEvent& ev) {
  this->dialog = new CardViewDialog(this->db_controller, this, this->ads);
  this->dialog->ShowModal();
  this->dialog->Destroy();
}
