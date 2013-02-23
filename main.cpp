/*
    This example shows how to make a running lights with
    MCP23017 for Raspberry PI

    Version 0.1
*/

#include "mcp23017pi.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    MCP23017PI mcp;

    mcp.begin(0);

    mcp.pinMode(7, OUTPUT);
    mcp.pinMode(6, OUTPUT);
    mcp.pinMode(5, OUTPUT);
    mcp.pinMode(4, OUTPUT);
    mcp.pinMode(3, OUTPUT);
    mcp.pinMode(2, OUTPUT);
    mcp.pinMode(1, OUTPUT);
    mcp.pinMode(0, OUTPUT);

    mcp.digitalWrite(7, HIGH);
    delay(500);
    mcp.digitalWrite(7, LOW);

    mcp.digitalWrite(6, HIGH);
    delay(500);
    mcp.digitalWrite(6, LOW);

    mcp.digitalWrite(5, HIGH);
    delay(500);
    mcp.digitalWrite(5, LOW);

    mcp.digitalWrite(4, HIGH);
    delay(500);
    mcp.digitalWrite(4, LOW);

    mcp.digitalWrite(3, HIGH);
    delay(500);
    mcp.digitalWrite(3, LOW);

    mcp.digitalWrite(2, HIGH);
    delay(500);
    mcp.digitalWrite(2, LOW);

    mcp.digitalWrite(1, HIGH);
    delay(500);
    mcp.digitalWrite(1, LOW);

    mcp.digitalWrite(0, HIGH);
    delay(500);
    mcp.digitalWrite(0, LOW);

    mcp.end();

    return 0;
}
