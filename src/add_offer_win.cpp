#include "add_offer_win.h"

OfferWinAdd::OfferWinAdd(DBControll* db_controller, std::string name, std::string email, std::string password)
: wxFrame(nullptr, wxID_ANY, "", wxPoint(wxDisplay().GetGeometry().GetSize().x / 2 - 300, wxDisplay().GetGeometry().GetSize().y / 2 - 300), wxSize(600, 600), wxBORDER_NONE){
  this->db_controller = db_controller;
  this->name = name;
  this->email = email;
  this->password = password;
  this->path_img = nullptr;

  wxStaticText* info_path = new wxStaticText(this, wxID_ANY, "Оберіть зображення для вашої пропозиції (.png)", wxPoint(20, 20), wxSize(150, 20));
  info_path->SetFont(wxFont(17, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));

  this->under_text = new wxStaticText(this, wxID_ANY, "тут буде ваше зображення", wxPoint(60, 130), wxSize(60, 20));

  this->path_img = new wxFilePickerCtrl(this, wxID_ANY, "", "", "", wxPoint(20, 250), wxSize(100, 20), wxBORDER_SUNKEN);
  this->path_img->SetFont(wxFont(13, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  this->path_img->Bind(wxEVT_FILEPICKER_CHANGED, &OfferWinAdd::file_picked, this);

  wxStaticText* info_title = new wxStaticText(this, wxID_ANY, "Введіть заголовок вашої пропозиції", wxPoint(20, 280), wxSize(150, 20));
  info_title->SetFont(wxFont(17, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
  this->title = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20, 300), wxSize(150, 20), wxBORDER_SUNKEN);
  this->title->SetFont(wxFont(13, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

  wxStaticText* info_description = new wxStaticText(this, wxID_ANY, "Коротко опишіть пропозицію", wxPoint(20, 330), wxSize(150, 20));
  info_description->SetFont(wxFont(17, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
  this->description = new wxRichTextCtrl(this, wxID_ANY, "" , wxPoint(20, 350), wxSize(250, 40), wxBORDER_SUNKEN);
  this->description->SetFont(wxFont(13, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  this->description->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);

  wxStaticText* price_info = new wxStaticText(this, wxID_ANY, "Введіть ціну за одиницю", wxPoint(20, 400), wxSize(100, 20));
  price_info->SetFont(wxFont(17, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
  this->price = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(20, 425), wxSize(150, 20), wxBORDER_NONE);
  this->price->SetRange(1, 1000000);
  this->price->SetFont(wxFont(17, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
  wxStaticText* pr_in = new wxStaticText(this, wxID_ANY, "грн.", wxPoint(175, 425), wxSize(50, 20));
  pr_in->SetFont(wxFont(17, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));

  wxStaticText* amount_info = new wxStaticText(this, wxID_ANY, "Введіть одиниць товару для продажу", wxPoint(20, 450), wxSize(100, 20));
  amount_info->SetFont(wxFont(17, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
  this->amount = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(20, 475), wxSize(150, 20), wxBORDER_NONE);
  this->amount->SetRange(1, 1000);
  this->amount->SetFont(wxFont(17, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));

  const wxString choices[] = {
    "Засоби захисту",
    "Тактичне спорядження",
    "Засоби зв'язку та електроніка",
    "Медичне забезпечення",
    "Інженерне обладнання",
    "Логістика та польове забезпечення",
    "Засоби маскування та введення в оману",
    "Засоби для виживання"
  };
  wxStaticText* category_info = new wxStaticText(this, wxID_ANY, "Категорія товару", wxPoint(20, 500), wxSize(100, 20));
  category_info->SetFont(wxFont(17, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
  this->category = new wxChoice(this, wxID_ANY, wxPoint(20, 520), wxSize(150, 40), sizeof(choices) / sizeof(wxString), choices);

  wxButton* btn_commit = new wxButton(this, wxID_ANY, "Додати пропозицію", wxPoint(60, 560), wxSize(480, 20), wxBORDER_DOUBLE);
  btn_commit->SetFont(wxFont(17, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
  btn_commit->Bind(wxEVT_BUTTON, &OfferWinAdd::btn_callback, this);

  wxButton* btn_close = new wxButton(this, wxID_ANY, "X", wxPoint(575, 5), wxSize(20, 20), wxBORDER_NONE);
  btn_close->SetFont(wxFont(17, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
  btn_close->Bind(wxEVT_BUTTON, &OfferWinAdd::close_callback, this);

  this->error_message = new wxStaticText(this, wxID_ANY, "", wxPoint(0, 580), wxSize(600, 10), wxTE_CENTRE);
  this->error_message->SetFont(wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
  this->error_message->SetForegroundColour(*wxRED);
}

void OfferWinAdd::file_picked(wxFileDirPickerEvent&) {
  wxImage img(this->path_img->GetPath(), wxBITMAP_TYPE_PNG);
  img.Rescale(200, 200);
  this->choice_img = new wxBitmap(img);
  this->Bind(wxEVT_PAINT, &OfferWinAdd::draw_img, this);
  this->Refresh();
}

void OfferWinAdd::close_callback(wxCommandEvent&) {
  Application::ProfileWindow* pw = new Application::ProfileWindow(this->db_controller, this->name, this->email, this->password);
  pw->Show();
  this->Close();
}

void OfferWinAdd::btn_callback(wxCommandEvent&) {
  if(this->path_img->GetPath() == wxEmptyString) {
    this->error_message->SetLabel("Фото не обране!");
    return;
  } else if(this->title->GetValue() == wxEmptyString) {
    this->error_message->SetLabel("Напишіть заголовок до пропозиції!");
    return;
  } else if(this->description->GetValue() == wxEmptyString || std::string(this->description->GetValue()).length() < 5) {
    this->error_message->SetLabel("Опишіть пропозицію!");
    return;
  }
  if(!this->db_controller->exists_card(std::string(this->title->GetValue()))) {
    wxMessageBox("Така пропозиція вже існує!");
    return;
  }
  this->db_controller->push_offer(
    this->name,
    std::string(this->category->GetStringSelection()),
    std::string(this->title->GetValue()),
    std::string(this->description->GetValue()),
    this->price->GetValue(),
    this->amount->GetValue(),
    this->load_image(std::string(this->path_img->GetPath()))
  );
  Application::ProfileWindow* pw = new Application::ProfileWindow(this->db_controller, this->name, this->email, this->password);
  pw->Show();
  this->Close();
}

void OfferWinAdd::draw_img(wxPaintEvent& ev) {
  wxPaintDC dc(this);
  if(this->choice_img) {
    dc.DrawBitmap(*this->choice_img, wxPoint(20, 40));
    this->under_text->Hide();
  }
  ev.Skip();
}

std::vector<char> OfferWinAdd::load_image(std::string path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Unable to open file: " + path);
  }
  return std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}
