#ifndef AVIEW_H
#define AVIEW_H
#include <memory>

class iController;
class iView {
   public:
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual std::shared_ptr<iController> getController() = 0;
    virtual ~iView() noexcept = default;
};

#endif