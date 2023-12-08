#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <type_traits>

#include "v5.h"
#include "v5_vcs.h"


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

template <typename T>
struct can_spin
  template <typename U>
  static auto test(U* x) -> decltype(x->spinFor(), std::true_type{});

  template <typename T>
  static auto test(...) -> std::false_type{};

  static constexpr bool value = decltype(test(std::declval<T*>()))::value;
};


namespace robot {

  inline const double wheelGearCircumfrenceIN = 1; //replace with actual circumfrence

  template <typename T, typename = typename std::enable_if< can_spin<T> >::type >
  inline void spinFor(const T& motorToSpin, vex::distanceUnits dstType, double dst, vex::velocityUnits velType, double vel std::pair<uint8_t, uint8_t> gearRatio = {1, 1}) {

    int dstIN = (dstType == vex::distanceUnits::cm) ? dst * 0.393701 : (dstType == vex::distanceUnits::mm) ? dst * 0.0393701 : dst;
    int rot = 360 * ((dstIN / wheelGearCircumfrenceIN) * gearRatio);
    motorToSpin.spinFor(vex::directionType::fwd, rot, vex::rotationUnits::deg, vel, velType);
    
  }


};
