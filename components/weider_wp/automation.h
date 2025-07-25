#pragma once

#include "esphome/core/automation.h"
#include "WeiderWpComponent.h"

namespace esphome {
namespace weider_wp {

template<typename... Ts> class SetCodeAction : public Action<Ts...> {
  public:
    explicit SetCodeAction(WeiderWpComponent *parent) : parent_(parent) {}
    
    TEMPLATABLE_VALUE(int, code)
    TEMPLATABLE_VALUE(int, value)
    
    void play(Ts... x) override {
      this->parent_->set_code(this->code_.value(x...), this->value_.value(x...));
    }

  protected:
    WeiderWpComponent *parent_;
};

} // weider_wp
} // esphome
