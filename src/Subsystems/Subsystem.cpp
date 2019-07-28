#include "user/subsystem.h"

std::unique_ptr<Subsystem> Subsystem::toPointer(Subsystem *subsystem) {
  std::unique_ptr<Subsystem> subsystemPointer(subsystem);
  return subsystemPointer;
}
