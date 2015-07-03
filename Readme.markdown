libbattlecreek
==============

Battlecreek is a client library that publishes/subscribes to actuation and sensor messages over daylite.


Published Daylite Messages
===========================

`robot/set_motor_states`
-----------------------

```
"msg": {
  "0": {
    "mode": "velocity" | "position" | "power" | "off",
    "open_loop": bool,
    "position": uint64,
    "velocity": uint32,
    "power": int16
  },
  ...
}
```

Cases:
  - For open loop position control:
    - mode = "position"
    - open_loop = true
    - positiion = The desired position in ticks
    - velocity = The desired velocity in ticks/second
  - For closed loop position control:
    - mode = "velocity"
    - open_loop = false
    - position = The desired position in ticks
    - velocity = The desired velocity in ticks/second
  - For open loop velocity control:
    - mode = "velocity"
    - open_loop = true
    - velocity = The desired velocity in ticks/second
  - For closed loop velocity control:
    - mode = "velocity"
    - open_loop = false
    - velocity = The desired velocity in ticks/second
  - For closed loop power control:
    - mode = "power"
    - power = The desired power from -1000 to 1000
  

`robot/set_servo_states`
------------------------

```
"msg": {
  "position": [uint16, uint16, uint16, ...]
}
```

Where [0 .. 2^11] are valid positions and 0xFFFF = no change

`robot/set_analog_states`
-------------------------

```
"msg": {
  "pullup": [uint8, uint8, uint8, uint8]
}
```

Where 0 = off, 1 = on, and 0xFF = no change


`robot/set_digital_states`
-------------------------

```
"msg": {
  "mode": [uint8, uint8, uint8, uint8]
}
```

Where 0 = off, 1 = on, and 0xFF = no change


Subscribed Daylite Messages
===========================

`robot/motor_states`
-------------------

```
"msg": {
  "0": {
    "mode": "velocity" | "position" | "power" | "off",
    "open_loop": bool,
    "position": uint64,
    "velocity": uint32,
    "power": uint16
  },
  ...
}
```

Note: The position, velocity, and power will be returned regardless of mode.

`robot/servo_states`
------------------------

```
"msg": {
  "position": [uint16, uint16, uint16, ...]
}
```

`robot/analog_states`
---------------

```
"msg": {
  "value": [uint16, uint16, uint16, ...],
  "pullup": [bool, bool, bool, ...]
}
```

`robot/digital_states`
----------------

```
"msg": {
  "value": [bool, bool, bool, ...],
  "mode": [bool, bool, bool, ...]
}
```
