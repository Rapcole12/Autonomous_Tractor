import pygame

pygame.init()

# Set up the display
display_width = 800
display_height = 600
screen = pygame.display.set_mode((display_width, display_height))

# Set up the button
button_width = 200
button_height = 50
button_rect = pygame.Rect((display_width - button_width) / 2, (display_height - button_height) / 2, button_width, button_height)
button_color = (255, 255, 255)
button_hover_color = (200, 200, 200)
button_text = pygame.font.Font(None, 30).render("Button", True, (0, 0, 0))
button_text_rect = button_text.get_rect(center=button_rect.center)

# Main game loop
while True:
    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == pygame.MOUSEBUTTONDOWN:
            if button_rect.collidepoint(event.pos):
                print("Button clicked!")

    # Draw the button
    mouse_pos = pygame.mouse.get_pos()
    if button_rect.collidepoint(mouse_pos):
        pygame.draw.rect(screen, button_hover_color, button_rect)
    else:
        pygame.draw.rect(screen, button_color, button_rect)
    screen.blit(button_text, button_text_rect)

    # Update the screen
    pygame.display.update()