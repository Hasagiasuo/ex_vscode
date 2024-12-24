#include "mainFrame.h"

Application::MainFrame::MainFrame(DBControll* db_controll, std::string name, std::string email, std::string password) : wxFrame(nullptr, wxID_ANY, "Index", wxPoint(wxDisplay().GetGeometry().GetSize().x / 2 - 400, wxDisplay().GetGeometry().GetSize().y / 2 - 400), wxSize(800, 800), wxBORDER_NONE) {
  wxAcceleratorEntry hot_keys[1];
  hot_keys[0].Set(M_KEY, (int)'R', id_REFRESH);
  this->db_controller = db_controll; 
  this->card_x = 0;
  this->card_y = 0;
  this->username = name;
  this->user_email = email;
  this->user_password = password;
  wxIcon icon("../assets/icon.png", wxBITMAP_TYPE_PNG);
  this->SetIcon(icon);
  this->Bind(wxEVT_MENU, &MainFrame::refresh_callback, this, id_REFRESH);
  this->gen_widgets();
}

void Application::MainFrame::draw_offers() {
  if(this->ads.size() > 0) {
    for(Advertisment* ad : this->ads) this->add_card(ad);
  } else {
    this->ads = this->db_controller->get_all_offers(this->db_controller->get_id_by_name(this->username));
    for(Advertisment* ad : this->ads) this->add_card(ad);
  }
}

void Application::MainFrame::gen_widgets() {
  this->gen_top_bar();
  this->gen_main_menu();
}

