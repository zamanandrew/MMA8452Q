MMA8452Q
========

The **MMA8452Q** is a tiny and low-power three-axis accelerometer. This library
implements a simple interface to access most of the accelerometer functionality
from an Arduino.

FEATURES
--------

* Normal and fast raw axes values reading
* Scale configuration (allowed 2g, 4g and 8g scales)
* Custom offset calibration
* Low noise mode
* Orientation detection (portrait/landscape and back/front)
* Auto-WAKE/SLEEP mode and detection

See the API reference_ for more information.

.. _reference: http://ghedo.github.io/MMA8452Q/apiref.html

TODO
----

* Motion and freefall detection
* Single and double tap detection
* Interrupts configuration

DEPENDENCIES
------------

The only dependency is the standard Wire_ Arduino library.

.. _Wire: http://arduino.cc/en/Reference/Wire

INSTALLATION
------------

Just clone the repository into your user libraries directory.

For more info, have a look at the Arduino guide_ page.

.. _guide: http://arduino.cc/en/Guide/Libraries

COPYRIGHT
---------

Copyright (C) 2013 Alessandro Ghedini <alessandro@ghedini.me>

See COPYING for the license.
