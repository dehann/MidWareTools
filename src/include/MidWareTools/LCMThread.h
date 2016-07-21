#ifndef __LCMThread_h
#define __LCMThread_h

//#include "ThreadLoop.h"

#include <lcm/lcm-cpp.hpp>
#include <sys/select.h>


//----------------------------------------------------------------------------
class LCMThread {
public:

  LCMThread();

  //boost::shared_ptr<lcm::LCM> lcmHandle();

protected:

  bool waitForLCM(double timeout);
  void handleLoopWithSelect();
  void handleLoop();
  void initLCM();

  bool UseSelect;
  double SelectTimeoutInSeconds;

  boost::shared_ptr<lcm::LCM> LCMHandle;
};


#endif // __LCMThread_h
