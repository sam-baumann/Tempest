#include "swapchain.h"

#include <Tempest/Frame>
#include <Tempest/Device>
#include <Tempest/Semaphore>

using namespace Tempest;

Swapchain::Swapchain(SystemApi::Window* w, AbstractGraphicsApi::Device& dev, AbstractGraphicsApi& api, uint8_t maxFramesInFlight)
  : api(&api), dev(&dev), hwnd(w), implMaxFramesInFlight(maxFramesInFlight) {
  reset();
  }

Swapchain::Swapchain(SystemApi::Window* w, Device& dev) {
  *this = dev.swapchain(w);
  }

Swapchain::~Swapchain() {
  delete impl.handler;
  }

Swapchain& Swapchain::operator = (Swapchain&& s) {
  impl = std::move(s.impl);

  std::swap(api,                  s.api);
  std::swap(dev,                  s.dev);
  std::swap(hwnd,                 s.hwnd);
  std::swap(framesCounter,        s.framesCounter);
  std::swap(imgId,                s.imgId);
  std::swap(framesIdMod,          s.framesIdMod);
  std::swap(implMaxFramesInFlight,s.implMaxFramesInFlight);

  return *this;
  }

uint32_t Swapchain::w() const {
  return impl.handler->w();
  }

uint32_t Swapchain::h() const {
  return impl.handler->h();
  }

void Swapchain::present(uint32_t img, const Semaphore& wait) {
  api->present(dev,impl.handler,img,wait.impl.handler);
  framesCounter++;
  framesIdMod=(framesIdMod+1)%maxFramesInFlight();
  }

void Swapchain::reset() {
  delete impl.handler;
  impl.handler = nullptr;
  impl = api->createSwapchain(hwnd,this->dev);
  }

uint32_t Swapchain::imageCount() const {
  return impl ? impl.handler->imageCount() : 0;
  }

uint8_t Swapchain::maxFramesInFlight() const {
  return implMaxFramesInFlight;
  }

uint8_t Swapchain::frameId() const {
  return framesIdMod;
  }

Frame Swapchain::frame(uint32_t id) {
  Frame fr(impl.handler->getImage(id),impl.handler,id);
  return fr;
  }

uint32_t Swapchain::nextImage(Semaphore& onReady) {
  imgId = impl.handler->nextImage(onReady.impl.handler);
  return imgId;
  }
