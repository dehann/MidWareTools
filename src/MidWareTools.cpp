
#include <midwaretools/MidWareTools.h>

#include <lcm/lcm-cpp.hpp>
#include <sys/select.h>


#include <queue>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include <boost/thread/thread.hpp>
#include <iostream>



// These producers subscribe to LCM messages and add received messages to a
// synchronized queue to be consumed by a separate thread.



void LCMSubscriber::subscribe(boost::shared_ptr<lcm::LCM> lcmHandle)












