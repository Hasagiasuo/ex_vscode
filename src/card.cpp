#include "card.h"

Application::Card::~Card() {
  try {
    if(this->img) delete this->img;
    if(this->card_title) delete this->card_title;
    if(this->card_description) delete this->card_description;
  } catch(const std::exception& er) {
    std::cout << "Delete Card error" << std::endl;
  }
}

Application::Card::Card(std::string path_to_img, std::string c_title, std::string c_description, std::string hidden_note, wxWindow* parent, wxPoint position) : wxPanel(parent, wxID_ANY, position, wxSize(400, 210), wxBORDER_MASK) {
  this->note = hidden_note;
  wxImage tmp_img(path_to_img, wxBITMAP_TYPE_PNG);
  this->path_img = path_to_img;
  tmp_img.Rescale(150, 150);
  this->img = new wxBitmap(tmp_img);
  this->card_title = new wxStaticText(this, wxID_ANY, c_title, wxPoint(210, 5), wxSize(180, 80), wxBORDER_NONE | wxTE_CENTRE);
  this->card_title->SetFont(wxFont(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->card_description = new wxStaticText(this, wxID_ANY, c_description, wxPoint(210, 85), wxSize(200, 110), wxBORDER_NONE);
  this->card_description->SetFont(wxFont(13, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->Bind(wxEVT_PAINT, &Card::draw_image, this);
  this->Bind(wxEVT_LEFT_DOWN, &Card::press_callback, this);
}

void Application::Card::draw_image(wxPaintEvent& ev) {
  wxPaintDC dc(this);
  if(this->img)
    dc.DrawBitmap(*this->img, wxPoint(25, 25), 1);
  ev.Skip();
}

void Application::Card::press_callback(wxMouseEvent& ev) {
  this->dialog = new CardViewDialog(this, this->path_img, std::string(this->card_title->GetLabel()), std::string(this->card_description->GetLabel()), this->note);
  this->dialog->ShowModal();
  this->dialog->Destroy();
}