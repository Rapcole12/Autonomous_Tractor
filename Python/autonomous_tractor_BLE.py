import asyncio
from bleak import BleakClient

BLE_ADDRESS = "34:08:E1:19:51:E7"
# BLE_UUID = "0B616D09-7832-0A4D-30B9-7149D796EDB5".lower()
#BLE_UUID = "94624EC8-6BB1-A9A9-C674-66457472D1B2"
#BLE_UUID = "e0cbf06c-cd8b-4647-bb8a-263b43f0f974"
#BLE_UUID = "61b9a289-600a-59b4-954a-7a751ce0260b"


BLE_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"


ON = "ON".encode("ASCII")
OFF = "OFF".encode("ASCII")

async def main():
    async with BleakClient(BLE_ADDRESS) as client:
        if client.is_connected:
            
            services = client.services
            for service in services:
                characterstics = service.characteristics
                for characterstic in characterstics:
                    print(characterstic.uuid)
                    print(characterstic.properties)
                    print("DONE")
            

            
            await client.write_gatt_char(BLE_UUID, ON)
            print("SENT ON")
            await asyncio.sleep(2)
            await client.write_gatt_char(BLE_UUID, OFF)
            print("SENT OFF")
            

asyncio.run(main())