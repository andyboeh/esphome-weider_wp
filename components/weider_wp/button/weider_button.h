#pragma once

#include "esphome/core/component.h"
#include "esphome/components/button/button.h"
#include "esphome/components/weider_wp/WeiderWpComponent.h"

namespace esphome {
namespace weider_wp {

class WeiderButton : public button::Button, public Component {
 public:
  void dump_config() override;
  void set_weider_parent(WeiderWpComponent *parent) { this->parent_ = parent; }

 protected:
  void press_action() override;

  WeiderWpComponent *parent_{nullptr};
};

}  // namespace weider_wp
}  // namespace esphome
