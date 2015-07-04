#ifndef _BATTLECREEK_NODE_HPP_
#define _BATTLECREEK_NODE_HPP_

#include <daylite/node.hpp>
#include <cstdint>
#include <array>

namespace battlecreek
{
  struct motor_state
  {
    enum _mode {
      mode_off,
      mode_power,
      mode_velocity,
      mode_position
    } mode;
    
    bool open_loop;
    uint64_t position;
    uint32_t velocity;
    uint16_t power;
    
    
    motor_state(const _mode m, bool open_loop, const uint64_t position,
      const uint32_t velocity, const uint16_t power);
      
    static motor_state off_motor_state();
    static motor_state power_motor_state(const uint16_t power);
    static motor_state velocity_motor_state(const uint32_t velocity, const bool open_loop);
    static motor_state position_motor_state(const uint64_t position, const uint32_t velocity,
      const bool open_loop);
  };
  
  class node
  {
  public:
    node();
    
    static node &ref()
    {
      if(!_singleton_self) _singleton_self = new node();
      return *_singleton_self;
    }
    
    bool initialize();
    
    inline void set_auto_publish(const bool auto_publish) { _auto_publish = auto_publish; }
    inline bool auto_publish() const { return _auto_publish; }
    
    void set_analog_pullup(const uint8_t id, const bool pullup);
    void set_digital_mode(const uint8_t id, const bool mode);
    void set_motor_state(const uint8_t id, const motor_state &motor_state);
    void set_servo_position(const uint8_t id, const uint16_t position);
    
    bool analog_pullup(const uint8_t id);
    bool digital_mode(const uint8_t id);
    motor_state motor_state(const uint8_t id);
    uint16_t servo_position(const uint8_t id);
    
  private:
    void motor_states_cb(const bson_t *msg, void *);
    void servo_states_cb(const bson_t *msg, void *);
    void analog_states_cb(const bson_t *msg, void *);
    void digital_states_cb(const bson_t *msg, void *);
    
    static node *_singleton_self;
    
    bool _auto_publish;
    
    std::shared_ptr<daylite::node> _node;
    
    std::shared_ptr<daylite::publisher> _set_motor_states;
    std::shared_ptr<daylite::publisher> _set_servo_states;
    std::shared_ptr<daylite::publisher> _set_analog_states;
    std::shared_ptr<daylite::publisher> _set_digital_states;
    
    std::shared_ptr<daylite::subscriber> _motor_states_sub;
    std::shared_ptr<daylite::subscriber> _servo_states_sub;
    std::shared_ptr<daylite::subscriber> _analog_states_sub;
    std::shared_ptr<daylite::subscriber> _digital_states_sub;
    
  };
}

#endif