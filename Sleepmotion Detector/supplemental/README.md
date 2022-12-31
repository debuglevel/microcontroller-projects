# `write-MQTT-to-CSV.py`

This script reads the (CSV) data sent to the MQTT topic.
It puts a ISO-8601 datetime in front of the data line.
As first line, it prints a CSV header.

The most basic call would be:

```bash
python3 write-MQTT-to-CSV.py > ../Data\ Analysis/describe-the-occasion.csv
```

As it would make sense to compress the data, it can be piped into `xz`:

```bash
python3 write-MQTT-to-CSV.py | xz -c -9e > ../Data\ Analysis/describe-the-occasion.csv.xz
```

Unfortunately there is a problem, as CTRL+C sends SIGINT to both processes.
Therefore only the data already compressed and written by `xz` would be in the `.xz`.
To circumvent this, a subshell can be used which ignores the SIGINT.
This way, `xz` handles the buffer.

```bash
python3 write-MQTT-to-CSV.py | ( trap '' INT; xz -9e -c > ../Data\ Analysis/describe-the-occasion.csv.xz )
```
