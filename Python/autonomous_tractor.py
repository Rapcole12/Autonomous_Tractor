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

# Main Loop
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                color = "green"

    window.fill(color)

    pygame.display.update()

pygame.quit()
    