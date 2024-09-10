#include <wx/wx.h>
#include "mainFrame.h"

class Application : public wxApp {
public:
  virtual bool OnInit();
};

wxIMPLEMENT_APP(Application);

bool Application::OnInit() {
  MainFrame* main_fr = new MainFrame();
  main_fr->Show();
  return 1;
}