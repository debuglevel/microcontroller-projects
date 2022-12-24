# Collection of various boards and how to handle them

- _No_ "ESP32 DEVKITV1" print on back.
- STLABS CP2102 DCLOOK 2108+
- 2\*19=38 Pins <https://raw.githubusercontent.com/AchimPieters/esp32-homekit-camera/master/Images/ESP32-38%20PIN-DEVBOARD.png>

## Arduino configuration

- Board: "DOIT ESP32 DEKITv1" ("ESP Dev Module" and "LOLIN D32" also worked)
- Upload speed: 115200 (921600 also worked)
- Flash frequency: 80 MHz
- Needs to press "BOOT" button for about 1 second while upload waits for `Connecting........_____....._`!

Output of a fresh(?) "ESP-WROOM-32" module (probably "devkit"-size) at 115200 baud.

```
22:15:03.220 -> ets Jun  8 2016 00:22:57
22:15:03.220 ->
22:15:03.220 -> rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
22:15:03.220 -> configsip: 0, SPIWP:0x00
22:15:03.220 -> clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
22:15:03.220 -> mode:DIO, clock div:2
22:15:03.220 -> load:0x3fff0008,len:8
22:15:03.220 -> load:0x3fff0010,len:3480
22:15:03.220 -> load:0x40078000,len:7804
22:15:03.220 -> ho 0 tail 12 room 4
22:15:03.220 -> load:0x40080000,len:252
22:15:03.254 -> entry 0x40080034
22:15:03.254 -> [0;32mI (45) boot: ESP-IDF v2.0-3-gbef9896 2nd stage bootloader[0m
22:15:03.254 -> [0;32mI (46) boot: compile time 05:59:45[0m
22:15:03.254 -> [0;32mI (46) boot: Enabling RNG early entropy source...[0m
22:15:03.254 -> [0;32mI (65) boot: SPI Speed      : 40MHz[0m
22:15:03.254 -> [0;32mI (77) boot: SPI Mode       : DIO[0m
22:15:03.254 -> [0;32mI (90) boot: SPI Flash Size : 4MB[0m
22:15:03.254 -> [0;32mI (102) boot: Partition Table:[0m
22:15:03.288 -> [0;32mI (113) boot: ## Label            Usage          Type ST Offset   Length[0m
22:15:03.288 -> [0;32mI (136) boot:  0 phy_init         RF data          01 01 0000f000 00001000[0m
22:15:03.288 -> [0;32mI (159) boot:  1 otadata          OTA data         01 00 00010000 00002000[0m
22:15:03.288 -> [0;32mI (183) boot:  2 nvs              WiFi data        01 02 00012000 0000e000[0m
22:15:03.288 -> [0;32mI (206) boot:  3 at_customize     unknown          40 00 00020000 000e0000[0m
22:15:03.321 -> [0;32mI (229) boot:  4 ota_0            OTA app          00 10 00100000 00180000[0m
22:15:03.321 -> [0;32mI (252) boot:  5 ota_1            OTA app          00 11 00280000 00180000[0m
22:15:03.321 -> [0;32mI (276) boot: End of partition table[0m
22:15:03.321 -> [0;32mI (289) boot: Disabling RNG early entropy source...[0m
22:15:03.321 -> [0;32mI (306) boot: Loading app partition at offset 00100000[0m
22:15:03.696 -> [0;32mI (1481) boot: segment 0: paddr=0x00100018 vaddr=0x00000000 size=0x0ffe8 ( 65512) [0m
22:15:03.730 -> [0;32mI (1482) boot: segment 1: paddr=0x00110008 vaddr=0x3f400010 size=0x1c5f0 (116208) map[0m
22:15:03.730 -> [0;32mI (1498) boot: segment 2: paddr=0x0012c600 vaddr=0x3ffb0000 size=0x0215c (  8540) load[0m
22:15:03.730 -> [0;32mI (1529) boot: segment 3: paddr=0x0012e764 vaddr=0x40080000 size=0x00400 (  1024) load[0m
22:15:03.730 -> [0;32mI (1552) boot: segment 4: paddr=0x0012eb6c vaddr=0x40080400 size=0x1b028 (110632) load[0m
22:15:03.764 -> [0;32mI (1631) boot: segment 5: paddr=0x00149b9c vaddr=0x400c0000 size=0x00034 (    52) load[0m
22:15:03.764 -> [0;32mI (1632) boot: segment 6: paddr=0x00149bd8 vaddr=0x00000000 size=0x06430 ( 25648) [0m
22:15:03.764 -> [0;32mI (1648) boot: segment 7: paddr=0x00150010 vaddr=0x400d0018 size=0x7a56c (501100) map[0m
22:15:03.764 -> [0;32mI (1676) heap_alloc_caps: Initializing. RAM available for dynamic allocation:[0m
22:15:03.799 -> [0;32mI (1698) heap_alloc_caps: At 3FFBA6B8 len 00025948 (150 KiB): DRAM[0m
22:15:03.799 -> [0;32mI (1719) heap_alloc_caps: At 3FFE8000 len 00018000 (96 KiB): D/IRAM[0m
22:15:03.799 -> [0;32mI (1740) heap_alloc_caps: At 4009B428 len 00004BD8 (18 KiB): IRAM[0m
22:15:03.799 -> [0;32mI (1761) cpu_start: Pro cpu up.[0m
22:15:03.799 -> [0;32mI (1773) cpu_start: Single core mode[0m
22:15:03.832 -> [0;32mI (1786) cpu_start: Pro cpu start user code[0m
22:15:03.832 -> [0;32mI (1847) cpu_start: Starting scheduler on PRO CPU.[0m
22:15:03.832 -> [0;32mI (2069) uart: queue free spaces: 10[0m
22:15:03.832 -> Bin version:0.10.0

22:15:03.867 -> I (2070) wifi: wifi firmware version: c604573
22:15:03.867 -> I (2070) wifi: config NVS flash: enabled
22:15:03.867 -> I (2072) wifi: config nano formating: disabled
22:15:03.867 -> I (2080) wifi: Init dynamic tx buffer num: 32
22:15:03.867 -> I (2080) wifi: wifi driver task: 3ffc4f34, prio:23, stack:3584
22:15:03.867 -> I (2085) wifi: Init static rx buffer num: 10
22:15:03.867 -> I (2089) wifi: Init dynamic rx buffer num: 0
22:15:03.867 -> I (2093) wifi: Init rx ampdu len mblock:7
22:15:03.867 -> I (2097) wifi: Init lldesc rx ampdu entry mblock:4
22:15:03.901 -> I (2102) wifi: wifi power manager task: 0x3ffca2dc prio: 21 stack: 2560
22:15:03.901 -> I (2108) wifi: wifi timer task: 3ffcb35c, prio:22, stack:3584
22:15:03.901 -> [0;31mE (2114) phy_init: PHY data partition validated[0m
22:15:03.901 -> [0;32mI (2139) phy: phy_version: 329, Feb 22 2017, 15:58:07, 0, 0[0m
22:15:03.934 -> I (2140) wifi: mode : softAP (c8:c9:a3:c9:45:cd)
22:15:03.934 -> I (2143) wifi: mode : sta (c8:c9:a3:c9:45:cc) + softAP (c8:c9:a3:c9:45:cd)
22:15:03.934 -> I (2147) wifi: mode : softAP (c8:c9:a3:c9:45:cd)
```

