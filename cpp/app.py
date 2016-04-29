#!/usr/bin/env python2

import subprocess
import time
import pygame
import traceback
import math

size = (800,680)

screen = pygame.display.set_mode(size)

run = True


datadir = "outputImages"

data = {}

def get_norm_age(age):
    if age < 5 :
        return 5
    if age > 80 :
        return 80
    return int(math.floor(age/5)*5)

for gender in ["male","female"] :
    data[gender] = {}
    for age in range(5,85,5) :
        data[gender][age] = pygame.transform.scale(pygame.image.load("/".join([datadir,gender,str(age),"image.jpg"])),size)

data["male"][5].blit(screen,(0,0))

proc = subprocess.Popen(["./openBrMain"],stdout=subprocess.PIPE,stdin=subprocess.PIPE)
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
            num = int(fl[1])
            gender = fl[2].lower()
            age = float(fl[3])
            screen.blit(data[gender][get_norm_age(age)],(0,0))
            #np = int(fl[1])
            #nr = int(fl[2])
            #print(proc.stdout.readline())
            #print(list(map(float,proc.stdout.readline().strip().split())))
            #for i in range(np) :
            #    point = tuple(map(lambda x : int(float(x)),proc.stdout.readline().strip().split()))
            #    pygame.draw.circle(screen,(255,255,255),point,5,2)
            #for i in range(nr) :
            #    rect = tuple(map(lambda x : int(float(x)),proc.stdout.readline().strip().split()))
            #    pygame.draw.rect(screen,(100,100,100),rect,5)
        pygame.display.flip()
        print("FRAME")
    except Exception :
        traceback.print_exc()
        break

proc.stdin.write("QUIT\n")
