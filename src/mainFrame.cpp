#include "mainFrame.h"

Application::MainFrame::~MainFrame() {
  try {
    for(Card* card : this->cards) if(card) delete card;
    if(this->img_for_search) delete this->img_for_search;
    if(this->img_add) delete this->img_add;
    if(this->btn_add) delete this->btn_add;
    if(this->search_entry) delete this->search_entry;
    if(this->btn_search) delete this->btn_search;
    if(this->username_l) delete this->username_l;
    if(this->img_for_profbtn) delete this->img_for_profbtn;
    if(this->btn_profile) delete this->btn_profile;
    if(this->btn_close) delete this->btn_close;
    if(this->top_menu_bar) delete this->top_menu_bar;
    if(this->main_menu) delete this->main_menu;
    if(this->burger_menu) delete this->burger_menu;
  } catch (const std::exception& er) {
    std::cout << "Delete MainFrame error" << std::endl;
  }
}

Application::MainFrame::MainFrame(DBControll* db_controll, std::string name) : wxFrame(nullptr, wxID_ANY, "Index", wxPoint(wxDisplay().GetGeometry().GetSize().x / 2 - 400, wxDisplay().GetGeometry().GetSize().y / 2 - 400), wxSize(800, 800), wxBORDER_NONE) {
  this->db_controller = db_controll; 
  this->card_x = 0;
  this->card_y = 0;
  this->username = name;
  this->gen_widgets();
}

void Application::MainFrame::gen_widgets() {
  this->gen_top_bar();
  this->gen_main_menu();
}

void Application::MainFrame::gen_top_bar() {
  this->top_menu_bar = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 30), wxBORDER_SUNKEN);

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

  this->img_add = new wxBitmap("../assets/add.png", wxBITMAP_TYPE_PNG);
  this->btn_add = new wxBitmapButton(this->top_menu_bar, wxID_ANY, *this->img_add, wxPoint(230, 7), wxSize(20, 20), wxBORDER_NONE);
  this->btn_add->Bind(wxEVT_BUTTON, &MainFrame::add_callback, this);

  this->username_l = new wxStaticText(this->top_menu_bar, wxID_ANY, this->username, wxPoint(350, 5), wxSize(100, 20), wxTE_CENTRE);
  this->username_l->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  this->btn_close = new wxButton(this->top_menu_bar, wxID_CLOSE, "X", wxPoint(770, 5), wxSize(25, 20), wxBORDER_NONE);
  this->btn_close->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->btn_close->Bind(wxEVT_BUTTON, &MainFrame::close_window, this);
}

void Application::MainFrame::gen_burger(wxCommandEvent&) {
  this->burger_menu = new wxMenu;
  this->burger_menu->Append(MainFrameID::idPROFILE, "Профіль");
  this->burger_menu->Append(MainFrameID::idLOGOUT, "Вийти");
  Bind(wxEVT_MENU, &MainFrame::logout_profile, this, idLOGOUT);
  this->PopupMenu(this->burger_menu, wxPoint(0, 30));
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
  this->main_menu = new wxPanel(this, wxID_ANY, wxPoint(0, 30), wxSize(800, 770), wxBORDER_SUNKEN);
}

void Application::MainFrame::close_window(wxCommandEvent&) {
  this->Close();
  this->~MainFrame();
}

void Application::MainFrame::search_open(wxCommandEvent&) {
  if(this->search_entry->IsShown()) this->search_entry->Hide();
  else this->search_entry->Show();
} 

void Application::MainFrame::search_some(wxKeyEvent& ev) {
  if(ev.GetKeyCode() == WXK_RETURN) {
    // search logic
    this->search_entry->SetValue("");
    this->search_entry->Hide();
  }
  ev.Skip();
}

void Application::MainFrame::add_card(std::string path_to_img, std::string title, std::string description) {
  Card* tmp_card = new Card(path_to_img, title, description, "balalbalabdlbasjfhlasjdflkjsaldfksadfljsaklfsjkdfsj", this->main_menu, wxPoint(this->card_x, this->card_y));
  this->cards.push_back(tmp_card);
  if(this->card_x == 400) {
    this->card_y += 210;
    this->card_x = 0;
  } else {
    this->card_x += 400;
  }
}

void Application::MainFrame::add_callback(wxCommandEvent&) {
  this->add_card("../assets/test1.png", "Title2", "About u....");
}