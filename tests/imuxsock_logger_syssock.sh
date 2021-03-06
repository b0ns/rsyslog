#!/bin/bash
# test trailing LF handling in imuxsock
# note: we use the system socket, but assign a different name to
# it. This is not 100% the same thing as running as root, but it
# is pretty close to it. -- rgerhards, 201602-19
. ${srcdir:=.}/diag.sh init
check_logger_has_option_d
generate_conf
add_conf '
module(load="../plugins/imuxsock/.libs/imuxsock"
       SysSock.name="'$RSYSLOG_DYNNAME'-testbench_socket")

$template outfmt,"%msg:%\n"
*.notice      action(type="omfile" file=`echo $RSYSLOG_OUT_LOG` template="outfmt")
'
startup
# send a message with trailing LF
logger -d -u $RSYSLOG_DYNNAME-testbench_socket test
# the sleep below is needed to prevent too-early termination of rsyslogd
./msleep 100
shutdown_when_empty # shut down rsyslogd when done processing messages
wait_shutdown	# we need to wait until rsyslogd is finished!
cmp $RSYSLOG_OUT_LOG $srcdir/resultdata/imuxsock_logger.log
if [ ! $? -eq 0 ]; then
  echo "imuxsock_logger_syssock.sh failed"
  echo "contents of $RSYSLOG_OUT_LOG:"
  echo \"$(cat $RSYSLOG_OUT_LOG)\"
  error_exit 1
fi;
exit_test
