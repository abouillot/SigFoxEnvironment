#Environmental sensing with SmartEverything

This sketch is targeted to [http://smarteverything.it](SmartEverything) Arduino compatible board.
The board is fitted with multiple sensors and a SigFox communication module. This sketch periodically read the HTS211 temperature/humidity sensor, the LPS25H pressure/temperature sensor and the VL6180 light sensor; pack the values in a message and send it to the SIgFox network.

##View data on the SIGFOX Cloud

* Get to your device page (https://backend.sigfox.com/device/:deviceid/info)
* Click on the _device type_ name
* Click _Edit_
* Update the _Display type_
	* Custom
	* `humidity::int:16 temperature1::int:16 pressure::int:16 temperature2::uint:16 luminosity::uint:32`
