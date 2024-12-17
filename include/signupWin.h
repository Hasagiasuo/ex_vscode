
#ifndef SIGN_H
#define SIGN_H

#include <wx/wx.h>
#include <wx/display.h>
#include "dbControll.h"
#include "loginWin.h"

namespace Application {
  class SignWindow : public wxFrame {
    wxPanel* panel;
    wxBoxSizer* sizer;
    wxButton* btn_close;
    wxTextCtrl* name;
    wxTextCtrl* email;
    wxTextCtrl* password;
    wxTextCtrl* phone_number;
    wxButton* btn_commit;
    wxStaticText* error_message;
    DBControll* db_controller;
    void gen_widgets();
    void close_window(wxCommandEvent&);
    void registr_user(wxCommandEvent&);
  public:
    SignWindow(DBControll* db_controll);
  };
}

#endif
