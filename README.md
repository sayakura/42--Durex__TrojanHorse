### 42--matt-daemon__InternetServiceDaemon
*Internet service daemon, listen on TCP connections and log all the info to var/log in the background.*

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

$ ./Matt_daemon -h
Usage: make [options] [parameters] ...
Options:
  -h                         Print this menu.
  -p                         Path for the log file.
  -a                         Enable authentication, enter login and password seperated by ':'
  -e                         Enable encryption mode.
  

$ ./Matt_daemon -a kura:123
#this will start the daemon in secure mode, all the incomming connection will need to authenticate first.



$ ./Matt_daemon -e
#this will start the daemon in encryption mode.
```
* it will just run in the background and listen to port 4242.
* client can use nc commant to connect to it, it will just log whatever it receives to the log file.
* when receive termination signal, it will log to the file and shut itself down.

### Bounus ideas
- [ ] Create a graphical client to interact with the daemon.
- [x] Add utility functions to your daemon (creating a remote shell by
example!).
- [x] Encrypt the sending and receiving of data (involves a customer, logically).
- [ ] Advanced archiving of logs.
- [ ] Sending mail according to selected filtering rules.
- [x] Create an authentication system to connect to the daemon (via graphical / remote client
shell).
- [ ] Use of advanced encryption systems (public / private key).
