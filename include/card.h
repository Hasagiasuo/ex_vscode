#ifndef CARD_H
#define CARD_H

#include <wx/wx.h>
#include <string>
#include <iostream>
#include <fstream>

#include "card_view.h"
#include "dbControll.h"
#include <wx/mstream.h>

namespace Application {
  class Card : public wxPanel {
    DBControll* db_controller;
    Advertisment ads;
    wxStaticText* card_title;
    wxStaticText* card_description;
    CardViewDialog* dialog;
    void draw_image(wxPaintEvent&);
    void press_callback(wxMouseEvent&);
  public:
    Card(DBControll* db_controller, Advertisment& ads, wxWindow* parent, wxPoint position);
  };
};

#endif
