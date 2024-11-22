#ifndef CARD_H
#define CARD_H

#include <wx/wx.h>
#include <string>
#include <iostream>
#include <fstream>

#include "card_view.h"
#include "dbControll.h"

namespace Application {
  class Card : public wxPanel {
    DBControll* db_controller;
    std::string owner_id;
    wxBitmap* img;
    std::string path_img;
    std::string note;
    wxStaticText* card_title;
    wxStaticText* card_description;
    CardViewDialog* dialog;
    void draw_image(wxPaintEvent&);
    void press_callback(wxMouseEvent&);
  public:
    Card(DBControll* db_controller, std::string owner_id, std::string path_to_img, std::string c_title, std::string c_description, std::string hidden_note, wxWindow* parent, wxPoint position);
  };
};

#endif
