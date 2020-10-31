# Thermometer

The following repository contains my homemade thermometer project.

## Purpose & Function

This thermometer was made for the Science Olympiad event Detector Building. This repo contains code that finds the temperature of the thermometer probe and calibrates the thermometer to a reference thermometer. 

## Parts Used

 - Arduino Uno
 - NTC Thermistor (MF52-103)
 - Resistor (9.8 kOhm)
 - Voltage Reference (LM4040)
 - Heat Shrink Tube
 - Silicon Adhesive
 - Breadboard
 - Lots of Jumper Wires
 
 ## Circuit Breakdown

![Circuit Diagram](thermometer_circuit.png)

The circuit can be broken down into two parts

 #### Voltage Dividor
 
 The 5V output from the Arduino goes into a 4.096 VRef, which then goes into a voltage divider circuit containing the NTC thermistor and 9.8k Ohm resistor. A wire that reads the voltage across the thermistor is located between the two resistors and connects to an Arduino digital input port. 
  
 #### LED

 Digital output pins power a certain LEDs depending on the calculated temperature.
 
 ## Code Breakdown
 
 #### General
 
 The following files are used to calibrate the themometer to a reference thermometer and measure temperature. The Steinhart-Hart Equation is used to calculate temperature values. 
 
 ![Steinhart-Hart Equation](https://www.ametherm.com/wp-content/uploads/2017/07/Steinhart-and-Hart-Equations-2-4-300x171.jpg)
 
 #### Calibrate
 
 The code in this file calculates the resistance across the thermistor at a given temperature. These values are used in Co_Calc to calibrate the thermometer.
 
 #### Co_Calc
 
 The code in this file caluclates the 
 
 #### Thermometer_1
 
 The code reads the voltage across the thermistor and converts that to resistance. Then, using the Steinhart-hart Equation, resistance is converted to a temperature value.

