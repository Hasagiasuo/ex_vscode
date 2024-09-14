#ifndef CARD_H
#define CARD_H

#include <wx/wx.h>
#include <string>

namespace Application {
  class Card : public wxPanel {
    wxBitmap* img;
    wxStaticText* description;
    wxStaticText* another_info;
  public:
    Card(std::string path_to_img, std::string description, std::string another_info, wxWindow* parent, wxPoint position, wxSize size);
    ~Card();
  };
};

#endif