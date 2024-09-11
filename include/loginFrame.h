#ifndef LOGINF_H
#define LOGINF_H

#include <wx/wx.h>

class LoginFrame : public wxFrame {
  wxTextCtrl* login;
  wxTextCtrl* password;
  wxBitmap* bg_image;
  void draw_bg(wxPaintEvent&);
public:
  LoginFrame();
  ~LoginFrame();
};

#endif