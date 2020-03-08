#pragma once

/*
#include <string>
#include "tbb/concurrent_queue.h"

template<class MessageT>
class ConcurrentQueuePublisher {
public:
  // TODO use another container since if we use shared ptr it will be deleted at try_pop.
  using CElement = MessageT*;
  using Container = tbb::concurrent_queue<CElement>;

  ConcurrentQueuePublisher(Container& container) :
    _container(container) {    
  }

  void publish(CElement& message) {
    _container.push(message);
  }

private:
  Container& _container;
};
*/
