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
    "position": float32,
    "velocity": float32,
    "power": float32
  },
  ...
}
```

Cases:
  - For open loop position control:
    - mode = "position"
    - open_loop = true
    - positiion = The desired position in meters
    - velocity = The desired velocity in meters/second
  - For closed loop position control:
    - mode = "velocity"
    - open_loop = false
    - position = The desired position in meters
    - velocity = The desired velocity in meters/second
  - For open loop velocity control:
    - mode = "velocity"
    - open_loop = true
    - velocity = The desired velocity in meters/second
  - For closed loop velocity control:
    - mode = "velocity"
    - open_loop = false
    - velocity = The desired velocity in meters/second
  - For closed loop power control:
    - mode = "power"
    - power = The desired power from -1.0 to 1.0
    
`robot/set_motor_calibration`
-----------------------------

```
"msg" : {
  "0": float32, # ticks per meter
  ...
}
```

Note: float32 shall be `NaN` for no configuration

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
    "velocity": float32,
    "power": float32
  },
  ...
}
```

Note: The position, velocity, and power will be returned regardless of mode.

`robot/motor_calibration`
-------------------------

```
"msg": {
  "0": float32, # ticks per meter
  ...
}
```