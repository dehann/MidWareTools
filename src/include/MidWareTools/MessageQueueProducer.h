#ifndef __LCMProducers_h
#define __LCMProducers_h

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/thread/thread.hpp>

#include <MidWareTools/LCMSubscriber.h>
#include <MidWareTools/QueueTypes.h>
#include <MidWareTools/SynchronizedQueue.h>
#include <MidWareTools/CompTimeUtil.hpp>

// These producers subscribe to LCM messages and add received messages to a
// synchronized queue to be consumed by a separate thread.

//template <class T>
//class MsgProd {
//public:
//  MsgProd() {
//    std::cout << "Created one" << std::endl;
//  }
//};

template <class MessageType>
class MessageQueueProducer {
public:

  MessageQueueProducer() {
    ;
  }

  MessageQueueProducer(const MessageQueueProducer<MessageType>& other) {
    ;
  }


  void subscribe(boost::shared_ptr<lcm::LCM> lcmHandle, const std::string& channel, boost::function<void(MessageType&)> cbck_binding) {
    this->mChannel = channel;
    std::cout << "MessageQueueProducer::subscribe -- " << this->mChannel << std::endl;
    lcmHandle->subscribe(this->mChannel, &MessageQueueProducer::messageHandler, this);

    callback = cbck_binding;

    compTime.setName(this->mChannel);

    //example from http://stackoverflow.com/questions/3381829/how-do-i-implement-a-callback-in-c
    //	Target myTarget;
    //	callback=boost::bind(&Target::doSomething,&myTarget);
  }

  void stop() {
    this->mQueue.stopQueue();
  }

  SynchronizedQueue<MessageType>& messageQueue() {
    return this->mQueue;
  }

  void handleDeque() {
    MessageType buf;
    while (true) {
      this->mQueue.waitWhileEmpty();
#ifndef BLOCK_COMPTIME_UDP
      compTime.begin();
#endif
      this->mQueue.dequeue(buf);
      callback(buf);
#ifndef BLOCK_COMPTIME_UDP
      compTime.after();
#endif
    }
  }

  //  struct doStart {
  //	doStart( const MessageQueueProducer)
  //  };

  void start() {
    this->Thread = boost::shared_ptr<boost::thread>(
        new boost::thread(    boost::bind( &MessageQueueProducer::handleDeque, this )    ));
  }

  boost::shared_ptr<boost::thread> Thread;

protected:

  boost::function<void(MessageType&)> callback;

  void messageHandler(const lcm::ReceiveBuffer* rbuf, const std::string& channel, const MessageType* msg) {
    VarNotUsed(rbuf);
    VarNotUsed(channel);

    // enqueue a copy of the message
    mQueue.enqueue(*msg);
  }

  std::string mChannel;
  SynchronizedQueue<MessageType> mQueue;

  CompTimeUtil compTime;
};


#endif // __LCMProducers_h
