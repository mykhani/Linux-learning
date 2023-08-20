# Using Linux's pseudo-terminal API
This program is just to playaround with the Linux's pseudoterminal API.
It opens `/dev/ptmx` device to get the handle of the master from the
master-slave pair created. The slave end of the connection can be
found by the ptsname_r call which gives the path to slave device at
`/dev/pts/X`. Data written to the master's handle is then received
at the `/dev/pts/X` and vice-versa.
