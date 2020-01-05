#pragma once

#include <vulkan/vulkan.hpp>

namespace Tempest {
namespace Detail {

class VulkanApi {
  public:
    VulkanApi(bool enableValidationLayers=true);
    ~VulkanApi();

    const bool       validation;
    VkInstance       instance;

  private:
    const std::initializer_list<const char*> checkValidationLayerSupport();
    bool layerSupport(const std::vector<VkLayerProperties>& sup,const std::initializer_list<const char*> dest);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugReportCallback(
        VkDebugReportFlagsEXT       flags,
        VkDebugReportObjectTypeEXT  objectType,
        uint64_t                    object,
        size_t                      location,
        int32_t                     messageCode,
        const char*                 pLayerPrefix,
        const char*                 pMessage,
        void*                       pUserData);

    VkDebugReportCallbackEXT            callback;
    PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT = nullptr;
  };

}}
