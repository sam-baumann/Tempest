#pragma once

#include <Tempest/AbstractGraphicsApi>
#include <Tempest/UniformsLayout>

#include "vulkan_sdk.h"
#include <mutex>
#include <list>
#include <vector>

#include "utility/spinlock.h"

namespace Tempest {

class UniformsLayout;

namespace Detail {

class VDescriptorArray;
class VDevice;
class VShader;

class VUniformsLay : public AbstractGraphicsApi::UniformsLay {
  public:
    VUniformsLay(VDevice& dev, const std::vector<UniformsLayout::Binding>& comp);
    VUniformsLay(VDevice& dev, const std::vector<UniformsLayout::Binding>* sh[], size_t cnt);
    ~VUniformsLay();

    using Binding = UniformsLayout::Binding;

    VkDevice                      dev =nullptr;
    VkDescriptorSetLayout         impl=VK_NULL_HANDLE;
    std::vector<Binding>          lay;
    UniformsLayout::PushBlock     pb;
    bool                          hasSSBO = false;

  private:
    enum {
      POOL_SIZE=512
      };

    struct Pool {
      VkDescriptorPool impl      = VK_NULL_HANDLE;
      uint16_t         freeCount = POOL_SIZE;
      };

    Detail::SpinLock sync;
    std::list<Pool>  pool;

    void implCreate(VkDescriptorSetLayoutBinding *bind);
    void adjustSsboBindings();

  friend class VDescriptorArray;
  };

}
}
