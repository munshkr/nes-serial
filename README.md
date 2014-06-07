# nes-serial #

A proof-of-concept for transmitting data through the NES input controllers with
an Arduino Uno.

This could be used to later implement MIDI inputs to control the audio unit
*wink* *wink* ...

## Requirements ##

* NES
* PowerPak or other ROM loader
* Arduino Uno
  - It should work on others but the PORT manipulation routines may need to be
    changed accordingly.

## Usage ##

...

## Compile ##

If you want to compile the Arduino source, you can use Ino:

    $ cd ino
    $ ino build

To upload to the Arduino:

    # ino upload

For the NES rom, you need the CA65 compiler:

    $ cd nes
    $ make

## Explanation ##

...
