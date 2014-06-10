!!MIDI Library v4.1

This library enables MIDI I/O communications on the Arduino serial ports. You can send and receive messages of all kinds (including System Exclusive, RealTime etc..). The purpose of this library is not to make a big synthetizer out of an Arduino board, the application remains yours. However, it will help you interfacing it with other MIDI devices.

Download the latest version [[ https://github.com/FortySevenEffects/arduino_midi_library/releases/download/4.1/Arduino_MIDI_Library_v4.1.zip | here ]].

You can now follow the developments on [[ http://github.com/FortySevenEffects/arduino_midi_library/ | GitHub]].


!!!!Features:
* Compatible with all Arduino boards (and clones with an AVR processor)
* Simple and fast way to send and receive every kind of MIDI message (including all System messages, SysEx, Clock, etc..).
* OMNI input reading (read all channels).
* Software Thru, with message filtering.
* [[ http://playground.arduino.cc/Main/MIDILibraryCallbacks | Callbacks]] to handle input messages more easily.
* Last received message is saved until a new one arrives.
* Configurable: disable input or output if you don't need it, and get the pin back for IO use (and save some flash space).
* Create more than one MIDI port for mergers/splitters applications.
* Use any serial port, hardware or software.


!!!!Changelog:
* 16/04/2014 : Version 4.1 released. Bug fixes regarding running status.
* 13/02/2014 : Version 4.0 released. Moved to GitHub, added multiple instances & software serial support, and a few bug fixes.
* 29/01/2012 : Version 3.2 released. Release notes are [[ http://sourceforge.net/news/?group_id=265194 | here ]]
* 06/05/2011 : Version 3.1 released. Added [[ http://playground.arduino.cc/Main/MIDILibraryCallbacks | callback]] support.
* 06/03/2011 : Version 3.0 released. Project is now hosted on [[ http://sourceforge.net/projects/arduinomidilib/ | SourceForge]].
* 14/12/2009 : Version 2.5 released.
* 28/07/2009 : Version 2.0 released.
* 28/03/2009 : Simplified version of MIDI.begin, Fast mode is now on by default.
* 08/03/2009 : Thru method operationnal. Added some features to enable thru.

!!!!Warning: this library requires Arduino 1.0 or more recent versions.


!!!What do I need to do?

* Download the library ([[ https://github.com/FortySevenEffects/arduino_midi_library/releases/download/4.1/Arduino_MIDI_Library_v4.1.zip | link ]])
* Follow the installation instructions there: http://arduino.cc/en/Guide/Libraries
* Include the library in your sketch using the menu in the IDE, or type [@#include <MIDI.h>@]

You are now ready to use the library. Look at the reference page to learn how to use it, or the examples given. Just don't forget to enable the I/O communications with MIDI.begin...


!!Reference

See the extended reference [[ http://arduinomidilib.fortyseveneffects.com | here ]].
Mirror: [[ http://fortyseveneffects.github.io/arduino_midi_library/ | GitHub ]].

To know how to use the callback feature, see the dedicated page [[ http://playground.arduino.cc/Main/MIDILibraryCallbacks | here]].


!!A few things...

!!!Using MIDI.begin

In the setup() function of the Arduino, you must call the MIDI.begin method. If you don't give any argument to this method, the input channel for MIDI in will be set to 1 (channels are going from 1 to 16, plus MIDI_CHANNEL_OMNI to listen to all channels at the same time).

This method will:
* Start the serial port at the MIDI baudrate (31250)
* Set the input channel at the argument given (if any, else 1)
* Enable Soft Thru, without filtering (everything at the input is sent back)



!!!MIDI Thru

The MIDI Thru allows you to redirect your incoming messages to the MIDI output. It replaces the need of a MIDI Thru connector, as it copies every valid incoming message from the input. For good performance, you might want to call read() in a fast loop, for low latency.

Incoming unread bytes/messages are kept in the Arduino serial buffer, in order not to flood it, check regularily with MIDI.read. See the reference for Thru explanations.

Thru is enabled by default, you can turn it off using appropriate methods.


!!!Hardware

Take a look at [[ http://www.midi.org/techspecs/electrispec.php | the MIDI.org schematic ]]


!!Contact
if you have any comment or support request to make, feel free to contact me at francois.best{at}fortyseveneffects[dot]com.

You can follow the developments on GitHub:
[[ http://github.com/FortySevenEffects/arduino_midi_library/tree/dev ]]

You can also get informations about bug fixes and updates on my twitter account: @fortysevenfx.
