# Import Pygame
from cmath import rect
from operator import length_hint
import pygame

# Init Pygame
pygame.init()
##Colors 
white = (255,255,255)
black = (0,0,0)
light_blue = (173,216,230)
light_green = (144,238,144)

# Set Window
WINDOW_HEIGHT = 500
WINDOW_WIDTH = 800
window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))

#Set Grass 
Rec_Width = 800
Rec_Height = 50
rect = pygame.Rect(0,WINDOW_HEIGHT-Rec_Height,Rec_Width,Rec_Height)

##Set the Clouds 
Elipse_width = 125
Elipse_height = 50
Elipse_cloud_1 = pygame.Rect(35, 60, Elipse_width, Elipse_height)
Elipse_cloud_2 = pygame.Rect(200, 85, Elipse_width, Elipse_height)
Elipse_cloud_3 = pygame.Rect(365, 35, Elipse_width, Elipse_height)
Elipse_cloud_4 = pygame.Rect(500, 110, Elipse_width, Elipse_height)
Elipse_cloud_5 = pygame.Rect(650, 10, Elipse_width, Elipse_height)


##SET Tractor 
Tractor = pygame.image.load('Tractor_transparent.png');
Tractor_rect = Tractor.get_rect()
Tractor = pygame.transform.scale(Tractor, (Tractor_rect.width // 2, Tractor_rect.height // 2))
Tractor_rect = Tractor.get_rect()
Tractor_rect.center = (150, 335)
# Is the GUI running?
running = True

##SET THE TEXT

font = pygame.font.SysFont("timesnewroman", 20)

text =  font.render('ECE 2804', True, black, white)

"""
textRect = text.get_rect()
textRect.center = (WINDOW_WIDTH // 4, WINDOW_HEIGHT // 2)
"""
 


# Main Loop
while running:
    #This is for user inputs
   
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        """
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                color = "green"
            if event.key == pygame.K_RETURN: 
                color = "blue"
                print("PRESSED ENTER")
            if event.key == pygame.K_BACKSPACE:
                color = "yellow"
                print("PRESSED BACKSPACE")
        """     
    #Start drawing Strings HERE
    """
    window.blit(text,(360,50)) ## LOWER Y COORDINATE MEANS GO UP and LOWER X COORDINATE MEANS GO LEFT
    window.blit(image_extration, (275,250))
    """
    window.fill(light_blue)
    pygame.draw.rect(window,light_green ,rect)
    pygame.draw.ellipse(window,white, Elipse_cloud_1)
    pygame.draw.ellipse(window,white, Elipse_cloud_2)
    pygame.draw.ellipse(window,white, Elipse_cloud_3)
    pygame.draw.ellipse(window, white, Elipse_cloud_4)
    pygame.draw.ellipse(window, white, Elipse_cloud_5)
    window.blit(Tractor,Tractor_rect)
    pygame.display.update()

pygame.quit()
    

    