#ifndef OFFER_H
#define OFFER_H

#include <wx/wx.h>
#include <wx/display.h>
#include <wx/filepicker.h>
#include <wx/richtext/richtextctrl.h>
#include "dbControll.h"
#include "profile_win.h"

class OfferWinAdd : public wxFrame {
  std::string name;
  std::string email;
  std::string password;

  DBControll* db_controller;  
  wxFilePickerCtrl* path_img;
  wxStaticText* under_text;
  wxBitmap* choice_img;
  wxTextCtrl* title;
  wxTextCtrl* description;
  wxRichTextCtrl* note;

  void draw_img(wxPaintEvent& ev);
  void file_picked(wxFileDirPickerEvent&);
  void btn_callback(wxCommandEvent&);
  void close_callback(wxCommandEvent&);
public:
  OfferWinAdd(DBControll* db_controller, std::string name, std::string email, std::string password);
  ~OfferWinAdd();
};

#endif