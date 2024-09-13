
#ifndef SIGN_H
#define SIGN_H

#include <wx/wx.h>
#include <wx/display.h>
#include "dbControll.h"

namespace Application {
  class SignWindow : public wxFrame {
    DBControll* db_controller;
  public:
    SignWindow(DBControll* db_controll);
  };
}

#endif