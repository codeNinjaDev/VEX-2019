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
  confirmButton = createBtn(lv_scr_act(), 50, 50, 50, 50, 711, "Confirm");
  autoList = createDropdown(lv_scr_act(), 100, 200, 10, 50, 712, "Autos:");
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

int AutoSelector::getSelectedAuto() {
  return autoNumbers[lv_ddlist_get_selected(autoList)];
}



lv_res_t AutoSelector::playButtonIsClicked(lv_obj_t * btn) {
  return LV_RES_OK;

}
lv_obj_t * AutoSelector::createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    int id, const char * title)
{
    lv_obj_t * btn = lv_btn_create(parent, NULL);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_size(btn, width, height);
    lv_obj_set_free_num(btn, id);
    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label, title);
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);
    lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, AutoSelector::playButtonIsClicked);
    return btn;
}
lv_obj_t * AutoSelector::createDropdown(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    int id, const char * title)
{
    lv_obj_t * dd = lv_ddlist_create(parent, NULL);
    lv_obj_set_pos(dd, x, y);
    lv_obj_set_size(dd, width, height);
    lv_obj_set_free_num(dd, id);

    lv_obj_t * label = lv_label_create(dd, NULL);
    lv_label_set_text(label, title);
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

    return dd;
}
