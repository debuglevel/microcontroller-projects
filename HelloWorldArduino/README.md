## Install platformio
See their website.

Might still be `python3 -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"`

## Activate platformio
For the sake of ease, do `source ~/.platformio/penv/bin/activate` to activate the Python virtual environment of platfomio.
`platformio` (or the shortcut `pio`) will be in your PATH.

## Check which `run` targets exist
```shell
$ ~/.platformio/penv/bin/platformio run --list-targets
Environment    Group     Name         Title                        Description
-------------  --------  -----------  ---------------------------  ------------------------------------------------------------
d1             Advanced  compiledb    Compilation Database         Generate compilation database `compile_commands.json`
d1             General   clean        Clean
d1             General   cleanall     Clean All                    Clean a build environment and installed library dependencies
d1             Platform  buildfs      Build Filesystem Image
d1             Platform  erase        Erase Flash
d1             Platform  size         Program Size                 Calculate program size
d1             Platform  upload       Upload
d1             Platform  uploadfs     Upload Filesystem Image
d1             Platform  uploadfsota  Upload Filesystem Image OTA
```

## Compile and upload
`platformio run --target=upload` will compile and upload it.

## Monitor Serial
`sudo chmod 666 /dev/ttyUSB0` might be needed if you did not install the `udev` rules <https://docs.platformio.org/en/latest/faq.html#platformio-udev-rules>.

`platformio device monitor` might just work, as it loads the baudrate from `platformio.ini`.

Also try filters, e.g. `platformio device monitor -f time` to display a timestamp. `-f esp8266_exception_decoder` should decode crash exceptions.

Some bootloaders like in ESP8266 send some stuff over serial. If not set to the correct baudrate, this is just decoded as garbage.

You probably have to cancel monitoring if you want to `pio run upload`.
Some combination like `pio run --target upload --target monitor` or `pio upload && pio device monitor` might be a usable workaround.

## PlatformIO `home` GUI
`pio home` starts a web GUI on `localhost:8008`.
If you want, you can open it using `platformio home --host=0.0.0.0`.
You can then secure it ba providing some kind of token: `platformio home --host=0.0.0.0 --session-id=hello` which makes it available at <http://HOST:8008/session/hello/> for those who know.

