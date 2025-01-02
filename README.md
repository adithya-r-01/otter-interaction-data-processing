<h1 align="center" style="border-bottom: none">
    <a href="https://prometheus.io" target="_blank"><img alt="Prometheus" src="./.assets/heading_image.svg"></a><br>Animal Computer Interaction: Sea Otters
</h1>

- [Overview](https://github.com/adithya-r-01/otter-interaction-data-processing?tab=readme-ov-file#overview)
- [`Arduino` Interface](https://github.com/adithya-r-01/otter-interaction-data-processing?tab=readme-ov-file#arduino-interface)
- [Report](https://github.com/adithya-r-01/otter-interaction-data-processing?tab=readme-ov-file#report)

## Overview

This project interfaces with an `MPU-6050` and an `ESP-32` which allowed us to gather simple accelerometer and gyroscope data. The collection process and the interface with the `Arduino` is described in [`connection.ino`](src/connection.ino). Data post-processing is done in the [`analysis.ipynb`](analysis.ipynb) notebook. The data from the `Arduino` readings is sampled in the [`data.csv`](src/data.csv) file.

## `Arduino` Interface

The `MPU-6050` and `ESP-32` where interfaced into the arduino at known locations so the reference to them in the `connection.ino` is hardcoded. From there, three seperate processes are defined:

- `Setup()`: The setup function was responsible for starting the Wi-Fi client (used later on), ensuring the data collection mechanisms were functioning as expected, and also starting the local server
- `Loop()`: The loop function was responsible for sending data over Wi-Fi, the data transmitted was in a raw string format and was later processed into a `csv` file.
- `Read_MPU()`: The read function was responsible for actually getting the data from the `MPU-6050` and sending it to the `Loop` function to transmit.

## Report

This data collection and analysis process was part of a larger project in conjunction with the _Animal Computer Interaction_ lab at the _Georgia Institute of Technology_. The full report can be found [here](https://drive.google.com/file/d/1vhUtgIPKyBQ3KttIlGnzjX_AYDwL7k8i/view?usp=sharing).

