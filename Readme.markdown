libbattlecreek
==============

Battlecreek is a client library that publishes/subscribes to actuation and sensor messages over daylite.


Published Daylite Messages
===========================

`robot/set_motor_state`
-----------------------

```
"msg": {
  "0": {
    "mode": "velocity" | "position" | "power",
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
  

Subscribed Daylite Messages
===========================

`robot/motor_state`
-------------------

```
"msg": {
  "0": {
    "mode": "velocity" | "position" | "power",
    "open_loop": bool,
    "position": uint64,
    "velocity": uint32,
    "power": uint16
  },
  ...
}
```

Note: The position, velocity, and power will be returned regardless of mode.
