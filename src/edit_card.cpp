#include "edit_card.h"

Application::EditCardDialog::EditCardDialog(DBControll* db_controller, wxWindow* parent, std::string owner_id, std::string card_title) : wxDialog(parent, wxID_ANY, "", wxPoint(C_X - 350, C_Y - 300), wxSize(700, 500), wxBORDER_NONE) {
  this->db_controller = db_controller;
  this->true_title = card_title;
  Advertisment card_data = this->db_controller->get_card_data_by_title(card_title);
  this->uid = card_data.uid;
  this->status_id = card_data.status_id;
  this->SetBackgroundColour(wxColor(38, 42, 48));
  wxStaticText* info = new wxStaticText(this, wxID_ANY, "За необхідності змініть параметри вашої пропозиції!", wxPoint(20, 20), wxSize(640, 20), wxTE_CENTRE);
  info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
 
  this->title_e = new wxTextCtrl(this, wxID_ANY, card_data.title, wxPoint(20, 50), wxSize(150, 20), wxBORDER_NONE);
  wxStaticText* title_info = new wxStaticText(this, wxID_ANY, "Заголовок пропозиції", wxPoint(200, 50), wxSize(300, 20));
  title_info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  
  this->desc_e = new wxRichTextCtrl(this, wxID_ANY, card_data.description, wxPoint(20, 80), wxSize(300, 40), wxBORDER_NONE);
  wxStaticText* desc_info = new wxStaticText(this, wxID_ANY, "Опис пропозиції", wxPoint(350, 80), wxSize(200, 20));
  desc_info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
 
  this->price_e = new wxSpinCtrlDouble(this, wxID_ANY, wxString(std::to_string(card_data.price)), wxPoint(20, 130), wxSize(50, 20));
  wxStaticText* note_info = new wxStaticText(this, wxID_ANY, "Ціна товару", wxPoint(450, 130), wxSize(200, 20));
  note_info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  this->amount_e = new wxSpinCtrlDouble(this, wxID_ANY, wxString(std::to_string(card_data.amount)), wxPoint(20, 160), wxSize(50, 20));
  wxStaticText* amount_info = new wxStaticText(this, wxID_ANY, "Кількість товару", wxPoint(450, 160), wxSize(200, 20));
  amount_info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  const wxString choices[] = {
    "Protective equipment",
    "Tactical equipment",
    "Communication equipment and electronics",
    "Medical support",
    "Engineering equipment",
    "Logistics and field support",
    "Camouflage and deception equipment",
    "Means for survival"
  };
  wxStaticText* category_info = new wxStaticText(this, wxID_ANY, "Оберіть категорію товару", wxPoint(20, 190), wxSize(100, 20));
  category_info->SetFont(wxFont(17, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
  this->category_e = new wxChoice(this, wxID_ANY, wxPoint(20, 210), wxSize(100, 40), 0, choices);

  wxImage img(200, 200, card_data.image.data(), wxBITMAP_TYPE_PNG);
  this->choice_img = new wxBitmap(img);
  
  this->file_path = new wxFilePickerCtrl(this, wxID_ANY, "", "", "", wxPoint(270, 230), wxSize(350, 20));
  this->file_path->Bind(wxEVT_FILEPICKER_CHANGED, &EditCardDialog::file_picked, this);

  wxButton* btn_commit = new wxButton(this, wxID_ANY, "Підтвердити", wxPoint(80, 465), wxSize(540, 20), wxTE_CENTRE);
  btn_commit->Bind(wxEVT_BUTTON, &EditCardDialog::commit_handle, this);
  
  wxButton* btn_close = new wxButton(this, wxID_ANY, "X", wxPoint(675, 5), wxSize(20, 20), wxBORDER_NONE);
  btn_close->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
 
  btn_close->Bind(wxEVT_BUTTON, &EditCardDialog::close_handle, this);
  this->Bind(wxEVT_PAINT, &EditCardDialog::draw_image, this);
}

void Application::EditCardDialog::commit_handle(wxCommandEvent&) {
  if(this->db_controller->exists_card(this->true_title)) {
    wxMessageBox("Така пропозиція вже існує!");
    return;
  }
  Advertisment n_ads;
  n_ads.title = std::string(this->title_e->GetValue());
  n_ads.description = std::string(this->desc_e->GetValue());
  n_ads.price = this->price_e->GetValue();
  n_ads.amount = this->amount_e->GetValue();
  n_ads.category = this->category_e->GetName();
  n_ads.uid = this->uid;
  n_ads.status_id = this->status_id;
  if(this->file_path->GetPath().empty()) {
    wxStaticText* error_message = new wxStaticText(this, wxID_ANY, "Вкажіть зображення");
  }
  std::ifstream file(this->file_path->GetPath(), std::ios::binary);
  if (!file) {
    throw std::runtime_error("Unable to open file: " + this->file_path->GetPath());
  }
  auto tmp = std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  n_ads.image = std::vector<unsigned char>(tmp.begin(), tmp.end());
  this->db_controller->update_card_by_title(n_ads);
  this->Close();
}

void Application::EditCardDialog::close_handle(wxCommandEvent&) {
  this->Close();
}

void Application::EditCardDialog::draw_image(wxPaintEvent& ev) {
  wxPaintDC dc(this);
  if(this->choice_img) {
    dc.DrawBitmap(*this->choice_img, wxPoint(40, 230));
  }
  ev.Skip();
}

void Application::EditCardDialog::file_picked(wxFileDirPickerEvent&) {
  wxImage img(this->file_path->GetPath(), wxBITMAP_TYPE_PNG);
  img.Rescale(200, 230);
  this->choice_img = new wxBitmap(img);
  this->Bind(wxEVT_PAINT, &EditCardDialog::draw_image, this);
  this->Refresh();
}
