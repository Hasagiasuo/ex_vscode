#ifndef MainFrame_H
#define MainFrame_H

#include <wx/wx.h>
#include <wx/bmpbuttn.h>
#include <wx/splitter.h>
#include <wx/font.h>
#include "loginWin.h"
#include "signupWin.h"

namespace Application {
  class MainFrame : public wxFrame {
    // another data
    DBControll* db_controller;
    std::string username;
    // Tool bar
    wxStaticText* username_l;
    wxPanel* top_menu_bar;
    wxBitmap* img_for_profbtn;
    wxBitmapButton* btn_profile;
    wxButton* btn_close;
    // Main
    wxPanel* main_menu;
    void gen_widgets();
    void gen_top_bar();
    void gen_main_menu();
    void close_window(wxCommandEvent&);
    void show_burger_menu(wxCommandEvent&);
  public:
    MainFrame(DBControll* db_controll, std::string name);
    ~MainFrame();
  };
}; 

#endif 