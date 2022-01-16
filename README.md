# arduino-projects

## General CAVEATs
### Avoid blocking the loop for too long
ESP8266 crashes on e.g. a `while(1) { }` loop:

```
21:29:37.122 > Entering endless loop...
21:29:40.220 > --------------- CUT HERE FOR EXCEPTION DECODER ---------------
21:29:40.225 >
21:29:40.226 > Soft WDT reset
21:29:40.226 >
21:29:40.226 > >>>stack>>>
21:29:40.228 >
21:29:40.228 > ctx: cont
21:29:40.228 > sp: 3ffffdc0 end: 3fffffc0 offset: 01a0
21:29:40.232 > 3fffff60:  3ffee47c 3ffe864c 3fffff80 402099bf
21:29:40.237 > 3fffff70:  40202bae 00000000 3fffff80 402010e1 <
21:29:40.240 > 3fffff80:  00000000 00000000 0000000a feefeffe
21:29:40.246 > 3fffff90:  feefeffe feefeffe 3fffffa0 402010b0 <
21:29:40.249 > 3fffffa0:  feefeffe feefeffe 3fffffb0 402022e0 <
21:29:40.255 > 3fffffb0:  feefeffe feefeffe 3fffef30 401016d5
21:29:40.260 > <<<stack<<<
21:29:40.260 >
21:29:40.260 > --------------- CUT HERE FOR EXCEPTION DECODER ---------------
21:29:40.280 >
21:29:40.280 >  ets Jan  8 2013,rst cause:2, boot mode:(3,6)
21:29:40.283 >
21:29:40.283 > load 0x4010f000, len 3460, room 16
21:29:40.290 > tail 4
21:29:40.291 > chksum 0xcc
21:29:40.291 > load 0x3fff20b8, len 40, room 4
21:29:40.293 > tail 4
21:29:40.293 > chksum 0xc9
21:29:40.296 > csum 0xc9
21:29:40.296 > v00045df0
21:29:40.299 > ~ld
21:29:40.358 > Hello World! Loops since last reset: 0

```

`Soft WDT reset` in the exception means the software watchdog timer was triggered. This happens after about 2 seconds.
`rst cause:2` in the bootloader means the hardware watchdog timer was triggered instead (because the software watchdog timer provided by the SDK is disabled or not working).

A `yield()` somehwere in the loop (or a long calculation) should help. This gives the ESP8266 some time to breathe and do things in the background (e.g. WiFi). `Serial.println()` or `delay()` might have the same effect.

See also <https://arduino-esp8266.readthedocs.io/en/latest/faq/a02-my-esp-crashes.html#watchdog>.