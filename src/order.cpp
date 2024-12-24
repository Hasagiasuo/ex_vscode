#include "order.h"

namespace Application {
  Order::~Order() {}
  Order::Order(Advertisment& ads, DBControll* db_controller) : wxDialog(nullptr, wxID_ANY, "", wxPoint(wxDisplay().GetGeometry().width / 2 - 300, wxDisplay().GetGeometry().height / 2 - 225), wxSize(600, 450), wxBORDER_NONE) {
    this->ads = ads;
    this->db_controller = db_controller;
    this->SetBackgroundColour(wxColor(38, 42, 48));
    wxStaticText* info = new wxStaticText(this, wxID_ANY, "Заповніть форму замолення", wxPoint(0, 5), wxSize(600, 20), wxTE_CENTRE);
    info->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxStaticText* customer_info = new wxStaticText(this, wxID_ANY, "ПІБ", wxPoint(15, 40), wxSize(50, 20));
    customer_info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    this->customer = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(30, 60), wxSize(300, 20), wxBORDER_NONE);
    this->customer->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxStaticText* delivery_info = new wxStaticText(this, wxID_ANY, "Оберіть спосіб доставки", wxPoint(15, 90), wxSize(300, 20));
    delivery_info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    wxArrayString* delivery_choise = new wxArrayString;
    delivery_choise->Add("Нова пошта");
    delivery_choise->Add("Укр пошта");
    delivery_choise->Add("Meest");
    this->delivery = new wxRadioBox(this, wxID_ANY, wxEmptyString, wxPoint(30, 110), wxSize(130, 70), *delivery_choise, 1);
    this->delivery->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxStaticText* address_info = new wxStaticText(this, wxID_ANY, "Введіть адресу доставки", wxPoint(15, 190), wxSize(300, 20));
    address_info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    this->address_entry = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(30, 210), wxSize(300, 20), wxBORDER_NONE);
    this->address_entry->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxStaticText* payment_info = new wxStaticText(this, wxID_ANY, "Оберіть спосіб оплати", wxPoint(15, 240), wxSize(300, 20));
    payment_info->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    wxArrayString* payment_choise = new wxArrayString;
    payment_choise->Add("Наложним платижем при отриманні");
    payment_choise->Add("Карткою при отриманні");
    this->payment = new wxRadioBox(this, wxID_ANY, "", wxPoint(30, 260), wxSize(280, 50), *payment_choise, 1);

    this->btn_commit = new wxButton(this, wxID_ANY, "Замовити", wxPoint(10, 410), wxSize(580, 20));
    this->btn_commit->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    this->btn_commit->Bind(wxEVT_BUTTON, &Order::commit_callback, this);

    this->btn_close = new wxButton(this, wxID_CLOSE, "X", wxPoint(570, 5), wxSize(25, 20), wxBORDER_NONE);
    this->btn_close->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    this->btn_close->Bind(wxEVT_BUTTON, &Order::close_callback, this);
  }   

  void Order::commit_callback(wxCommandEvent&) {
    if(this->customer->GetValue() != "" || this->address_entry->GetValue() != "") {
      wxMessageBox("Ваше замовлення додано! Очікуйте на звінок оператора!", "Успішно", wxICON_NONE);
      this->ads.status_id = 1;
      this->db_controller->udpate_state_by_title(this->ads.title, this->ads.status_id);
      this->Close();
    } else {
      wxMessageBox("Будь ласка заповніть форму замовлення", "Помилка заповнення", wxICON_NONE);
    }
  }
 
  void Order::close_callback(wxCommandEvent&) {
    this->Close();
  }
}
