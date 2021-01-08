# openWB_EV-Simulator
Hardware: ESP32, ESP8266


Der Ampere sollwert wird an http://$IP/setcurrent?current=$WERT gesendet. Für eine korrekte Funktion ist als Ladeleistungsmodul HTTP zu wählen. WERT kann sein: 0 = keine Ladung erlaubt, 6-32 = x Ampere erlaubt. 

Die abgerufene Url muss eine reine Zahl zurückgeben. Enthält der Rückgabewert etwas anderes, wird der Wert auf null gesetzt. Der Wert muss in Watt sein. 


Die abgerufene Url muss eine reine Zahl zurückgeben. Enthält der Rückgabewert etwas anderes, wird der Wert auf null gesetzt. Der Wert muss in kWh mit einem Punkt als Trennzeichen für Nachkommastellen sein. 

Abgerufene werden die Urls http://IP/plugstat und http://IP/chargestat. Rückgabe ist jeweils 0 oder 1. Plugstat gibt an ob ein Stecker steckt, Chargestat gibt an, ob EVSEseitig die Ladung aktiv ist 