## GetChipID sketch

```c
/* The true ESP32 chip ID is essentially its MAC address.
This sketch provides an alternate chip ID that matches
the output of the ESP.getChipId() function on ESP8266
(i.e. a 32-bit integer matching the last 3 bytes of
the MAC address. This is less unique than the
MAC address chip ID, but is helpful when you need
an identifier that can be no more than a 32-bit integer
(like for switch...case).

created 2020-06-07 by cweinhofer
with help from Cicicok */

uint32_t chipId = 0;

void setup() {
 Serial.begin(115200);
}

void loop() {
 for(int i=0; i<17; i=i+8) {
   chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
 }

 Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
 Serial.printf("This chip has %d cores\n", ESP.getChipCores());
    Serial.print("Chip ID: "); Serial.println(chipId);

 delay(3000);

}
```

```
22:34:20.340 -> ESP32 Chip model = ESP32-D0WDQ6 Rev 1
22:34:20.340 -> This chip has 2 cores
22:34:20.340 -> Chip ID: 13190604
```

## Upload output

Arduino IDE 1.8.10 on Windows 10

```
esptool.py v3.0-dev
Serial port COM5
Connecting........_____.....__
Chip is ESP32-D0WDQ6 (revision 1)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 40MHz
MAC: c8:c9:a3:c9:45:cc
Uploading stub...
Running stub...
Stub running...
Changing baud rate to 921600
Changed.
Configuring flash size...
Auto-detected Flash size: 4MB
Compressed 8192 bytes to 47...
Writing at 0x0000e000... (100 %)
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.0 seconds (effective 4369.0 kbit/s)...
Hash of data verified.
Compressed 17120 bytes to 11164...
Writing at 0x00001000... (100 %)
Wrote 17120 bytes (11164 compressed) at 0x00001000 in 0.1 seconds (effective 951.1 kbit/s)...
Hash of data verified.
Compressed 208688 bytes to 108779...
Writing at 0x00010000... (14 %)
Writing at 0x00014000... (28 %)
Writing at 0x00018000... (42 %)
Writing at 0x0001c000... (57 %)
Writing at 0x00020000... (71 %)
Writing at 0x00024000... (85 %)
Writing at 0x00028000... (100 %)
Wrote 208688 bytes (108779 compressed) at 0x00010000 in 1.7 seconds (effective 979.8 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 128...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (128 compressed) at 0x00008000 in 0.0 seconds (effective 1445.7 kbit/s)...
Hash of data verified.


Leaving...
Hard resetting via RTS pin...
```
