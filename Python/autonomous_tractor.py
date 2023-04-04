# Import Pygame
import pygame

# Init Pygame
pygame.init()

# Set Window
WINDOW_HEIGHT = 500
WINDOW_WIDTH = 800
window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))


# Is the GUI running?
running = True
color = "red"

##SET THE TEXT
white = (255,255,255)
black = (0,0,0)

font = pygame.font.SysFont("timesnewroman", 20)

text =  font.render('ECE 2804', True, black, white)

"""
textRect = text.get_rect()

textRect.center = (WINDOW_WIDTH // 4, WINDOW_HEIGHT // 2)
"""

##SET THE IMAGE
image_extration = pygame.image.load("Tractor.png")

# TODO: Every time the enter key is pressed, print "ENTER" to the console, set screen to "blue"
# DONE
# TODO: Every time the backspace key is pressed, print "BACKSPACE" to the console, set screen to "yellow" 
# DONE 
# https://www.pygame.org/docs/ref/key.html
# Use if statements similar to event.key == pygame.K_SPACE

# TODO: Display some text on the screen (Doesn't really matter what text)
# https://www.geeksforgeeks.org/python-display-text-to-pygame-window/#
# https://www.pygame.org/docs/ref/font.html#pygame.font.Font.render   (Read this whole page really)
# https://www.pygame.org/docs/ref/font.html#pygame.font.SysFont
# Basically, create a SysFont object (no need for a .ttf file) and render text to a surface
# Then blit that surface to the screen (blit means drawing one surface onto another in pygame)

# TODO: Try drawing an image on the screen (maybe like a tractor stock image)
# https://www.pygame.org/docs/ref/image.html

# Main Loop
while running:
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
                 
    window.fill(color)
    #Start drawing Strings HERE
    window.blit(text,(360,50)) ## LOWER Y COORDINATE MEANS GO UP and LOWER X COORDINATE MEANS GO LEFT
    window.blit(image_extration, (275,250))

    pygame.display.update()

pygame.quit()
    