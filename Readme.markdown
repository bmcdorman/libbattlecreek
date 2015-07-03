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
    "mode": "velocity" | "position",
    "open_loop": bool,
    "position": float32,
    "velocity": float32,
  },
  ...
}
```

Cases:
  - For open loop position control:
    - mode = "position"
    - open_loop = true
    - positiion = The desired position in meters (in the wheel rotational frame)
    - velocity = The desired velocity in meters/second (in the wheel rotational frame)
  - For closed loop position control:
    - mode = "velocity"
    - open_loop = false
    - position = The desired position in meters (in the wheel rotational frame)
    - velocity = The desired velocity in meters/second (in the wheel rotational frame)
  - For open loop velocity control:
    - mode = "velocity"
    - open_loop = true
    - velocity = The desired velocity in meters/second (in the wheel rotational frame)
  - For closed loop velocity control:
    - mode = "velocity"
    - open_loop = false
    - velocity = The desired velocity in meters/second (in the wheel rotational frame)
    
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
    "mode": "velocity" | "position",
    "open_loop": bool,
    "position": uint64,
    "velocity": float32,
  },
  ...
}
```

Note: The position and velocity will be returned regardless of mode.

`robot/motor_calibration`
-------------------------

```
"msg": {
  "0": float32, # ticks per meter
  ...
}
```