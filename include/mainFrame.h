#ifndef MainFrame_H
#define MainFrame_H

#include <wx/wx.h>
#include <wx/bmpbuttn.h>
#include <wx/splitter.h>
#include "loginWin.h"
#include "signupWin.h"

namespace Application {
  class MainFrame : public wxFrame {
    // User menu 
    wxWindow* user_window;
    wxSplitterWindow* user_menu_split;
    // another data
    wxWindow* main_window;
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
    void gen_user_menu();
    void gen_main_menu();
    void close_window(wxCommandEvent&);
  public:
    MainFrame(DBControll* db_controll, std::string name);
    ~MainFrame();
  };
}; 

#endif 