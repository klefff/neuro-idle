# neuro:Idle: an e-paper keychain project
> e-paper keychain for a smart little cookie

A keychain with a little neuro and evil in it. Randomly cycle through 12 mildly different images. This is what I got with some spare parts lying around:


## Warning!
This is currently only a personal project, so not everything will be documented in full. Use at your own risk! Code and 3D models provided as-is, with no warranty or support. 
For artwork included in `imagedata.cpp`, please do not use for commercial purposes.

## Parts:
- [Waveshare 1.54in Black and White e-paper display](https://www.waveshare.com/1.54inch-e-paper-module.htm?srsltid=AfmBOookzQq-V9QjeiVIqoWIYjMAoK0YIIsNmEkHs5cvppdsAwC-qUso)
- [Nice Keyboards nice!nano v1](https://nicekeyboards.com/nice-nano/)
  - Overkill, but has a ton of flash memory (the code needs about 135kb of memory because of the images)
  - Also comes with built in battery charge controller
- 602535-size 400mAh LiPo battery
- Small inline switch
- 2x M2x20mm bolts and nuts
- Some breakout boards and jumper wires
- Kapton Tape
- Insulating plastic

## Code:
- Based on the Wareshare code [here](https://github.com/waveshareteam/e-Paper/tree/master/Arduino/epd1in54_V2)
- Pinout modified for nice!nano mcu
- Some code also changed in `epd1in54_V2.cpp` to accomodate for this project's purpose (could have been a bug in original code)
- When the voltage of the battery falls below ~3.6V, a small battery warning will appear on the screen
### Images:
- 200x200px bitmaps converted into char maps using [image2cpp](https://javl.github.io/image2cpp/)
- Change them if you want in `imagedata.cpp`

## Hardware:
### 3D Parts:
- Print out the two files in the `STL Files` folder.
  - Print `nIdle_Housing` with screen-side down
  - Print `nIdle_Cover` with back-side facing down
  - Originally printed with 0.4mm nozzle, ABS filament
- Thread a string or ribbon through the two holes on the back to act as a keychain
- Combine the two pieces with two bolts. The nuts fit into holes inside the `cover` pieces
### Wiring:
- I can show the pinout but everything else is a bit scuffed so use at your own risk:
#### epaper to mcu
- RST <-> P1.04
- DC <-> P1.00
- CS <-> P1.06
- BUSY <-> P0.11
- CLK <-> P1.13
- DIN <-> P0.10
- GND <-> GND
- VCC <-> VCC
#### Battery:
- negative <-> B-
- positive <- switch -> B+
  - for safety
### Assembly:
- I'll show pictures it'll make more sense.
 
# Additional:
### Battery life?
- Dunno lol, I'll update if something happens.

### Future plans?
- Miniaturise, make it thinner
- Bigger screen
- Less spicy battery configuration
- Step counter? Fidget toy? Actually have Neuro in it? yes.
