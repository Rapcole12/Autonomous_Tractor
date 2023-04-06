# Import Pygame and Bluetooth
import asyncio
import pygame
from bleak import BleakClient

# Init Pygame
pygame.init()

# Set Window
WINDOW_HEIGHT = 500
WINDOW_WIDTH = 800
window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))

#set BLE Parameters
BLE_ADDRESS = "34:08:E1:19:51:E7"
BLE_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"

#Set ON and OFF commands
ON = "ON\n".encode("ASCII")
OFF = "OFF\n".encode("ASCII")

# Is the GUI running?
running = True
color = "red"

##SET THE TEXT
white = (255,255,255)
black = (0,0,0)

##Counter to display a message once
display_once = 0

font = pygame.font.SysFont("timesnewroman", 20)

text =  font.render('ECE 2804', True, black, white)

"""
textRect = text.get_rect()

textRect.center = (WINDOW_WIDTH // 4, WINDOW_HEIGHT // 2)
"""

##SET THE IMAGE
image_extration = pygame.image.load("Tractor.png")

def handle_Motors(client):
    global running, color
        #This is for user inputs
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                color = "green"
            elif event.key == pygame.K_RETURN: 
                client.write_gatt_char(BLE_UUID, ON)
                color = "blue"
                print("PRESSED ENTER")
            elif event.key == pygame.K_BACKSPACE:
                client.write_gatt_char(BLE_UUID, OFF)
                color = "yellow"
                print("PRESSED BACKSPACE")     
    window.fill(color)
            #Start drawing Strings HERE
    window.blit(text,(360,50)) ## LOWER Y COORDINATE MEANS GO UP and LOWER X COORDINATE MEANS GO LEFT
    window.blit(image_extration, (275,250))
    pygame.display.update()

async def Handle_BLE_Connection(client):
   if client.is_connected:
      print("BLE IS CONNECTED")
      display_once = display_once + 1

async def main():
    # Main Loop
    async with BleakClient(BLE_ADDRESS) as client:
         while running:
            if display_once == 0:
                Handle_BLE_Connection(client)    
            handle_Motors(client)
    pygame.quit()

asyncio.run(main())