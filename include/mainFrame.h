#ifndef MainFrame_H
#define MainFrame_H

#include <wx/wx.h>
#include <wx/bmpbuttn.h>
#include <wx/splitter.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "loginWin.h"
#include "signupWin.h"
#include "card.h"

namespace Application {
  enum MainFrameID {
    idPROFILE = 1,
    idLOGOUT = 2
  };
  class MainFrame : public wxFrame {
    int card_x, card_y;
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
    wxBitmap* img_add;
    wxBitmapButton* btn_add;
    wxButton* btn_close;
    // Main
    wxPanel* main_menu;
    std::vector<Card*> cards;
    // Callbacks
    void gen_widgets();
    void gen_top_bar();
    void gen_main_menu();
    void add_callback(wxCommandEvent&);
    void logout_profile(wxCommandEvent&);
    void close_window(wxCommandEvent&);
    void gen_burger(wxCommandEvent&);
    void search_open(wxCommandEvent&);
    void search_some(wxKeyEvent& ev);
    void add_card(std::string path_to_img, std::string title, std::string description);
  public:
    MainFrame(DBControll* db_controll, std::string name);
    ~MainFrame();
  };
}; 

#endif 