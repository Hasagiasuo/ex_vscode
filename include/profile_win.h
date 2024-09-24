#ifndef PR_WIN_H
#define PR_WIN_H

#include <wx/wx.h>
#include <wx/display.h>
#include "dbControll.h"
#include "mainFrame.h"
#include "add_offer_win.h"

#define CENTER_DISPLAY_X wxDisplay().GetGeometry().GetSize().x / 2
#define CENTER_DISPLAY_Y wxDisplay().GetGeometry().GetSize().y / 2

namespace Application {
  class ProfileWindow : public wxFrame {
    std::vector<std::vector<std::string>> offers;
    int card_x, card_y;
    DBControll* db_controller;
    std::string name;
    std::string email;
    std::string password;

    wxStaticText* _name;
    wxStaticText* name_l;
    wxBitmapButton* btn_nedit;
    wxDialog* nedit_window;
    wxTextCtrl* nedit_entry;
    wxStaticText* error_message_nedit;
    void close_nedit_window(wxCommandEvent&);
    void nedit_callback(wxCommandEvent&);
    void _nedit_callback(wxCommandEvent&);

    wxStaticText* _email;
    wxStaticText* email_l;
    wxBitmapButton* btn_eedit;
    wxDialog* eedit_window;
    wxTextCtrl* eedit_entry;
    wxStaticText* error_message_eedit;
    void close_eedit_window(wxCommandEvent&);
    void eedit_callback(wxCommandEvent&);
    void _eedit_callback(wxCommandEvent&);


    wxStaticText* _password;
    wxStaticText* password_l;
    wxBitmapButton* btn_pedit;
    wxDialog* pedit_window;
    wxTextCtrl* pedit_entry;
    wxStaticText* error_message_pedit;
    void close_pedit_window(wxCommandEvent&);
    void pedit_callback(wxCommandEvent&);
    void _pedit_callback(wxCommandEvent&);
    std::string convert_password();

    wxButton* btn_add;
    void add_callback(wxCommandEvent&);

    void delete_callback(wxMouseEvent&);

    wxScrolledWindow* user_cards;
    wxFlexGridSizer* cards_sizer;

    wxButton* btn_close;
    void close_callback(wxCommandEvent&);

    void draw_cards();
    void update_cu();
  public:
    ProfileWindow(DBControll* db_controller, std::string name, std::string email, std::string password);
  };
}

#endif