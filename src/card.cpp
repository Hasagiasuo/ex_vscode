#include "card.h"

Application::Card::~Card() {
  delete this->img;
  delete this->description;
  delete this->another_info;
}

Application::Card::Card(std::string path_to_img, std::string description, std::string another_info, wxWindow* parent, wxPoint position, wxSize size) : wxPanel(parent, wxID_ANY, position, size, wxBORDER_NONE) {
  wxImage tmp_img(path_to_img, wxBITMAP_TYPE_JPEG);
  tmp_img.Rescale(200, 200);
  this->img = new wxBitmap(tmp_img);
  wxPaintDC dc(this);
  dc.DrawBitmap(*this->img, wxPoint(0, 0), 1);
  this->description = new wxStaticText(this, wxID_ANY, description, wxPoint(210, 0), wxSize(size.x - 220, size.y / 2 + size.y / 4), wxBORDER_SUNKEN);
  this->another_info = new wxStaticText(this, wxID_ANY, another_info, wxPoint(210, (size.y / 2 + size.y / 4) + 5), wxSize(size.x - 220, size.y - (size.y / 2 + size.y / 4)), wxBORDER_SUNKEN);
}