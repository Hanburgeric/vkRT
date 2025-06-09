#ifndef PLATFORM_H
#define PLATFORM_H

namespace vkrt {
namespace platform {

class Platform {
public:
  virtual ~Platform() = default;

  virtual bool Initialize() = 0;
  virtual void Shutdown() = 0;
};

} // namespace platform
} // namespace vkrt

#endif // PLATFORM_H
