#include "card.h"

Application::Card::Card(DBControll* db_controller, std::string owner_id, std::string path_to_img, std::string c_title, std::string c_description, std::string hidden_note, wxWindow* parent, wxPoint position) : wxPanel(parent, wxID_ANY, position, wxSize(400, 210), wxBORDER_MASK) {
  this->db_controller = db_controller;
  this->owner_id = owner_id;
  this->note = hidden_note;
  wxImage tmp_img(path_to_img, wxBITMAP_TYPE_PNG);
  this->path_img = path_to_img;
  tmp_img.Rescale(150, 150);
  this->img = new wxBitmap(tmp_img);
  this->card_title = new wxStaticText(this, wxID_ANY, c_title, wxPoint(210, 5), wxSize(180, 80), wxBORDER_NONE | wxTE_CENTRE);
  this->card_title->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->card_description = new wxStaticText(this, wxID_ANY, c_description, wxPoint(210, 85), wxSize(180, 110), wxBORDER_NONE);
  this->card_description->SetFont(wxFont(11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->Bind(wxEVT_PAINT, &Card::draw_image, this);
  this->Bind(wxEVT_LEFT_DOWN, &Card::press_callback, this);
  this->Bind(wxEVT_RIGHT_DOWN, &Card::delete_callback, this);
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

void Application::Card::delete_callback(wxMouseEvent&) {
  std::ifstream file("../data/cu");
  std::stringstream ss;
  ss << file.rdbuf();
  std::string data_from_file = ss.str();
  std::string tmp;
  std::vector<std::string> user_data;
  for(char ch : data_from_file) {
    if(ch == '|') {
      user_data.push_back(tmp);
      tmp = "";
    } else {
      tmp.push_back(ch);
    }
  }
  file.close();
  std::string uid = this->db_controller->get_id_by_name(user_data[0]);
  if(this->owner_id == uid) this->db_controller->delete_offer_by_description(std::string(this->card_description->GetLabel()), uid);
  return;
}