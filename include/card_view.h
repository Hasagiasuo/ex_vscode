#ifndef CVIEW_H
#define CVIEW_H

#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/display.h>
#include <string>
#include <fstream>

#include "dbControll.h"
#include "edit_card.h"
#include "order.h"

namespace Application {
  class CardViewDialog : public wxDialog {
    wxBitmap* img;
    std::string uid;
    std::string owner_id;
    std::string u_name;
    DBControll* db_controller;
    wxStaticText* title;
    wxStaticText* desc;
    wxStaticText* note;
    wxBitmapButton* btn_close;
    wxButton* btn_buy;
    std::string path_img;
    std::string encrypt(std::string target);
    void draw_image(wxPaintEvent&);
    void close_callback(wxCommandEvent&);
    void delete_callback(wxCommandEvent&);
    void edit_dialog(wxCommandEvent&);
    void buy_callback(wxCommandEvent&);
  public:
    CardViewDialog(DBControll* db_controller, std::string owner_id, wxWindow* parent, std::string path, std::string title, std::string description, std::string note);
  }; 
}

#endif
