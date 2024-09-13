#include "mainFrame.h"

Application::MainFrame::MainFrame(DBControll* db_controll) : wxFrame(nullptr, wxID_ANY, "Index", wxPoint(wxDisplay().GetGeometry().GetSize().x / 2 - 300, wxDisplay().GetGeometry().GetSize().y / 2 - 420), wxSize(600, 800), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {
  this->db_controller = db_controll;
}
