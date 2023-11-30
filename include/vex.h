#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <stdexcept>
#include <type_traits>

#include "v5.h"
#include "v5_vcs.h"


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)



namespace robot {

  inline const std::pair<uint8_t, uint8_t> gearRatio{3, 4}; 
  inline const double wheelGearCircumfrenceIN = 1; //replace with actual circumfrence

  template <typename T, typename = typename std::enable_if< (std::is_same< T, vex::motor>::value || std::is_same<T, vex::motor_group>::value) >::type >
  inline void spinFor(const T& motorToSpin, vex::distanceUnits dstType, double dst, vex::velocityUnits velType, double vel) {

    int dstIN = (dstType == vex::distanceUnits::cm) ? dst * 0.393701 : (dstType == vex::distanceUnits::mm) ? dst * 0.0393701 : dst;
    int rot = 360 * (dstIN / wheelGearCircumfrenceIN);
    motorToSpin.spinFor(vex::directionType::fwd, rot, vex::rotationUnits::deg, vel, velType);
    
  }

  template <typename T>
  inline void spinFor(const T& motorToSpin, vex::distanceUnits dstType, double dst, vex::velocityUnits velType, double vel) {
    throw std::runtime_error("invalid template param");
  }

};