

#ifndef AUTOSELECTOR_H_
#define AUTOSELECTOR_H_
#include "../main.h"
#include "User/Constants.h"
class AutoSelector {
public:
  AutoSelector(std::string autoName, int defaultAutoNumber);
  void registerAuto(std::string autoName,int autoNumber);

  // Only call after finishing registerAutos
  void listOptions();
  int getSelectedAuto();
  ~AutoSelector();
private:
  std::vector<std::string> autoNames;
  std::vector<int> autoNumbers;

  lv_obj_t * createDropdown(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
          int id);
  lv_obj_t* autoList;

};

#endif /* COMMAND_H_ */
