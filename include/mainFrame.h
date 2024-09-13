#ifndef MainFrame_H
#define MainFrame_H

#include <wx/wx.h>
#include "loginWin.h"
#include "signupWin.h"

namespace Application {
  class MainFrame : public wxFrame {
    DBControll* db_controller;
  public:
    MainFrame(DBControll* db_controll);
  };
};

#endif 