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
    

    