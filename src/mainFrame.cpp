#include "mainFrame.h"

Application::MainFrame::~MainFrame() {
  delete this->username_l;
  delete this->img_for_profbtn;
  delete this->btn_profile;
  delete this->btn_close;
  delete this->top_menu_bar;
  delete this->main_menu;
}

Application::MainFrame::MainFrame(DBControll* db_controll, std::string name) : wxFrame(nullptr, wxID_ANY, "Index", wxPoint(wxDisplay().GetGeometry().GetSize().x / 2 - 300, wxDisplay().GetGeometry().GetSize().y / 2 - 420), wxSize(800, 800), wxBORDER_NONE) {
  this->db_controller = db_controll; 
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
  this->btn_profile = new wxBitmapButton(this, wxID_ANY, *this->img_for_profbtn, wxPoint(5, 7), wxSize(20, 20), wxBORDER_NONE);
  this->btn_profile->Bind(wxEVT_BUTTON, &MainFrame::show_burger_menu, this);
  this->burger_menu = new wxMenu;
  // this->burger_menu->Append("")

  this->username_l = new wxStaticText(this, wxID_ANY, this->username, wxPoint(350, 5), wxSize(100, 20), wxTE_CENTRE);
  this->username_l->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  this->btn_close = new wxButton(this, wxID_CLOSE, "X", wxPoint(775, 5), wxSize(25, 20), wxBORDER_NONE);
  this->btn_close->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->btn_close->Bind(wxEVT_BUTTON, &MainFrame::close_window, this);
}

void Application::MainFrame::show_burger_menu(wxCommandEvent&) {

}

void Application::MainFrame::gen_main_menu() {
  this->main_menu = new wxPanel(this, wxID_ANY, wxPoint(0, 30), wxSize(800, 770), wxBORDER_SUNKEN);
}

void Application::MainFrame::close_window(wxCommandEvent&) {
  this->Close();
  this->~MainFrame();
}