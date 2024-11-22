#include "card_view.h"

std::string Application::CardViewDialog::encrypt(std::string target) {
  // std::string result;
  // for(char ch : target) {
  //   result.push_back((char)((int)ch - 2));
  // }
  // return result;
  return target;
}

void Application::CardViewDialog::draw_image(wxPaintEvent&) {
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
 
Application::CardViewDialog::CardViewDialog(DBControll* db_controller, std::string owner_id, wxWindow* parent, std::string path, std::string title, std::string description, std::string note) : wxDialog(parent, wxID_ANY, "", wxPoint((wxDisplay().GetGeometry().GetSize().x / 2 - 250), (wxDisplay().GetGeometry().GetSize().y / 2 - 200)), wxSize(500, 400), wxBORDER_NONE) {
  this->path_img = path;
  this->owner_id = owner_id;
  this->db_controller = db_controller;
  this->SetBackgroundColour(wxColor(38, 42, 48));
  this->title = new wxStaticText(this, wxID_ANY, title, wxPoint(220, 30), wxSize(170, 50), wxBORDER_NONE);
  this->title->SetFont(wxFont(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->desc = new wxStaticText(this, wxID_ANY, description, wxPoint(220, 90), wxSize(170, 100), wxBORDER_NONE);
  this->desc->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
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
  this->uid = this->db_controller->get_id_by_name(this->encrypt(user_data[0]));
  this->u_name = this->encrypt(user_data[0]);

  this->note = new wxStaticText(this, wxID_ANY, note, wxPoint(15, 220), wxSize(100, 150), wxBORDER_SUNKEN);
  this->note->SetFont(wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  
  this->btn_buy = new wxButton(this, wxID_ANY, "Замовити", wxPoint(0, 375), wxSize(500, 20), wxTE_CENTRE);
  this->btn_buy->Bind(wxEVT_BUTTON, &CardViewDialog::buy_callback, this);

  wxImage close_img("../assets/close.png", wxBITMAP_TYPE_PNG);
  close_img.Rescale(20, 20);
  wxBitmap* close_bit = new wxBitmap(close_img);
  this->btn_close = new wxBitmapButton(this, wxID_ANY, *close_bit, wxPoint(475, 5), wxSize(20, 20), wxBORDER_NONE);
  this->btn_close->SetFont(wxFont(24, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->btn_close->Bind(wxEVT_BUTTON, &CardViewDialog::close_callback, this);
  this->Bind(wxEVT_PAINT, &CardViewDialog::draw_image, this);
  if(this->uid == this->owner_id) {
    wxImage delete_img("../assets/del.png", wxBITMAP_TYPE_PNG);
    delete_img.Rescale(20, 20);
    wxBitmap* delete_bit = new wxBitmap(delete_img);
    wxBitmapButton* btn_delete = new wxBitmapButton(this, wxID_ANY, *delete_bit, wxPoint(425, 5), wxSize(20, 20), wxBORDER_NONE);
    btn_delete->Bind(wxEVT_BUTTON, &CardViewDialog::delete_callback, this);
   
    wxImage img_edit("../assets/edit.png", wxBITMAP_TYPE_PNG);
    img_edit.Rescale(20, 20);
    wxBitmap* edit_bit = new wxBitmap(img_edit);
    wxBitmapButton* btn_edit = new wxBitmapButton(this, wxID_ANY, *edit_bit, wxPoint(450, 5), wxSize(20, 20), wxBORDER_NONE);
    btn_edit->Bind(wxEVT_BUTTON, &CardViewDialog::edit_dialog, this);
  }        
}

void Application::CardViewDialog::edit_dialog(wxCommandEvent&) {
  EditCardDialog* ce = new EditCardDialog(this->db_controller, this, this->owner_id, std::string(this->title->GetLabel()));
  ce->ShowModal();
  this->Close();
  ce->Destroy();
}

void Application::CardViewDialog::delete_callback(wxCommandEvent&) {
  if(this->owner_id == uid) 
    this->db_controller->delete_offer_by_description(std::string(this->desc->GetLabel()), uid);
  this->Close();
}

void Application::CardViewDialog::buy_callback(wxCommandEvent&) {
  Order* tmp = new Order();
  tmp->ShowModal();
  tmp->Destroy();
}
