## Korg MS-20 Mini expansion board

Here you will find schematics and documents regarding the MS-20 mini expansion board we're assembling.

#### Background

It all started when my Korg MS-20 mini broke. One every 4 notes would not turn off when the key was released. We started reversing the midi/power board and the keyboard circuit (we'll release a document explaining how most of that works).

IC50 appears to be broken so the solution was to send the selector bits and read the keyboard information using Arduino. We then output the note information via MIDI (DIN 5 pin). A simple (Arduino midi out) --> (synth midi in) cable is enough to complete the repair.
But we didn't stop there. I had a spare Arduino RP2040 so we tried to expand the ms-20 mini capabilities by adding:

- VCO2 output for every waveform
- PWM modulation CV in for VCO1
- HC-SR04 (ultrasound distance sensor) to CV
- 2x LFO out
- Ring Modulator
