#!/usr/bin/env python2

import subprocess
import time
import pygame
import traceback
import math
import os
size = (752,448)

drivers = ['fbcon', 'directfb', 'svgalib', 'x11']
found = False

# finds driver for the current OS
for driver in drivers:
    # Make sure that SDL_VIDEODRIVER is set
    if not os.getenv('SDL_VIDEODRIVER'):
        os.putenv('SDL_VIDEODRIVER', driver)
        try:
            pygame.display.init()
        except Exception:
            print 'Driver: {0} failed.'.format(driver)
            continue
        found = True
        break
if not found:
    raise Exception('No suitable video driver found!')

#Initializes screen
size = (pygame.display.Info().current_w, pygame.display.Info().current_h)
screen = pygame.display.set_mode(size, pygame.FULLSCREEN)

data = {}

# ALl ages are mod 5 with a min of 5 and max of 80
# param age - the age to be normalized
def get_norm_age(age):
    if age < 5 :
        return 5
    if age > 80 :
        return 80
    return int(math.floor(age/5)*5)

#Tranforms all of the images to the correct size
for gender in ["male","female"] :
    data[gender] = {}
    for age in range(5,85,5) :
        data[gender][age] = pygame.transform.scale(pygame.image.load("/".join([datadir,gender,str(age),"image.jpg"])),size)

data["male"][5].blit(screen,(0,0))

#Opens the cpp process and waits for it to initialize
proc = subprocess.Popen(["./openBrMain"],stdout=subprocess.PIPE,stdin=subprocess.PIPE)
while proc.stdout.readline().strip() != "STARTING" :
    pass

# While process does not output 
while True :
    try :
        # Allows pygame to exit
        for event in pygame.event.get():
            if event.type == pygame.QUIT :
                run = False
        # Tells the cpp code to use the webcam
        proc.stdin.write("CAPTURE\n")
        proc.stdin.write("0.webcam\n")
        proc.stdin.flush()
        screen.fill((0,0,0))
        fl = proc.stdout.readline().strip().split()
        # If a face was found then put picture on screen
	if fl[0] == "FACE" :
            num = int(fl[1])
            gender = fl[2].lower()
            age = float(fl[3])
            screen.blit(data[gender][get_norm_age(age)],(0,0))
        pygame.display.flip()
        print("FRAME")
    except Exception :
        traceback.print_exc()
        break
    if pygame.key.get_pressed()[pygame.K_ESCAPE] :
        break
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            break
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                break

proc.stdin.write("QUIT\n")
