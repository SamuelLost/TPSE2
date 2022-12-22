#!/bin/sh

### BEGIN INIT INFO
# Provides:          serverinit
# Required-Start:    $local_fs $remote_fs $network $syslog
# Required-Stop:     $local_fs $remote_fs $network $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Start node app and ssh server at boot time
# Description:       Enable node app and ssh server service.
### END INIT INFO

case "$1" in
    start)
        echo "Starting node server and ssh server"
        exec ./blink &
        ;;
    stop)
        echo "Starting node server and ssh server"
        pkill -f blink
        ;;
    *)
        echo "Usage: /etc/init.d/init {start|stop}"
        exit 1
            ;;
esac
exit 0