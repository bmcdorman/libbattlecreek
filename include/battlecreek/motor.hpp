#ifndef _BATTLECREEK_MOTOR_HPP_
#define _BATTLECREEK_MOTOR_HPP_

#include <cstdint>

namespace battlecreek
{
  class motor
  {
  public:
    motor(const uint8_t port);
    
    /**
     * Move the motor at a given power. This behavior is always closed loop.
     * \param amt The power between -1000 and +1000
     */
    void power(const int16_t amt);
    
    /**
     * Move the motor at a given velocity in ticks per second.
     * \param open_loop Whether or not PID control should be used
     * \param ticks_per_second How fast to move in ticks per second
     */
    void velocity(const bool open_loop, const int32_t ticks_per_second);
    
   /**
    * Move the motor to the given position in ticks at a given ticks per second.
    * \param open_loop Whether or not PID control should be used
    * \param ticks_per_second How fast to move in ticks per second
    * \param desired_position The desired motor position in ticks
    */
    void position(const bool open_loop, const int32_t ticks_per_second, const int32_t desired_position);
    
    int16_t power() const;
    int32_t velocity() const;
    int32_t position() const;
    bool open_loop() const;
    uint8_t port() const;
    
    /**
     * Sets the current motor position to 0
     */
    void clear_position();
    
  private:
    uint8_t _port;
    int32_t _origin_position;
  };
}

#endif