void Application::MainFrame::gen_top_bar() {
  this->top_menu_bar = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 30), wxBORDER_SUNKEN);

  wxImage img_refresh("../assets/refresh.png", wxBITMAP_TYPE_PNG);
  img_refresh.Rescale(20, 20);
  wxBitmap bitmap_refresh(img_refresh);
  wxBitmapButton* btn_refresh = new wxBitmapButton(this->top_menu_bar, wxID_ANY, bitmap_refresh, wxPoint(750, 5), wxSize(20, 20), wxBORDER_NONE);
  btn_refresh->Bind(wxEVT_BUTTON, &MainFrame::refresh_callback, this);

  this->img_for_profbtn = new wxBitmap("../assets/profile.png", wxBITMAP_TYPE_PNG);
  this->btn_profile = new wxBitmapButton(this->top_menu_bar, wxID_ANY, *this->img_for_profbtn, wxPoint(5, 7), wxSize(20, 20), wxBORDER_NONE);
  this->btn_profile->Bind(wxEVT_BUTTON, &MainFrame::gen_burger, this);

  this->img_for_search = new wxBitmap("../assets/search.png", wxBITMAP_TYPE_PNG);
  this->btn_search = new wxBitmapButton(this->top_menu_bar, wxID_ANY, *this->img_for_search, wxPoint(35, 7), wxSize(20, 20), wxBORDER_NONE);
  this->search_entry = new wxTextCtrl(this->top_menu_bar, wxID_ANY, "", wxPoint(60, 7), wxSize(160, 20), wxBORDER_NONE);
  this->search_entry->SetFont(wxFont(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->search_entry->Bind(wxEVT_KEY_DOWN, &MainFrame::search_some, this);
  this->search_entry->Hide();
  this->btn_search->Bind(wxEVT_BUTTON, &MainFrame::search_open, this);

  const wxString choices[] = {
    "Усі",
    "Засоби захисту",
    "Тактичне спорядження",
    "Засоби зв'язку та електроніка",
    "Медичне забезпечення",
    "Інженерне обладнання",
    "Логістика",
    "Засоби маскування",
    "Засоби для виживання"
  };
  this->category_search = new wxChoice(this, wxID_ANY, wxPoint(65, 8), wxSize(150, 20), sizeof(choices) / sizeof(wxString), choices);
  this->category_search->Bind(wxEVT_CHOICE, &MainFrame::category_callback, this);
  this->category_search->Hide();
  
  this->username_l = new wxStaticText(this->top_menu_bar, wxID_ANY, "MTP|" + this->username, wxPoint(330, 5), wxSize(100, 20), wxTE_CENTRE);
  this->username_l->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  this->btn_close = new wxButton(this->top_menu_bar, wxID_CLOSE, "X", wxPoint(770, 5), wxSize(25, 20), wxBORDER_NONE);
  this->btn_close->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->btn_close->Bind(wxEVT_BUTTON, &MainFrame::close_window, this);
}

void Application::MainFrame::gen_burger(wxCommandEvent&) {
  this->burger_menu = new wxMenu;
  this->burger_menu->Append(MainFrameID::idPROFILE, "Профіль");
  this->burger_menu->Append(MainFrameID::idINFO, "Інфо");
  this->burger_menu->Append(MainFrameID::idLOGOUT, "Вийти");
  Bind(wxEVT_MENU, &MainFrame::profile_callback, this, idPROFILE);
  Bind(wxEVT_MENU, &MainFrame::logout_profile, this, idLOGOUT);
  Bind(wxEVT_MENU, &MainFrame::info_callback, this, idINFO);
  this->PopupMenu(this->burger_menu, wxPoint(0, 30));
}

void Application::MainFrame::profile_callback(wxCommandEvent&) {
  ProfileWindow* pw = new ProfileWindow(this->db_controller, this->username, this->user_email, this->user_password);
  pw->Show();
  this->Close();
}

void Application::MainFrame::logout_profile(wxCommandEvent&) {
  std::ofstream file("../data/cu");
  file << "";
  file.close();
  LoginWindow* lw = new LoginWindow(this->db_controller);
  lw->Show();
  this->Close();
}

void Application::MainFrame::gen_main_menu() {
  this->main_menu = new wxScrolledWindow(this, wxID_ANY, wxPoint(0, 30), wxSize(800, 770), wxBORDER_SUNKEN);
  this->main_menu->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
  this->sizer_main = new wxFlexGridSizer(2);
  this->main_menu->SetScrollRate(1, 1);
  this->main_menu->SetVirtualSize(wxSize(800, 800));
  this->main_menu->SetSizer(this->sizer_main);
  this->main_menu->Layout();
  this->draw_offers();
}

void Application::MainFrame::close_window(wxCommandEvent&) {
  this->Close();
}

void Application::MainFrame::search_open(wxCommandEvent&) {
  if(this->search_id++ == 2) this->search_id = 0;
  if(this->search_id == 1) {
    this->search_entry->Show();
  } else if(this->search_id == 2) {
    this->search_entry->Hide();
    this->category_search->Show();
  } else {
    this->search_entry->Hide();
    this->category_search->Hide();
  }
} 

void Application::MainFrame::search_some(wxKeyEvent& ev) {
  if(ev.GetKeyCode() == WXK_RETURN) {
    this->search_callback(); 
    this->search_entry->SetValue("");
    this->search_entry->Hide();
  }
  ev.Skip();
}

void Application::MainFrame::add_card(Advertisment* ad) {
  Card* tmp_card = new Card(this->db_controller, *ad, this->main_menu, wxPoint(this->card_x, this->card_y));
  this->cards.push_back(tmp_card);
  if(this->cards.size() > 6 && this->cards.size() % 2 == 0) {
    int x, y;
    this->main_menu->GetVirtualSize(&x, &y);
    this->main_menu->SetVirtualSize(x, y + 200);
  }
  this->sizer_main->Add(tmp_card);
  this->main_menu->SetSizer(this->sizer_main);
  this->main_menu->Layout();
  if(this->card_x == 380) {
    this->card_y += 210;
    this->card_x = 0;
  } else {
    this->card_x += 400;
  }
}

void Application::MainFrame::refresh_callback(wxCommandEvent &) {
  for (Card* card : this->cards) {
    delete card;
  }
  this->cards.clear();
  this->ads.clear();
  this->ads = this->db_controller->get_all_offers(this->db_controller->get_id_by_name(this->username));
  for(Advertisment* ad : this->ads) this->add_card(ad);
  this->sizer_main->Clear();
  this->main_menu->Layout();
}

void Application::MainFrame::set_title(std::string new_val) {
  this->username_l->SetLabel(new_val);
}

void Application::MainFrame::search_callback() {
  std::string search_value = std::string(this->search_entry->GetValue());
  if(search_value.length() == 0) return;
  this->dialog_s = new wxDialog(this, wxID_ANY, "", wxPoint(wxDisplay().GetGeometry().GetSize().x / 2 - 400, wxDisplay().GetGeometry().GetSize().y / 2 - 300), wxSize(800, 600), wxBORDER_NONE);
  wxStaticText* info_dialog = new wxStaticText(this->dialog_s, wxID_ANY, "Результат пошуку '" + search_value + "':", wxPoint(50, 5), wxSize(700, 30), wxTE_CENTRE);
  info_dialog->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  wxButton* btn_close_dialog = new wxButton(this->dialog_s, wxID_ANY, "X", wxPoint(775, 5), wxSize(20, 20), wxBORDER_NONE);
  btn_close_dialog->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  btn_close_dialog->Bind(wxEVT_BUTTON, &MainFrame::close_dialog_callback, this);
  this->scrl_win_dialog = new wxScrolledWindow(this->dialog_s, wxID_ANY, wxPoint(0, 70), wxSize(800, 770), wxBORDER_SUNKEN);
  scrl_win_dialog->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
  this->sizer_dialog = new wxFlexGridSizer(2);
  scrl_win_dialog->SetScrollRate(5, 5);
  scrl_win_dialog->SetVirtualSize(wxSize(800, 800));
  scrl_win_dialog->SetSizer(this->sizer_dialog);
  scrl_win_dialog->Layout();
  int c_x = 0;
  int c_y = 0;
  std::vector<Advertisment*> offers = this->db_controller->get_all_offers(this->db_controller->get_id_by_name(this->username));
  this->sizer_dialog->Clear();
  scrl_win_dialog->Layout();
  scrl_win_dialog->SetSizer(this->sizer_dialog);
  std::vector<Card*> cards;
  for(Advertisment* row : offers) {
    if(row->title.find(search_value) != std::string::npos) {
      Card* tmp_card = new Card(this->db_controller, *row, this->scrl_win_dialog, wxPoint(c_x, c_y));
      cards.push_back(tmp_card);
      if(cards.size() > 6 && cards.size() % 2 == 0) {
        int x, y;
        scrl_win_dialog->GetVirtualSize(&x, &y);
        scrl_win_dialog->SetVirtualSize(x, y + 200);
      }
      this->sizer_dialog->Add(tmp_card);
      this->scrl_win_dialog->SetSizer(this->sizer_dialog);
      this->scrl_win_dialog->Layout();
      if(c_x == 380) {
        c_y += 210;
        c_x = 0;
      } else {
        c_x += 400;
      }   
    }
  }   
  this->dialog_s->Show();
  this->Hide();
}

void Application::MainFrame::close_dialog_callback(wxCommandEvent&) {
  this->dialog_s->Close();
  this->Show();
}

void Application::MainFrame::info_callback(wxCommandEvent&) {
  Info* info = new Info();
  info->ShowModal();
  info->Destroy();
}

void Application::MainFrame::category_callback(wxCommandEvent& event) {
  wxChoice* choice = dynamic_cast<wxChoice*>(event.GetEventObject());
  if (choice) {
    wxString selected = choice->GetString(choice->GetSelection());
    this->category_search->SetSelection(0);
    this->category_search_callback(selected);
  }
}

void Application::MainFrame::category_search_callback(wxString target) {
  if(target == "Усі") return;
  this->dialog_s = new wxDialog(this, wxID_ANY, "", wxPoint(wxDisplay().GetGeometry().GetSize().x / 2 - 400, wxDisplay().GetGeometry().GetSize().y / 2 - 300), wxSize(800, 600), wxBORDER_NONE);
  wxStaticText* info_dialog = new wxStaticText(this->dialog_s, wxID_ANY, "Результат пошуку за категорією '" + target + "':", wxPoint(50, 5), wxSize(700, 30), wxTE_CENTRE);
  info_dialog->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  wxButton* btn_close_dialog = new wxButton(this->dialog_s, wxID_ANY, "X", wxPoint(775, 5), wxSize(20, 20), wxBORDER_NONE);
  btn_close_dialog->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  btn_close_dialog->Bind(wxEVT_BUTTON, &MainFrame::close_dialog_callback, this);
  this->scrl_win_dialog = new wxScrolledWindow(this->dialog_s, wxID_ANY, wxPoint(0, 70), wxSize(800, 770), wxBORDER_SUNKEN);
  scrl_win_dialog->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
  this->sizer_dialog = new wxFlexGridSizer(2);
  scrl_win_dialog->SetScrollRate(5, 5);
  scrl_win_dialog->SetVirtualSize(wxSize(800, 800));
  scrl_win_dialog->SetSizer(this->sizer_dialog);
  scrl_win_dialog->Layout();
  int c_x = 0;
  int c_y = 0;
  std::vector<Advertisment*> offers = this->db_controller->get_all_offers(this->db_controller->get_id_by_name(this->username));
  this->sizer_dialog->Clear();
  scrl_win_dialog->Layout();
  scrl_win_dialog->SetSizer(this->sizer_dialog);
  std::vector<Card*> cards;
  for(Advertisment* row : offers) {
    if(row->category == target) {
      Card* tmp_card = new Card(this->db_controller, *row, this->scrl_win_dialog, wxPoint(c_x, c_y));
      cards.push_back(tmp_card);
      if(cards.size() > 6 && cards.size() % 2 == 0) {
        int x, y;
        scrl_win_dialog->GetVirtualSize(&x, &y);
        scrl_win_dialog->SetVirtualSize(x, y + 200);
      }
      this->sizer_dialog->Add(tmp_card);
      this->scrl_win_dialog->SetSizer(this->sizer_dialog);
      this->scrl_win_dialog->Layout();
      if(c_x == 380) {
        c_y += 210;
        c_x = 0;
      } else {
        c_x += 400;
      }   
    }
  }   
  this->dialog_s->Show();
  this->Hide();
}
