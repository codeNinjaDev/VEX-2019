#include "user/autoselector.h"
AutoSelector::AutoSelector(std::string autoName, int defaultAutoNumber) {
  this->autoNames.push_back(autoName);
  this->autoNumbers.push_back(defaultAutoNumber);
}

void AutoSelector::registerAuto(std::string autoName, int autoNumber) {
  autoNames.push_back(autoName);
  autoNumbers.push_back(autoNumber);
}

void AutoSelector::listOptions() {
  autoList = createDropdown(lv_scr_act(), 100, 0, 100, 100, 2);
  std::string options = "";
  for(int i = 0; i < autoNames.size(); i++) {
    if(i == autoNames.size() - 1) {
      options += autoNames[i];
    } else {
      options += autoNames[i] + "\n";
    }
  }
  lv_ddlist_set_options(autoList, options.c_str());
}


lv_obj_t * AutoSelector::createDropdown(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    int id)
{
    lv_obj_t * dd = lv_ddlist_create(parent, NULL);
    lv_obj_set_pos(dd, x, y);
    lv_obj_set_size(dd, width, height);
    lv_obj_set_free_num(dd, id);


    return dd;
}
int AutoSelector::getSelectedAuto() {
  return autoNumbers[lv_ddlist_get_selected(autoList)];
}

AutoSelector::~AutoSelector() {
  delete autoList;
}
