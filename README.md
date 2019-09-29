# btlehrservice
This is a small application that opens up a listening UNIX socket and
continuously in the background tries to connect to a Bluetooth Low-Energy
(BTLE) Heart Rate monitor. If a connection is successfully established, it
reports the data periodically.

The underlying BTLE stack is huge and comparatively unreliable. It depends
highly on the connection quality and there's a lot of things that can go wrong.
Furthermore, the stack doesn't really seem written to allow to properly handle
reconnections ([e.g., I had this issue](https://github.com/labapart/gattlib/issues/132)).
Therefore, btlehrservice is written in a way that encapsulates the actual
fragile BTLE communication in a child *process* (i.e., contain it in its own
address space) and -- as soon as any timeout occurs -- just kills the whole
thing off entirely and retries.

## Usage
It's quite simple, there's not many arguments right now:

```
usage: btlehrservice dest_mac_address socket

Bluetooth Low Energy Heart Rate service.

positional arguments:
  dest_mac_address  BTLE MAC address of the device that the btlehrservice
                    should try to connect to.
  socket            UNIX socket that the btlehrservice listens on.
```

For example:

```
$ ./btlehrservice 20:C3:8F:FF:0A:7E heartrate_socket
```

This opens a "heartrate_socket" UNIX socket that gives linewise JSON data when
connected to it. For example:

```
{ "connected": false }
{ "connected": false }
{ "connected": false }
{ "connected": true, "have_value": false, "ts": 0.000000, "last_value": 0 }
{ "connected": true, "have_value": false, "ts": 0.000000, "last_value": 0 }
{ "connected": true, "have_value": false, "ts": 0.000000, "last_value": 0 }
{ "connected": true, "have_value": false, "ts": 0.000000, "last_value": 0 }
{ "connected": true, "have_value": true, "ts": 1569758841.500977, "last_value": 78 }
{ "connected": true, "have_value": true, "ts": 1569758842.498586, "last_value": 78 }
{ "connected": true, "have_value": true, "ts": 1569758843.496032, "last_value": 78 }
{ "connected": true, "have_value": true, "ts": 1569758844.493620, "last_value": 78 }
{ "connected": true, "have_value": true, "ts": 1569758845.491243, "last_value": 77 }
{ "connected": true, "have_value": true, "ts": 1569758846.488755, "last_value": 77 }
{ "connected": true, "have_value": true, "ts": 1569758847.486287, "last_value": 77 }
```

The "connected" item indicates if a BTLE connection was successfully
established. The "have_value" item indicates if the heart rate monitor returned
a value (and therefore the "last_value" heart rate in BPM is current).

## License
GNU GPL-3.
