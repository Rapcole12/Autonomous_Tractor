# Import Bleak
import asyncio
from bleak import BleakClient

# BLE Parameters
BLE_ADDRESS = "34:08:E1:19:51:E7"
BLE_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"

# ASCII Strings to Send
ON = "ON\n".encode("ASCII")
OFF = "OFF\n".encode("ASCII")

# Import Pygame
from cmath import rect
from operator import length_hint
import pygame

WINDOW_HEIGHT = 500
WINDOW_WIDTH = 800

# Colors 
white = (255,255,255)
black = (0,0,0)
light_blue = (173,216,230)
light_green = (144,238,144)

# Set Grass 
Rec_Width = 800
Rec_Height = 50
rect = pygame.Rect(0,WINDOW_HEIGHT-Rec_Height,Rec_Width,Rec_Height)

# Set the Clouds 
Elipse_width = 125
Elipse_height = 50
Elipse_cloud_1 = pygame.Rect(35, 60, Elipse_width, Elipse_height)
Elipse_cloud_2 = pygame.Rect(200, 85, Elipse_width, Elipse_height)
Elipse_cloud_3 = pygame.Rect(365, 35, Elipse_width, Elipse_height)
Elipse_cloud_4 = pygame.Rect(500, 110, Elipse_width, Elipse_height)
Elipse_cloud_5 = pygame.Rect(650, 10, Elipse_width, Elipse_height)

# Set Tractor Image
Tractor = pygame.image.load('Tractor_transparent.png');
Tractor_rect = Tractor.get_rect()
Tractor = pygame.transform.scale(Tractor, (Tractor_rect.width // 2, Tractor_rect.height // 2))
Tractor_rect = Tractor.get_rect()
Tractor_rect.center = (150, 335)

# SET THE TEXT
#font = pygame.font.SysFont("timesnewroman", 20)
#text =  font.render('ECE 2804', True, black, white)

#textRect = text.get_rect()
#textRect.center = (WINDOW_WIDTH // 4, WINDOW_HEIGHT // 2)

# Is the GUI running?
running = True

def pygame_mainloop():
    global running

    #This is for user inputs
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                color = "green"
            if event.key == pygame.K_RETURN: 
                color = "blue"
                print("PRESSED ENTER")
            if event.key == pygame.K_BACKSPACE:
                color = "yellow"
                print("PRESSED BACKSPACE")
            
    #Start drawing Strings HERE
        
    #window.blit(text,(360,50)) ## LOWER Y COORDINATE MEANS GO UP and LOWER X COORDINATE MEANS GO LEFT
    #window.blit(image_extration, (275,250))
    
    window.fill(light_blue)
    pygame.draw.rect(window,light_green ,rect)
    pygame.draw.ellipse(window,white, Elipse_cloud_1)
    pygame.draw.ellipse(window,white, Elipse_cloud_2)
    pygame.draw.ellipse(window,white, Elipse_cloud_3)
    pygame.draw.ellipse(window, white, Elipse_cloud_4)
    pygame.draw.ellipse(window, white, Elipse_cloud_5)
    window.blit(Tractor,Tractor_rect)
    pygame.display.update()


# Main Program
async def main():
    async with BleakClient(BLE_ADDRESS) as client:
        # Init Pygame
        pygame.init()

        # Set Window
        global window, running
        window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))

        while (running):
            print("INSIDE BLE")
            pygame_mainloop()

# Run the program
asyncio.run(main())

# Quit when done
pygame.quit()
    

    