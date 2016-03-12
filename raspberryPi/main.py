import subprocess
import signal
import os
import time
import pygame
from pygame.locals import *

#blackPic = pygame.image.load('black.jpg')
#blackPic = pygame.transform.scale(blackPic,(200,200))

#catPic = pygame.image.load('cat1.jpg')
#catPic = pygame.transform.scale(catPic,(200,200))

#screen = pygame.display.set_mode((200,200))

def displayRandomImage():
	pygame.quit()
	screen = pygame.display.set_mode((200,200))
	catPic = pygame.image.load('cat1.jpg')
	catPic = pygame.transform.scale(catPic,(200,200))
	screen.blit(catPic,(0,0))
	pygame.display.flip()
	time.sleep(6)

def displayBlackImage():
	pygame.quit()
	screen = pygame.display.set_mode((200,200))
	blackPic = pygame.image.load('black.jpg')
	blackPic = pygame.transform.scale(blackPic,(200,200))
	screen.blit(blackPic,(200,200))
	pygame.display.flip()

def runFacialRecognition():
	proc = os.popen("br -gui -algorithm 'Cvt(Gray)+Cascade(FrontalFace)+Draw(lineThickness=3)+Show(false)' -enroll 0.webcam output.mtx")
	time.sleep(5)
	while os.path.getsize("output.mtx") == 0:
		time.sleep(.1)
	p = subprocess.Popen(['ps', '-A'],stdout=subprocess.PIPE)
	out, err = p.communicate()
	for line in out.splitlines():
		if 'br' in line:
			pid = int(line.split(None, 1)[0])
			os.kill(pid,signal.SIGKILL)
	displayRandomImage()

def main():
	while True:
		displayBlackImage()
		runFacialRecognition()

if __name__ == "__main__":
	main()
