#ifndef SETTING_H
#define SETTING_H
#include <string>
class setting {
   public:
    virtual void changeValue() = 0;
    virtual std::string settingName() = 0;
    virtual std::string settingValue() = 0;
    virtual ~setting() noexcept = default;
};

#endif