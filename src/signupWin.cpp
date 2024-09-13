#include "signupWin.h"

Application::SignWindow::SignWindow(DBControll* db_controll) : wxFrame(nullptr, wxID_ANY, "Реєстрація", wxPoint(wxDisplay().GetGeometry().GetSize().x / 2 - 250, wxDisplay().GetGeometry().GetSize().y / 2 - 170), wxSize(500, 300), wxBORDER_NONE) {
  
}