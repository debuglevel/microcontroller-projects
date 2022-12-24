# PlatformIO cheat sheet

## Install `platformio`

See their website.
It might still be `python3 -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"`

## `/dev/ttyUSB*` permissions

`sudo chmod 666 /dev/ttyUSB0`

To let you regular user access `/dev/ttyUSB*` without `chmod`ing it every time, add some udev rules:

```sh
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/master/scripts/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules > /dev/null
```

## Activate virtual environment

For the sake of ease, just do `source ~/.platformio/penv/bin/activate` to activate the Python virtual environment of platfomio.
`platformio` (and the shortcut `pio`) will be in your `$PATH` from now on (instead of `~/.platformio/penv/bin/platformio`).

## List `run` targets

```sh
$ platformio run --list-targets

Environment    Group     Name         Title                        Description
-------------  --------  -----------  ---------------------------  ------------------------------------------------------------
esp32          Advanced  compiledb    Compilation Database         Generate compilation database `compile_commands.json`
esp32          General   clean        Clean
esp32          General   cleanall     Clean All                    Clean a build environment and installed library dependencies
esp32          Platform  buildfs      Build Filesystem Image
esp32          Platform  erase        Erase Flash
esp32          Platform  size         Program Size                 Calculate program size
esp32          Platform  upload       Upload
esp32          Platform  uploadfs     Upload Filesystem Image
esp32          Platform  uploadfsota  Upload Filesystem Image OTA
```

## Compile and upload

* `pio run` will compile the project for every environment defined in `platformio.ini`.
Use `--environment esp32` to compile it only for one environment.
* `platformio run --target=upload` will compile and upload the project via `ttyUSB`.
Again, use `--environment esp32` to define which board is plugged in, as there will be chaos otherwise.

## Monitor Serial

`platformio device monitor` should just work, as it uses the baudrate from `platformio.ini`.

Also try filters, e.g. `platformio device monitor -f time` to display a timestamp. `-f esp8266_exception_decoder` should decode crash exceptions.

Some bootloaders like in ESP8266 send some stuff over serial. If not set to the correct baudrate, this is just decoded
as garbage.

You probably have to cancel monitoring if you want to `pio run upload`. Some combination
like `pio run --target upload --target monitor` or `pio upload && pio device monitor` might be a usable workaround.

## PlatformIO `home` GUI

`pio home` starts a web GUI on `localhost:8008`. If you want, you can open it using `platformio home --host=0.0.0.0`.
You can then secure it ba providing some kind of token: `platformio home --host=0.0.0.0 --session-id=hello` which makes
it available at <http://HOST:8008/session/hello/> for those who know.

## MQTT

MQTT Explorer is a nice tool to subscribe to topics and graph their history.
