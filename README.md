# Animal Computer Interaction: Sea Otters
---

#### Overview

This project interfaces with an `MPU-6050` and an `ESP-32` which allowed us to gather simple accelerometer and gyroscope data. The collection process and the interface with the `Arduino` is described in [`connection.ino`](connection.ino). Data post-processing is done in the [`Data-Analysis.ipynb`](Data-Analysis.ipynb) notebook.

#### `Arduino` Interface

The `MPU-6050` and `ESP-32` where interfaced into the arduino at known locations so the reference to them in the `connection.ino` is hardcoded. From there, three seperate processes are defined:

- `Setup()`: The setup function was responsible for starting the Wi-Fi client (used later on), ensuring the data collection mechanisms were functioning as expected, and also starting the local server
- `Loop()`: The loop function was responsible for sending data over Wi-Fi, the data transmitted was in a raw string format and was later processed into a `csv` file.
- `Read_MPU()`: The read function was responsible for actually getting the data from the `MPU-6050` and sending it to the `Loop` function to transmit.

#### Data Post-Processing

The Jupyter notebook was responsible for taking in the `csv` formatted data and computing derivative order calculations based off the acceleration data (i.e. _torque_ and _jerk_).


