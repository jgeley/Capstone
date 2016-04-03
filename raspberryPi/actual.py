

from brpy import init_brpy
import requests
import subprocess
import signal
import os
import time
#import pygame
#from pygame.locals import *

#blackPic = pygame.image.load('black.jpg')
#blackPic = pygame.transform.scale(blackPic,(200,200))

#catPic = pygame.image.load('cat1.jpg')
#catPic = pygame.transform.scale(catPic,(200,200))

#screen = pygame.display.set_mode((200,200))


def main():
	br = init_brpy()
	br.br_initialize(0,[],use_gui='true')
	br.br_set_property('algorithm','Cvt(Gray)+Cascade(FrontalFace)+Draw(lineThickness=3)+Show(false)')
	gal = br.br_make_gallery('output.mtx')
	
	br.br_enroll('0.webcam','output.mtx')
	#br.br_enroll_template('0.webcam')
	#time.sleep(6)
	print "hi"
	br.br_finalize()

if __name__ == "__main__":
	main()
