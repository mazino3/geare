#ifndef _INCLUDE__GEARE__BASE__CLOCK_
#define _INCLUDE__GEARE__BASE__CLOCK_

#include "../core/System.hpp"
#include "../utils/Singleton.hpp"
#include "glfw.hpp"

namespace geare::base {

struct Clock : utils::Singleton<Clock> {
  double delta_time;
  double fixed_timestep;
  double global_time;
  unsigned long frame_count;

  double frame_timer;
  unsigned long fps;
};

struct ClockSystem : core::System {
  ClockSystem() {
    contract.call_only_on_main = false;
    contract.global_priority = INT32_MAX;
  }

  virtual void tick() override {
    auto &clock = Clock::instance();
    double current_tick_time = glfwGetTime();
    clock.global_time = current_tick_time;
    clock.delta_time = current_tick_time - last_tick_time;
    last_tick_time = current_tick_time;

    if (clock.global_time - clock.frame_timer > 1) {
      clock.fps = clock.frame_count;
      clock.frame_count = 0;
      clock.frame_timer = clock.global_time;
      std::cout << clock.fps << std::endl;
    }
  }

  double last_tick_time = 0;
};

} // namespace geare::base

#endif
