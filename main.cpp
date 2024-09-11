#include <wx/wx.h>
#include "loginFrame.h"

class Application : public wxApp {
public:
  virtual bool OnInit();
};

wxIMPLEMENT_APP(Application);

bool Application::OnInit() {
  wxApp::SetNativeTheme("dark");
  wxInitAllImageHandlers();
  LoginFrame* login_fr = new LoginFrame();
  login_fr->Show();
  return 1;
}