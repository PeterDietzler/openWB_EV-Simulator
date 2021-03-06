# openWB_EV-Simulator


# Wofür?
Simulation einer EVSE DIN oder anderer Ladepunkte für sofortiges laden, Überwachung der Ladung, PV Überschussladung und Lastmanagement mehrerer WB.

Die Software simulirt eine Fharzeug am "Ladepunkt" und ein "Batteriespeicher".

Damit wird ein Bidirektional Ladendes Fahrzeug realisiert. 

# Funktionsweise?

Der ESPxx wird über WLAN mit openWB verbunden und wird als ein Fahrzeug an einem Ladepunkt interpretiert.
Gleichzeitig wird die Batterie des Fahrzeuges als Haus-Batteriespeicher eingebunden.


Über einen Analogen Engang am ESPxx wird die Batterie Spannung gemessen und der "State of Charge" SoC ermittelt.
Der SoC ist für das Fahrzeug und den Batteriespeicher der selbe.
 






# Was wird benötigt?
Hardware:

- ESP32, ESP8266
- ADS1115
- I2C PWM Modul
    ServoMotor für Akku Ladestrom Regler (optional Digital-Analogwandler)
    ServoMotor für Akku Wechslrichter   (optional Digital-Analogwandler)

Software:
Die openWB-Software steuert den EV-Simulator per GET Requests:

In der den openWB Einstellungen - Modulkonfiguration sinde folgende Punkte zu konfigurieren:
    - Ladepunkt
    - Batteriespeicher






## OpenWB - Einstellungen - Modulkonfiguration - Ladepunkt


- Name
    
        Hostname

- Anbindung

         HTTP

- IP Adresse
    
        IP = Hostname oder IP-Addresse
    
        http://IP/setcurrent?current=$WERT
    

- Ladeleistungmodul 
        
        HTTP

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







