#pragma once

#include <Tempest/AbstractGraphicsApi>
#include "../utility/dptr.h"

namespace Tempest {

class Device;
class CommandBuffer;
class FrameBuffer;
class Texture2d;

class FrameBufferLayout final {
  public:
    bool operator == (const FrameBufferLayout& fbo) const;
    bool operator != (const FrameBufferLayout& fbo) const;

  private:
    FrameBufferLayout()=default;
    FrameBufferLayout(Detail::DSharedPtr<AbstractGraphicsApi::FboLayout*>&& f);

    Detail::DSharedPtr<AbstractGraphicsApi::FboLayout*> impl;

  friend class Tempest::Device;
  friend class Tempest::FrameBuffer;
  friend class Tempest::CommandBuffer;
  };

class FrameBuffer final {
  public:
    FrameBuffer()=default;
    FrameBuffer(FrameBuffer&& f);
    ~FrameBuffer();
    FrameBuffer& operator = (FrameBuffer&& other);

    uint32_t w() const { return mw; }
    uint32_t h() const { return mh; }

    auto     layout() const -> const FrameBufferLayout&;

  private:
    FrameBuffer(Tempest::Device& dev,
                Detail::DSharedPtr<AbstractGraphicsApi::Fbo*>&& f,
                FrameBufferLayout&& lay,uint32_t w,uint32_t h);

    Tempest::Device*                              dev=nullptr;
    Detail::DSharedPtr<AbstractGraphicsApi::Fbo*> impl;
    FrameBufferLayout                             lay;
    uint32_t                                      mw=0, mh=0;

  friend class Tempest::Device;
  friend class Tempest::Encoder<Tempest::CommandBuffer>;
  };
}
