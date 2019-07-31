

#ifndef AUTOSELECTOR_H_
#define AUTOSELECTOR_H_
#include "../main.h"
class AutoSelector {
public:
  AutoSelector(std::string autoName, int defaultAutoNumber);
  void registerAuto(std::string autoName,int autoNumber);
  static bool play;

  // Only call after finishing registerAutos
  void listOptions();
  int getSelectedAuto();
private:
  std::vector<std::string> autoNames;
  std::vector<int> autoNumbers;
  lv_obj_t* confirmButton;
  lv_obj_t* confirmButtonLabel;
  lv_obj_t * createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
      int id, const char * title);
  lv_obj_t * createDropdown(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
          int id, const char * title);
  static lv_res_t playButtonIsClicked(lv_obj_t * btn);
  lv_obj_t* autoList;

};

#endif /* COMMAND_H_ */
