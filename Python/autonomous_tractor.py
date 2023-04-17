# Import Bleak
import asyncio
from bleak import BleakClient

# BLE Parameters
BLE_ADDRESS = "34:08:E1:19:51:E7"
BLE_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"

# ASCII Strings to Send
ON = "ON\n".encode("ASCII")
OFF = "OFF\n".encode("ASCII")

# Create Timer
import time
import datetime

start_time = 0
current_time = 0
ticking = False
past_time_running = 0

def start_timer():
	global start_time, ticking
	ticking = True
	start_time = time.time()

def calculate_time_elapsed():
    if ticking:
	    global start_time, current_time
	    current_time = time.time()
	    return (current_time - start_time)
    else:
        return 0

def end_timer():
    global ticking, past_time_running
    past_time_running += calculate_time_elapsed()
    ticking = False
   
def calculate_total_time():
    global past_time_running
    return round(past_time_running + calculate_time_elapsed(), 1)

def formatted_time_string():
    # Get Time Delta String
    total_time_seconds = calculate_total_time()
    time_delta = datetime.timedelta(seconds = total_time_seconds)
    time_string = str(time_delta)

    if (len(time_string) < 9): # Integer seconds
        time_string += ".0"

    time_string = time_string[2:9] # Chop off Hours and Millseconds
    return time_string


# Import Pygame
from cmath import rect
from operator import length_hint
import pygame

# Window Size
WINDOW_HEIGHT = 500
WINDOW_WIDTH = 800

# Colors 
white = (255,255,255)
black = (0,0,0)
light_blue = (173,216,230)
light_green = (144,238,144)
light_yellow = (241,235,156)

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

# Set the crops 
Rec_Width_Crop  = 2; 
Rect_Height_Crop = 75; 
rect_crop_1 = pygame.Rect(400,WINDOW_HEIGHT - 125,Rec_Width_Crop, Rect_Height_Crop );
rect_crop_2 = pygame.Rect(475,WINDOW_HEIGHT - 125,Rec_Width_Crop, Rect_Height_Crop );
rect_crop_3 = pygame.Rect(550,WINDOW_HEIGHT - 125,Rec_Width_Crop, Rect_Height_Crop );
rect_crop_4 = pygame.Rect(625,WINDOW_HEIGHT - 125,Rec_Width_Crop, Rect_Height_Crop );
rect_crop_5 = pygame.Rect(700,WINDOW_HEIGHT - 125,Rec_Width_Crop, Rect_Height_Crop );

##Set the top of the crops 
Elipse_width_crop = 15
Elipse_height_crop = 50
Elipse_crop_1 = pygame.Rect(393,WINDOW_HEIGHT - 175,Elipse_width_crop, Elipse_height_crop );
Elipse_crop_2 = pygame.Rect(468,WINDOW_HEIGHT - 175,Elipse_width_crop, Elipse_height_crop );
Elipse_crop_3 = pygame.Rect(543,WINDOW_HEIGHT - 175,Elipse_width_crop, Elipse_height_crop );
Elipse_crop_4 = pygame.Rect(618,WINDOW_HEIGHT - 175,Elipse_width_crop, Elipse_height_crop );
Elipse_crop_5 = pygame.Rect(693,WINDOW_HEIGHT - 175,Elipse_width_crop, Elipse_height_crop );

# User inputs
pressedSpaceBar = False
pressedEnterKey = False
pressedBackspace = False
pressedStartButton = False 
pressedStopButton = False

# Is the GUI running?
running = True

def pygame_mainloop():
    global running, pressedSpaceBar, pressedEnterKey, pressedBackspace, pressedStartButton, pressedStopButton

    # Reset Input Flags
    pressedSpaceBar = False
    pressedEnterKey = False
    pressedBackspace = False

    #Set Button Press Boolean
    pressedStartButton = False 
    pressedStopButton = False

    # Update User Inputs
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.MOUSEBUTTONDOWN:
            if Button_Start_Text_Rect.collidepoint(event.pos):
                pressedStartButton = True
                print("Pressed START Button")
                
            if Button_Stop_Text_Rect.collidepoint(event.pos):
                pressedStopButton = True
                print("Pressed STOP Button")
        
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                pressedSpaceBar = True
            if event.key == pygame.K_RETURN: 
                pressedEnterKey = True
            if event.key == pygame.K_BACKSPACE:
                pressedBackspace = True
    
    # Draw to the Screen
    window.fill(light_blue)

    # Draw the Ground
    pygame.draw.rect(window,light_green ,rect)

    ##Draw Crops 
    pygame.draw.rect(window,light_yellow,rect_crop_1); 
    pygame.draw.rect(window,light_yellow,rect_crop_2); 
    pygame.draw.rect(window,light_yellow,rect_crop_3); 
    pygame.draw.rect(window,light_yellow,rect_crop_4); 
    pygame.draw.rect(window,light_yellow,rect_crop_5); 

    pygame.draw.ellipse(window,light_yellow,Elipse_crop_1); 
    pygame.draw.ellipse(window,light_yellow,Elipse_crop_2); 
    pygame.draw.ellipse(window,light_yellow,Elipse_crop_3); 
    pygame.draw.ellipse(window,light_yellow,Elipse_crop_4); 
    pygame.draw.ellipse(window,light_yellow,Elipse_crop_5); 

    #Draw Clouds 
    pygame.draw.ellipse(window,white, Elipse_cloud_1)
    pygame.draw.ellipse(window,white, Elipse_cloud_2)
    pygame.draw.ellipse(window,white, Elipse_cloud_3)
    pygame.draw.ellipse(window, white, Elipse_cloud_4)
    pygame.draw.ellipse(window, white, Elipse_cloud_5)

    window.blit(Button_Start_Text,Button_Start_Text_Rect)
    window.blit(Button_Stop_Text,Button_Stop_Text_Rect)
    window.blit(Tractor, Tractor_rect)
    window.blit(text, textRect)

    # Dynamic Text
    window.blit(numBlackTapesText, numBlackTapesTextRect)
    window.blit(timeElapsedText, timeElapsedTextRect)

    pygame.display.update()

