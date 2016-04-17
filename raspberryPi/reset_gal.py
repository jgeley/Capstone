import picamera
from time import sleep
from brpy import init_brpy

#camera = picamera.PiCamera()

#sleep(5)
#camera.capture('newimage.jpg')
br = init_brpy()
br.br_initialize(0,[],use_gui='true')
br.br_set_property('algorithm','FaceRecognition')
br.br_set_property('enrollAll','true')
br.br_enroll('images','gals/meds.gal')
#gal = br.br_make_gallery('images/james3.jpg')
#targets = br.br_enroll_template(gal)

#fileToComp = 'newimage.jpg'

#thisFile = open(fileToComp, 'rb')
#thisData = thisFile.read()
#thisFile.close()
#print 'hi'
#tmpl = br.br_load_img(thisData, len(thisData))
#print 'no'
#target = br.br_enroll_template(tmpl)
#br.br_add_template_to_gallery('meds.gal','tmpl')


#br.br_enroll('images','meds.gal')
#br.br_set_property('enrollAll','false')
#br.br_compare('meds.gal','newimage.jpg','match_scores.csv')
#myGal = br.br_make_gallery('meds.gal')
# look at match_scores.csv for a match

#if no match
#br.br_add_template_to_gallery(myGal,tmpl)
#br.br_close_gallery(myGal)

# if there is match do nothing



#camera = picamera.PiCamera()

#sleep(3)
#camera.capture('image2.jpg')
