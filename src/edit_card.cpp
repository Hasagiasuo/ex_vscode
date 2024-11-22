#include "edit_card.h"

Application::EditCardDialog::EditCardDialog(DBControll* db_controller, wxWindow* parent, std::string owner_id, std::string card_title) : wxDialog(parent, wxID_ANY, "", wxPoint(C_X - 350, C_Y - 300), wxSize(700, 500), wxBORDER_NONE) {
  this->db_controller = db_controller;
  std::vector<std::string> card_data = this->db_controller->getcard_data_by_title(card_title);
  this->true_title = card_title;
  this->SetBackgroundColour(wxColor(38, 42, 48));
  wxStaticText* info = new wxStaticText(this, wxID_ANY, "За необхідності змініть параметри вашої пропозиції!", wxPoint(20, 20), wxSize(640, 20), wxTE_CENTRE);
  info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
 
  this->title_e = new wxTextCtrl(this, wxID_ANY, card_title, wxPoint(20, 50), wxSize(150, 20), wxBORDER_NONE);
  wxStaticText* title_info = new wxStaticText(this, wxID_ANY, "Тут впишіть новий заголовок", wxPoint(200, 50), wxSize(300, 20));
  title_info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  
  this->desc_e = new wxRichTextCtrl(this, wxID_ANY, card_data[2], wxPoint(20, 80), wxSize(300, 40), wxBORDER_NONE);
  wxStaticText* desc_info = new wxStaticText(this, wxID_ANY, "Введіть невелики опис пропозиції", wxPoint(350, 80), wxSize(200, 20));
  desc_info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
 
  this->note_e = new wxRichTextCtrl(this, wxID_ANY, card_data[3], wxPoint(20, 130), wxSize(400, 70), wxBORDER_NONE);
  wxStaticText* note_info = new wxStaticText(this, wxID_ANY, "Детально опишіть пропозицію", wxPoint(450, 130), wxSize(200, 20));
  note_info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  wxImage img(card_data[0], wxBITMAP_TYPE_PNG);
  img.Rescale(200, 200);
  this->choice_img = new wxBitmap(img);
  
  this->file_path = new wxFilePickerCtrl(this, wxID_ANY, card_data[0], "", "", wxPoint(270, 230), wxSize(350, 20));
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
  std::string n_title = std::string(this->title_e->GetValue());
  std::string n_desc = std::string(this->desc_e->GetValue());
  std::string n_note = std::string(this->note_e->GetValue());
  std::string n_img_path = std::string(this->file_path->GetPath()); 
  if(n_img_path.empty()) {
    wxStaticText* error_message = new wxStaticText(this, wxID_ANY, "Вкажіть зображення");
  }
  this->db_controller->update_card_by_title(this->true_title, n_img_path, n_title, n_desc, n_note);
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
