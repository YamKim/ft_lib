#!/bin/sh

sleep 2
influx -execute "CREATE DATABASE telegraf;"
influx -execute "CREATE USER yekim WITH PASSWORD '5933' WITH ALL PRIVILEGES;"
influx -execute "GRANT ALL ON telegraf TO yekim;"
influx -execute "SHOW USERS;"

sleep 2
/usr/sbin/telegraf/telegraf &
influxd run -config /etc/influxdb.conf
