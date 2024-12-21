#ifndef EDIT_CARD
#define EDIT_CARD

#include <wx/wx.h>
#include <wx/display.h>
#include <wx/filepicker.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/spinctrl.h>
#include "dbControll.h"
#include <fstream>
#include <wx/mstream.h>

#define C_X wxDisplay().GetGeometry().GetSize().x / 2
#define C_Y wxDisplay().GetGeometry().GetSize().y / 2

namespace Application {
  class EditCardDialog : public wxDialog {
    int uid;
    int status_id;
    Advertisment* card_data;
    std::string true_title;
    DBControll* db_controller;
    wxTextCtrl* title_e;
    wxRichTextCtrl* desc_e;
    wxSpinCtrlDouble* price_e;
    wxSpinCtrlDouble* amount_e;
    wxFilePickerCtrl* file_path;
    wxChoice* category_e;
    wxBitmap* choice_img;
    void file_picked(wxFileDirPickerEvent&);
    void close_handle(wxCommandEvent&);
    void commit_handle(wxCommandEvent&);
    void draw_image(wxPaintEvent& ev);
  public:
    EditCardDialog(DBControll* db_controller, wxWindow* parent, std::string owner_id, std::string card_title);
  };
}

#endif 
