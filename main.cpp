#include <wx/wx.h>
#include "signupFrame.h"
#include "dbControll.h"

class Application : public wxApp {
public:
  virtual bool OnInit();
};

wxIMPLEMENT_APP(Application);

bool Application::OnInit() {
  wxInitAllImageHandlers();
  DBControll* db_controller = new DBControll("dbname=trpz_db user=trpz password=ex1234");
  SignupFrame* login_fr = new SignupFrame(db_controller);
  login_fr->Show();
  return 1;
}