#ifndef LOGINW_H
#define LOGINW_H

#include <wx/wx.h>
#include <wx/display.h>
#include "dbControll.h"
#include "mainFrame.h"
#include "signupWin.h"

namespace Application {
  class LoginWindow : public wxFrame {
    wxPanel* panel;
    wxBoxSizer* sizer;
    wxButton* btn_close;
    wxTextCtrl* email;
    wxTextCtrl* password;
    wxStaticText* email_l;
    wxStaticText* password_l;
    wxButton* btn_commit;
    wxStaticText* message_for_signup;
    wxButton* btn_signup;
    wxStaticText* error_message;
    DBControll* db_controller;
    void gen_widgets();
    void close_window(wxCommandEvent&);
    void go_to_signup(wxCommandEvent&);
    void check_user_in_system(wxCommandEvent&);
  public:
    LoginWindow() = delete;
    LoginWindow(DBControll* db_controll);
    ~LoginWindow();
  };
}

#endif