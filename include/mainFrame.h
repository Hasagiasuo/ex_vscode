#ifndef MainFrame_H
#define MainFrame_H

#include <wx/wx.h>
#include <wx/bmpbuttn.h>
#include <wx/splitter.h>
#include <wx/scrolwin.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "profile_win.h"
#include "loginWin.h"
#include "signupWin.h"
#include "card.h"
#include "info.h"

namespace Application {
  enum MainFrameID {
    idPROFILE = 1,
    idLOGOUT = 2,
    idINFO = 3
  };
  class MainFrame : public wxFrame {
    int card_x, card_y;

    wxDialog* dialog_s;
    wxScrolledWindow* scrl_win_dialog;
    wxFlexGridSizer*  sizer_dialog;
    void close_dialog_callback(wxCommandEvent&);

    // another data
    DBControll* db_controller;
    std::string username;
    std::string user_email;
    std::string user_password;
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
    wxScrolledWindow* main_menu;
    wxFlexGridSizer* sizer_main;
    std::vector<Card*> cards;
    // Callbacks
    void draw_offers();
    void gen_widgets();
    void gen_top_bar();
    void gen_main_menu();
    void info_callback(wxCommandEvent&);
    void logout_profile(wxCommandEvent&);
    void profile_callback(wxCommandEvent&);
    void close_window(wxCommandEvent&);
    void gen_burger(wxCommandEvent&);
    void search_open(wxCommandEvent&);
    void search_some(wxKeyEvent& ev);
    void search_callback();
    void add_card(std::string owner_id, std::string path_to_img, std::string title, std::string description, std::string note);
  public:
    MainFrame(DBControll* db_controll, std::string name, std::string email, std::string password);
    void set_title(std::string new_val);
  };
}; 

#endif 
