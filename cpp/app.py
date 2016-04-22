#!/usr/bin/env python2

import subprocess
import time
import pygame
import traceback

size = (800,800)

screen = pygame.display.set_mode(size)

run = True

proc = subprocess.Popen(["./main"],stdout=subprocess.PIPE,stdin=subprocess.PIPE)

while proc.stdout.readline().strip() != "STARTING" :
    pass

while run :
    try :
        for event in pygame.event.get():
            if event.type == pygame.QUIT :
                run = False
        proc.stdin.write("CAPTURE\n")
        proc.stdin.write("0.webcam\n")
        proc.stdin.flush()
        screen.fill((0,0,0))
        fl = proc.stdout.readline().strip().split()
	if fl[0] == "FACE" :
            np = int(fl[1])
            nr = int(fl[2])
            print(proc.stdout.readline())
            #print(list(map(float,proc.stdout.readline().strip().split())))
            for i in range(np) :
                point = tuple(map(lambda x : int(float(x)),proc.stdout.readline().strip().split()))
                pygame.draw.circle(screen,(255,255,255),point,5,2)
            for i in range(nr) :
                rect = tuple(map(lambda x : int(float(x)),proc.stdout.readline().strip().split()))
                pygame.draw.rect(screen,(100,100,100),rect,5)
        pygame.display.flip()
        print("FRAME")
    except Exception :
        traceback.print_exc()
        break

proc.stdin.write("QUIT\n")
