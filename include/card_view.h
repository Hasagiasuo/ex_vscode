#ifndef CVIEW_H
#define CVIEW_H

#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/display.h>
#include <string>
#include <fstream>

#include <wx/mstream.h>
#include "dbControll.h"
#include "edit_card.h"
#include "order.h"

namespace Application {
  class CardViewDialog : public wxDialog {
    std::string username;
    std::string cid;
    Advertisment ads;
    DBControll* db_controller;
    wxStaticText* title;
    wxStaticText* desc;
    wxStaticText* category;
    wxStaticText* price;
    wxStaticText* amount;
    wxBitmapButton* btn_close;
    wxButton* btn_buy;
    std::string encrypt(std::string target);
    void draw_image(wxPaintEvent&);
    void close_callback(wxCommandEvent&);
    void delete_callback(wxCommandEvent&);
    void edit_dialog(wxCommandEvent&);
    void buy_callback(wxCommandEvent&);
  public:
    CardViewDialog(DBControll* db_controller, wxWindow* parent, Advertisment& ads);
  }; 
}

#endif
