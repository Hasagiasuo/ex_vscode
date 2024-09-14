#ifndef MainFrame_H
#define MainFrame_H

#include <wx/wx.h>
#include <wx/bmpbuttn.h>
#include <wx/splitter.h>
#include <fstream>
#include <iostream>
#include "loginWin.h"
#include "signupWin.h"

namespace Application {
  enum MainFrameID {
    idPROFILE = 1,
    idLOGOUT = 2
  };
  class MainFrame : public wxFrame {
    // another data
    DBControll* db_controller;
    std::string username;
    // BURGER MENU
    wxMenu* burger_menu;
    // Tool bar
    wxStaticText* username_l;
    wxPanel* top_menu_bar;
    wxBitmap* img_for_profbtn;
    wxBitmapButton* btn_profile;
    wxBitmap* img_for_search;
    wxBitmapButton* btn_search;
    wxTextCtrl* search_entry;
    wxButton* btn_close;
    // Main
    wxPanel* main_menu;
    //
    void gen_widgets();
    void gen_top_bar();
    void gen_main_menu();
    void logout_profile(wxCommandEvent&);
    void close_window(wxCommandEvent&);
    void gen_burger(wxCommandEvent&);
    void search_open(wxCommandEvent&);
    void search_some(wxKeyEvent& ev);
  public:
    MainFrame(DBControll* db_controll, std::string name);
    ~MainFrame();
  };
}; 

#endif 