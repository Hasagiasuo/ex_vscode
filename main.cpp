#include <wx/wx.h>
#include "dbControll.h"
#include "loginWin.h"
#include "mainFrame.h"
#include "signupWin.h"

#include "add_offer_win.h"

#include <fstream>
#include <sstream>

namespace Application {
  class MApplication : public wxApp {
    std::vector<std::string> user_data;
    void read_user_data();
  public:
    virtual bool OnInit();
  };

  bool MApplication::OnInit() {
    wxInitAllImageHandlers();
    read_user_data();
    DBControll* db_controller = new DBControll("host=localhost dbname=trpz_db user=trpz password=ex1234");
    // OfferWinAdd* ow = new OfferWinAdd(db_controller, this->user_data[0], this->user_data[1], this->user_data[2]);
    // ow->Show();
    if(this->user_data.empty()) {
      LoginWindow* login_window = new LoginWindow(db_controller);
      login_window->Show();
    } else {
      MainFrame* mf = new MainFrame(db_controller, this->user_data[0], this->user_data[1], this->user_data[2]);
      mf->Show();
    }
    return 1;
  }

  void MApplication::read_user_data() {
    std::ifstream file("../data/cu");
    std::stringstream ss;
    ss << file.rdbuf();
    std::string data_from_file = ss.str();
    std::string tmp;
    for(char ch : data_from_file) {
      if(ch == '|') {
        this->user_data.push_back(tmp);
        tmp = "";
      } else {
        tmp.push_back(ch);
      }
    }
    file.close();
  }
};

wxIMPLEMENT_APP(Application::MApplication);