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
  wxImage image(200, 200, this->ads.image.data(), wxBITMAP_TYPE_PNG);
  image.Rescale(200, 200);
  wxBitmap* bitimg = new wxBitmap(image);
  wxPaintDC dc(this);
  if(bitimg)
    dc.DrawBitmap(*bitimg, wxPoint(10, 10), 1);
}

void Application::CardViewDialog::close_callback(wxCommandEvent &) {
  this->Close();
}
 
Application::CardViewDialog::CardViewDialog(DBControll* db_controller, wxWindow* parent, Advertisment& ads) : wxDialog(parent, wxID_ANY, "", wxPoint((wxDisplay().GetGeometry().GetSize().x / 2 - 250), (wxDisplay().GetGeometry().GetSize().y / 2 - 200)), wxSize(500, 400), wxBORDER_NONE) {
  this->ads = ads;
  this->db_controller = db_controller;
  this->SetBackgroundColour(wxColor(38, 42, 48));
  this->title = new wxStaticText(this, wxID_ANY, ads.title, wxPoint(220, 30), wxSize(170, 50), wxBORDER_NONE);
  this->title->SetFont(wxFont(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->desc = new wxStaticText(this, wxID_ANY, ads.description, wxPoint(220, 90), wxSize(170, 100), wxBORDER_NONE);
  this->desc->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->category = new wxStaticText(this, wxID_ANY, ads.category, wxPoint(220, 200), wxSize(150, 20));
  this->category->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->price = new wxStaticText(this, wxID_ANY, wxString(std::to_string(ads.price)), wxPoint(220, 230), wxSize(100, 20));
  this->price->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->amount = new wxStaticText(this, wxID_ANY, wxString(std::to_string(ads.amount)), wxPoint(220, 260), wxSize(100, 20));
  this->amount->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  std::ifstream file1("../data/cu");
  std::stringstream ss1;
  ss1 << file1.rdbuf();
  std::string data_from_file = ss1.str();
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
  file1.close();

  this->btn_buy = new wxButton(this, wxID_ANY, "Замовити", wxPoint(0, 375), wxSize(500, 20), wxTE_CENTRE);
  this->btn_buy->Bind(wxEVT_BUTTON, &CardViewDialog::buy_callback, this);

  wxImage close_img("../assets/close.png", wxBITMAP_TYPE_PNG);
  close_img.Rescale(20, 20);
  wxBitmap* close_bit = new wxBitmap(close_img);
  this->btn_close = new wxBitmapButton(this, wxID_ANY, *close_bit, wxPoint(475, 5), wxSize(20, 20), wxBORDER_NONE);
  this->btn_close->SetFont(wxFont(24, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->btn_close->Bind(wxEVT_BUTTON, &CardViewDialog::close_callback, this);
  this->Bind(wxEVT_PAINT, &CardViewDialog::draw_image, this);
  std::ifstream file("../data/cu");
  std::stringstream ss;
  ss << file.rdbuf();
  std::string cu = ss.str();
  std::string username;
  for(char ch : cu) {
    if(ch == '|') break;
    username.push_back(ch); 
  }
  this->cid = this->db_controller->get_id_by_name(username);

  if(std::to_string(this->ads.uid) == cid) {
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
  EditCardDialog* ce = new EditCardDialog(this->db_controller, this, std::to_string(this->ads.uid), std::string(this->title->GetLabel()));
  ce->ShowModal();
  this->Close();
  ce->Destroy();
}

void Application::CardViewDialog::delete_callback(wxCommandEvent&) {
  if(std::to_string(this->ads.uid) == this->cid) 
    this->db_controller->delete_offer_by_description(std::string(this->desc->GetLabel()), std::to_string(this->ads.uid));
  this->Close();
}

void Application::CardViewDialog::buy_callback(wxCommandEvent&) {
  Order* tmp = new Order();
  tmp->ShowModal();
  tmp->Destroy();
}
