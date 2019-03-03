### 42--matt-daemon__InternetServiceDaemon
~Internet service daemon, listen on TCP connections and log all the info to var/log in the background.~

# Usage

```sh
$ make
$ ./Matt_daemon
$ ps aux | grep Matt_daemon
$ netstat -an | grep 4242
$ nc localhost 4242
hello I am Kura
this project is so easy
did it in one day and still have some extra time to play arena and chill.
quit
$ cat [the_path_to_the_log_file]
```
* it will just run in the background and listen to port 4242.
* client can use nc commant to connect to it, it will just log whatever it receives to the log file.
* when receive termination signal, it will log to the file and shut itself down.
