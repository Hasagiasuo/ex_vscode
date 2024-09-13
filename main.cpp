#include <wx/wx.h>
#include "dbControll.h"
#include "loginWin.h"
#include "mainFrame.h"
#include "signupWin.h"

namespace Application {
  class MApplication : public wxApp {
  public:
    virtual bool OnInit();
  };

  bool MApplication::OnInit() {
    wxInitAllImageHandlers();
    DBControll* db_controller = new DBControll("dbname=trpz_db user=trpz password=ex1234");
    LoginWindow* login_window = new LoginWindow(db_controller);
    login_window->Show();

    return 1;
  }
};

wxIMPLEMENT_APP(Application::MApplication);