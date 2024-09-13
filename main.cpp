#include <wx/wx.h>
#include "dbControll.h"
#include "loginWin.h"
#include "mainFrame.h"
#include "signupWin.h"

namespace Application {
  MainFrame* main_window;
  LoginWindow* login_window;
  SignWindow* sign_window;

  enum mWindow {
    winLOGIN,
    winSIGN,
    winMAIN
  } current_window;
  
  class MApplication : public wxApp {
  public:
    virtual bool OnInit();
  };

  bool MApplication::OnInit() {
    wxInitAllImageHandlers();
    DBControll* db_controller = new DBControll("dbname=trpz_db user=trpz password=ex1234");
    LoginWindow* mf = new LoginWindow(db_controller);
    mf->Show();

    return 1;
  }
};

wxIMPLEMENT_APP(Application::MApplication);