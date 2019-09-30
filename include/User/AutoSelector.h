

#ifndef AUTOSELECTOR_H_
#define AUTOSELECTOR_H_
#include "../main.h"
#include "User/Constants.h"
/**
 * Class that handles user input for autonomous routine selection
 */
class AutoSelector {
public:
  /**
   * Constructor and sets default values for autonomous
   * @param autoName          Default autonomous routine name
   * @param defaultAutoNumber Default autonomous routine number
   */
  AutoSelector(std::string autoName, int defaultAutoNumber);
  /**
   * Function to append a new autonomous routine to the screen
   * @param autoName   Name of autonomous routine
   * @param autoNumber Number of autonomous routine
   */
  void registerAuto(std::string autoName,int autoNumber);

  // Only call after finishing registerAutos
  /**
   * Takes the array of autonomous routines and creates a dropdown on the screen.
   * Only call this function after registering all autonmous routines.
   */
  void listOptions();
  /**
   * Function that gets the selected autonomous routine from the dropdown
   * @return The autonomous number of the selected auto routine
   */
  int getSelectedAuto();
  ~AutoSelector();
private:
  // Array of auto routine names
  std::vector<std::string> autoNames;
  // Array of auto routine numbers
  std::vector<int> autoNumbers;
  // Function that creates a dropdown ui element
  lv_obj_t * createDropdown(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
          int id);
  // Autonomous Dropdown ui element
  lv_obj_t* autoList;

};

#endif /* COMMAND_H_ */
