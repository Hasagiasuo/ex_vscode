#ifndef ORDER_H
#define ORDER_H

#include <wx/wx.h>
#include <wx/display.h>
#include <wx/radiobut.h>

namespace Application {
  class Order : public wxDialog {
    wxRadioBox* delivery;
    wxTextCtrl* address_entry;
    wxRadioBox* payment;
    wxTextCtrl* customer;
    wxButton* btn_commit;
    wxButton* btn_close;
    void close_callback(wxCommandEvent&);
    void commit_callback(wxCommandEvent&);
  public:
    ~Order(); 
    Order();
  };
}
#endif
