import asyncio
from bleak import BleakClient

# BLE Parameters
BLE_ADDRESS = "34:08:E1:19:51:E7"
BLE_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"

# ASCII Strings to Send
ON = "ON\n".encode("ASCII")
OFF = "OFF\n".encode("ASCII")

# Async Functions INTERNAL ONLY
async def async_turnOn():
    async with BleakClient(BLE_ADDRESS) as client:
        if client.is_connected:
            await client.write_gatt_char(BLE_UUID, ON)
            print("SENT ON")
         
async def async_turnOff():
    async with BleakClient(BLE_ADDRESS) as client:
        if client.is_connected:
            await client.write_gatt_char(BLE_UUID, OFF)
            print("SENT OFF")

# Tractor Functions CALL THESE
def tractor_turnOn():
    asyncio.run(async_turnOn())

def tractor_turnOff():
    asyncio.run(async_turnOff())

# TEST INPUT, NOT FINAL
userInput = input("On or Off? ")
if (userInput.upper() == "ON"):
    tractor_turnOn()
elif (userInput.upper() == "OFF"):
    tractor_turnOff()