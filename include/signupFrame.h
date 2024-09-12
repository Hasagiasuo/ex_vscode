#ifndef LOGINF_H
#define LOGINF_H

#include <wx/wx.h>
#include "dbControll.h"

class SignupFrame : public wxFrame {
  DBControll* db_controller;
  wxTextCtrl* login;
  wxTextCtrl* password;
  wxTextCtrl* name;
  wxBitmap* bg_image;
  void draw_bg(wxPaintEvent&);
  void signup(wxCommandEvent&);
public:
  SignupFrame(DBControll* db_controller);
  ~SignupFrame();
};

#endif