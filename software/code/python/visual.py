import pygame

pygame.init()
screen = pygame.display.set_mode((400, 300))
done = False

while not done:
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      done = True
  # Add this somewhere after the event pumping and before the display.flip()
  pygame.draw.rect(screen, (0, 128, 255), pygame.Rect(30, 30, 60, 60))
  pygame.display.flip()

