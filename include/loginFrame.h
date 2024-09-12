#ifndef LOGINF_H
#define LOGINF_H

#include <wx/wx.h>
#include "dbControll.h"

class LoginFrame : public wxFrame {
  DBControll* db_controller;
  wxTextCtrl* login;
  wxTextCtrl* password;
  wxBitmap* bg_image;
  void draw_bg(wxPaintEvent&);
public:
  LoginFrame(DBControll* db_controller);
  ~LoginFrame();
};

#endif