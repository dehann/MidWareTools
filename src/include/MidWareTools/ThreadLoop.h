#ifndef __ThreadLoop_h
#define __ThreadLoop_h

#include <MidWareTools/SharedPtrMacros.h>
#include <boost/thread/thread.hpp>
#include <iostream>



//----------------------------------------------------------------------------
class ThreadLoop {
public:

  ThreadLoop();

  void start();

  void stop();

protected:

  virtual void run() = 0;

  bool ShouldStop;
  boost::shared_ptr<boost::thread> Thread;
};

#endif // __ThreadLoop_h
