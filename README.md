# btlehrservice
This is a small application that opens up a listening UNIX socket and
continuously in the background tries to connect to a Bluetooth Low-Energy
(BTLE) Heart Rate monitor. If a connection is successfully established, it
reports the data periodically.

The underlying BTLE stack is huge and comparatively unreliable. It depends
highly on the connection quality and there's a lot of things that can go wrong.
Furthermore, the stack doesn't really seem written to allow to properly handle
these connections ([e.g., I had this issue](https://github.com/labapart/gattlib/issues/132)).
Therefore, btlehrservice is written in a way that encapsulates the actual
fragile BTLE communication in a child *process* and -- as soon as any timeout
occurs -- just kills the whole thing off entirely and retries.

Note that this is currently work-in-progress, but it already shows that the
approach is feasible and works. Just the UNIX socket server has to be
implemented now, but that should be a piece of cake.

## License
GNU GPL-3.
