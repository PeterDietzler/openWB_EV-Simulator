# openWB_EV-Simulator


# Wofür?
Simulation einer EVSE DIN oder anderer Ladepunkte für sofortiges laden, Überwachung der Ladung, PV Überschussladung und Lastmanagement mehrerer WB.

Die Software simulirt eine "Ladepunkt" und ein "Batteriespeicher" der openWB Wahlbox.



# Was wird benötigt?
Hardware:

- ESP32, ESP8266

Die Software simulirt eine "Ladepunkt" und ein "Batteriespeicher" der openWB Wahlbox.



in der config.h wird der Hostname eingetragen 

IP Hostname oder IP Addresse



## OpenWB - Einstellungen - Modulkonfiguration - Ladepunkt


- Name
    
    Hostname

- Anbindung

    HTTP

- IP Adresse
    
    IP = Hostname oder IP-Addresse
    
    http://IP/setcurrent?current=$WERT
    

- Ladeleistungmodul HTTP

- URL Ladeleistung in Watt    

    http://IP/Ladeleistung


- URL Zählerstand in kWh       

    http://IP/LadeZaehlerKWh


- URL Stromstärke Phase 1-3

  http://IP/LadeStromL1

  http://IP/LadeStromL1

  http://IP/LadeStromL1


- IP Adresse Plug/Charge Status

  http://IP/plugstat

  http://IP/chargestat


- SOC Modul
  http://IP/SoC
  
  
  

## OpenWB - Einstellungen - Modulkonfiguration - Batteriespeicher


- Speicher-Modul
    
    HTTP Abfrage
    
- Leistung URL

    http://IP/Ladeleistung

- SoC URL
  
  http://IP/SoC







