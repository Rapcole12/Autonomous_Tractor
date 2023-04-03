import asyncio
from bleak import BleakClient

async def main():
    async with BleakClient("34:08:E1:19:51:E7") as client:
        if client.is_connected:
           print("BLE BLUETOOTH IS CONNECTED")
        else:
            print("BLE BLUETOOTH IS NOT CONNECTED")

asyncio.run(main())