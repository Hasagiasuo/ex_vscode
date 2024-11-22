#include "info.h"

Info::Info() : wxDialog(nullptr, wxID_ANY, "", wxPoint(wxDisplay().GetGeometry().width / 2 - 200, wxDisplay().GetGeometry().height / 2 - 200), wxSize(400, 400), wxBORDER_NONE) { 
  
  wxStaticText* project_name = new wxStaticText(this, wxID_ANY, "MTP: Military Trading Platform", wxPoint(0, 40), wxSize(400, 20), wxTE_CENTRE);
  project_name->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  wxStaticText* version = new wxStaticText(this, wxID_ANY, "version: 0.1", wxPoint(0, 80), wxSize(400, 20), wxTE_CENTRE);
  version->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  this->btn_close = new wxButton(this, wxID_ANY, "X", wxPoint(375, 5), wxSize(20, 20), wxBORDER_NONE);
  this->btn_close->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  this->btn_close->Bind(wxEVT_BUTTON, &Info::close_callback, this);
}

void Info::close_callback(wxCommandEvent &) {
  this->Close();
}