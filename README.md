MCP23017-PI
===========

Version 0.1

Raspberry PI functions for use with MCP23017

This library was ported from the original Arduino library wich can be found here: https://github.com/kasperskaarhoj/MCP23017-Arduino-Library.

To achieve this, BCM2835 library must be installed and can be found here: http://www.open.com.au/mikem/bcm2835/index.html.
Simply follow the instalation steppes.

The MCP23017 datasheet can be found in: http://ww1.microchip.com/downloads/en/devicedoc/21952b.pdf.

To compile simply execute the followinf command:

```gcc -o mcp main.cpp mcp23017pi.cpp -l bcm2835```

Then you can execute it with the following:

```sudo ./mcp```

For the wiring:


<img src="https://swp.pt/mcp23017_connections.png">
