#ifndef INFO_H
#define INFO_H

#include <wx/wx.h>
#include <wx/display.h>

class Info : public wxDialog {
  wxButton* btn_close;
  void close_callback(wxCommandEvent&);
public:
  Info();
};

#endif