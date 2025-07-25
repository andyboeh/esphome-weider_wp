#include "weider_button.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace weider_wp {

static const char *const TAG = "weider_wp.button";

void WeiderButton::dump_config() { LOG_BUTTON("", "WeiderWP Button", this); }
void WeiderButton::press_action() {
  ESP_LOGI(TAG, "Triggering action...");
  if(this->parent_) {
    if(this->type_ == "reset") {
      this->parent_->reset();
    } else if(this->type_ == "get_codes") {
      this->parent_->get_codes();
    }
  }
}

}  // namespace weider_wp
}  // namespace esphome
