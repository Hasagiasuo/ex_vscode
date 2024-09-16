#ifndef CVIEW_H
#define CVIEW_H

#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/display.h>
#include <fstream>
#include <iostream>
#include <string>

namespace Application {
  class CardViewDialog : public wxDialog {
    wxBitmap* img;
    wxStaticText* title;
    wxStaticText* desc;
    wxStaticText* note;
    wxButton* btn_close;
    std::string path_img;
    void draw_image(wxPaintEvent&);
    void close_callback(wxCommandEvent&);
  public:
    CardViewDialog(wxWindow* parent, std::string path, std::string title, std::string description, std::string note);
    ~CardViewDialog();
  }; 
}

#endif