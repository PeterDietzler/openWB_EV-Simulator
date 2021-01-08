# openWB_EV-Simulator
Hardware: ESP32, ESP8266

Die Software simulirt eine "Ladepunkt" und ein "Batteriespeicher" der openWB Wahlbox.

in der config.h wird der Hostname eingetragen 

IP Hostname oder IP Addresse


Name          Hostname
Anbindung     HTTP
IP Adresse
http://IP/setcurrent?current=$WERT



Ladeleistungmodul HTTP

URL Ladeleistung in Watt
http://IP/Ladeleistung


URL Zählerstand in kWh
http://IP/LadeZaehlerKWh


URL Stromstärke Phase 1-3
http://IP/LadeStromL1
http://IP/LadeStromL1
http://IP/LadeStromL1


IP Adresse Plug/Charge Status
http://IP/plugstat
http://IP/chargestat


SOC Modul
http://IP/SoC



Modulkonfiguration Batteriespeicher