numTapes = 0

# Main Program
async def main():
    async with BleakClient(BLE_ADDRESS) as client:
        # Enable Notifications
        def callback(sender, data):
            # Decode the Byte Array
            message = data.decode("ASCII").strip()

            print(message)

            if (message == 'BLACK TAPE'):
                global numTapes
                numTapes += 1

                global numBlackTapesText, numBlackTapesTextRect
                numBlackTapesText = smallfont.render(f"Black Tapes: {numTapes}", True, black, white)
                numBlackTapesTextRect = numBlackTapesText.get_rect()
                numBlackTapesTextRect.center = (200 + WINDOW_WIDTH // 2, 45 + WINDOW_HEIGHT // 2)

        await client.start_notify(BLE_UUID, callback)
        
        # Init Pygame
        pygame.init()
        pygame.font.init()

        # Set the Text
        global text, textRect, Button_Start_Text, Button_Start_Text_Rect, Button_Stop_Text_Rect, Button_Stop_Text
        font = pygame.font.SysFont("timesnewroman", 40)
        smallfont = pygame.font.SysFont("timesnewroman", 30)
        text = smallfont.render('ECE 2804 Autonomous Tractor', True, black, white)
        Button_Start_Text = font.render('START', True, black, white)
        Button_Stop_Text = font.render('STOP', True, black, white)

        Button_Start_Text_Rect = Button_Start_Text.get_rect()
        Button_Start_Text_Rect.center = (85, 30)

        Button_Stop_Text_Rect = Button_Stop_Text.get_rect()
        Button_Stop_Text_Rect.center = (225, 30)

        textRect = text.get_rect()
        textRect.center = (WINDOW_WIDTH // 4, 20 + WINDOW_HEIGHT // 3)

        # Dynamic Text
        global numBlackTapesText, numBlackTapesTextRect, numTapes, timeElapsedTextRect, timeElapsedText
        numBlackTapesText = smallfont.render(f"Black Tapes: {numTapes}", True, black, white)
        numBlackTapesTextRect = numBlackTapesText.get_rect()
        numBlackTapesTextRect.center = (200 + WINDOW_WIDTH // 2, 45 + WINDOW_HEIGHT // 2)

        timeElapsedText = smallfont.render(f"Total Time Driven: {formatted_time_string()}", True, black, white)
        timeElapsedTextRect = timeElapsedText.get_rect()
        timeElapsedTextRect.center = (200 + WINDOW_WIDTH // 2, 75 + WINDOW_HEIGHT // 3)

        # Set Window
        global window, running
        window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
        pygame.display.set_caption("Raphael Rodriguez and Richard Martinez")

        #await client.write_gatt_char(BLE_UUID, OFF)
        while (running):
            await client.read_gatt_char(BLE_UUID)

            # Stop running if the BLE is disconnected
            if (not client.is_connected):
                running = False
                #print("DISCONNECTED")
            if (ticking):
                timeElapsedText = smallfont.render(f"Total Time Driven: {formatted_time_string()}", True, black, white)
                timeElapsedTextRect = timeElapsedText.get_rect()
                timeElapsedTextRect.center = (200 + WINDOW_WIDTH // 2, 75 + WINDOW_HEIGHT // 3)
                #print(formatted_time_string())

            if (pressedStartButton or pressedEnterKey):
                # Turn ON
                await client.write_gatt_char(BLE_UUID, ON)
                start_timer()
                print("BLE START")
            if (pressedStopButton or pressedSpaceBar):
                # Turn OFF
                await client.write_gatt_char(BLE_UUID, OFF)
                end_timer()
                print("BLE STOP")
            if (pressedBackspace):
                # TODO: Add Backspace Functionality?
                await client.write_gatt_char(BLE_UUID, "a\n".encode("ASCII"))
                print("BLE BACKSPACE")

            # Update Pygame
            pygame_mainloop()

# Run the program
asyncio.run(main())


# Quit when done
pygame.quit()

# Print Trip Report
print("--------------------")
print("Tractor Trip Report")
print(f"Number of Black Tapes: {numTapes}")
print(f"Total Time Driven: {formatted_time_string()}")
print("--------------------")
