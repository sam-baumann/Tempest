#pragma once

#include <Tempest/AbstractGraphicsApi>
#include <d3d12.h>
#include "comptr.h"

namespace Tempest {
namespace Detail {

class DxDevice;

class DxBuffer : public AbstractGraphicsApi::Buffer {
  public:
    DxBuffer() = delete;
    DxBuffer(DxDevice* dev, ComPtr<ID3D12Resource>&& b, UINT sizeInBytes);
    DxBuffer(DxBuffer&& other);

    void  update(const void* data,size_t off,size_t count,size_t sz,size_t alignedSz) override;
    void  read  (void* data, size_t off, size_t sz);

    void  uploadS3TC(const uint8_t* d, uint32_t w, uint32_t h, uint32_t mip, UINT blockSize);

    DxDevice*              dev = nullptr;
    ComPtr<ID3D12Resource> impl;
    UINT                   sizeInBytes=0;
  };

}
}

