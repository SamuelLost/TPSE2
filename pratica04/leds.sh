#Desligando todos os led primeiramente
echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr0/brightness
echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr1/brightness
echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr2/brightness
echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr3/brightness
if [ $1 = "count_up" ]; then

	i=0
	while [ $i -le $2 ]
	do	
		aux=$i
		echo "Contagem: $aux"
		echo $(($aux & 1)) > /sys/devices/platform/leds/leds/beaglebone:green:usr0/brightness
		
		aux=$((aux >> 1))
		echo $(($aux & 1)) > /sys/devices/platform/leds/leds/beaglebone:green:usr1/brightness

		aux=$((aux >> 1))
		echo $(($aux & 1)) > /sys/devices/platform/leds/leds/beaglebone:green:usr2/brightness

		aux=$((aux >> 1))
		echo $(($aux & 1)) > /sys/devices/platform/leds/leds/beaglebone:green:usr3/brightness
		
		sleep 2
		i=$(( $i + 1 ))
		# valid=false
	done
elif [ $1 = "count_down" ]; then
	i=$2
	while [ $i -ge 0 ]
	do	
		aux=$i
		echo "Contagem: $aux"
		echo $(($aux & 1)) > /sys/devices/platform/leds/leds/beaglebone:green:usr0/brightness
		
		aux=$((aux >> 1))
		echo $(($aux & 1)) > /sys/devices/platform/leds/leds/beaglebone:green:usr1/brightness

		aux=$((aux >> 1))
		echo $(($aux & 1)) > /sys/devices/platform/leds/leds/beaglebone:green:usr2/brightness

		aux=$((aux >> 1))
		echo $(($aux & 1)) > /sys/devices/platform/leds/leds/beaglebone:green:usr3/brightness
		
		sleep 2
		i=$(( $i - 1 ))
		# valid=false
	done
else
	echo "Usage: count_up <0-15>: count up on the user leds | count_down <0-15>: countdown on the user leds"
fi

# echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr0/brightness
# echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr1/brightness
# echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr2/brightness
# echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr3/brightness
