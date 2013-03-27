MMA8452Q
========

The **MMA8452Q** is a tiny and low-power three-axis accelerometer. This library
implements a simple interface to access most of the accelerometer functionality
from an Arduino.

This library has support for the following features:

* Normal and fast raw axes values reading
* Scale configuration (allowed 2g, 4g and 8g scales)
* Custom offset calibration
* Low noise mode
* Auto-WAKE/SLEEP mode
* Orientation detection (portrait/landscape and back/front)

See the [simple.ino](examples/simple.ino) example for more information.

## TODO

* Motion and freefall detection
* Single and double tap detection
* Auto-WAKE/SLEEP detection
* Interrupts configuration

## DEPENDENCIES

The only dependency is the standard [Wire](http://arduino.cc/en/Reference/Wire)
Arduino library.

## INSTALLATION

Just clone the repository into your user libraries directory. For example, on
OSX, the default directory is `~/Documents/Arduino/libraries/` and on Windows
it's `My Documents\Arduino\libraries\`.

## COPYRIGHT

Copyright (C) 2013 Alessandro Ghedini <alessandro@ghedini.me>

See COPYING for the license.
