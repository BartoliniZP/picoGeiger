#ifndef ICONTROLLER_H
#define ICONTROLLER_H

class iController {
   public:
    virtual void onButton(unsigned buttonId) = 0;
    virtual ~iController() noexcept = default;
};

#endif