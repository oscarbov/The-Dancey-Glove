# The-Dancey-Glove
Arduino IDE code for interactive light up glove

This code exports the data from the modulino movement, passes the acceleration through a low pass filter to ignore gravity, regardless of the modulino's orientation (a challenge that took me a while!).

It can be edited and customised. The parameter alpha varies from 0 - 1 and gives the strength of the low pass filter. alpha = 1 would be completely not ignoring gravity, for example.

M is the minimum threshold of movement for lights, i.e. the sensitivity of the glove.

brightscale gives the maxmimum accel value that maxes out the brightness of the lights.

The code is simple to follow, and pretty short, to be easy to edit for others!
