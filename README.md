# Interpreter Flight-Simulator

This project receives a text file with instructions for flying the flight simulator, and interprets it.

This project contains
  
  -Lexer and Parser to open the text file. 
  
  -Client to send commands to control the simulator and Server to get flight data. 
  
  -Command to use  "command pattern"  to execute the correct command and more.
  
  
## Installation

Install the Flightrear simulator https://www.flightgear.org/

  -Copy the `generic_small.xml` to path `/usr/share/games/flightgear/Protocol/`

  -Run `make` in yuor Terminal, and run `./main`
