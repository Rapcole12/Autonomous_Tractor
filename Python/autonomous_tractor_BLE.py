import asyncio
from bleak import BleakClient

BLE_ADDRESS = "34:08:E1:19:51:E7"

BLE_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"

ON = "ON\n".encode("ASCII")
OFF = "OFF\n".encode("ASCII")

async def main():
    async with BleakClient(BLE_ADDRESS) as client:
        if client.is_connected:  
            await client.write_gatt_char(BLE_UUID, ON)
            print("SENT ON")
            await asyncio.sleep(2)
            await client.write_gatt_char(BLE_UUID, OFF)
            print("SENT OFF")
            

asyncio.run(main())