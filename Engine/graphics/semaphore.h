#pragma once

#include <Tempest/AbstractGraphicsApi>
#include "../utility/dptr.h"

namespace Tempest {

class Device;
class Swapchain;

class Semaphore final {
  public:
    Semaphore(Semaphore&& f)=default;
    ~Semaphore();
    Semaphore& operator = (Semaphore&& other)=default;

  private:
    Semaphore(Tempest::Device& dev,AbstractGraphicsApi::Semaphore* f);

    Tempest::Device*                              dev=nullptr;
    Detail::DPtr<AbstractGraphicsApi::Semaphore*> impl;

  friend class Tempest::Device;
  friend class Tempest::Swapchain;
  };

}
