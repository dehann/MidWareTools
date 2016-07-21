#ifndef __LCMSubscriber_h
#define __LCMSubscriber_h

#include <MidWareTools/Macros.h>
#include <MidWareTools/SharedPtrMacros.h>

#include <lcm/lcm-cpp.hpp>

//----------------------------------------------------------------------------
class LCMSubscriber
{
public:


  virtual void subscribe(boost::shared_ptr<lcm::LCM> lcmHandle) {
	VarNotUsed(lcmHandle);
  }

};

#endif // __LCMSubscriber_h
