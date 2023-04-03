import asyncio
from bleak import BleakClient

BLE_ADDRESS = "34:08:E1:19:51:E7"

async def main():
    async with BleakClient(BLE_ADDRESS) as client:
        while client.is_connected:
           print("BLE BLUETOOTH IS CONNECTED")
        
    print("BLE BLUETOOTH IS NOT CONNECTED")

asyncio.run(main())