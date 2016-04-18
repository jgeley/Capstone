# How to run Joes part
navigate to raspberryPi/
run "qmake main.pro"
run "make"
run "qmake pic.pro"
run "make"
run ./main

# What it does
When ./main is ran, is spawns a sub process that runs until a face is detected. Then after a face is detected it takes a snapshot and sends it to the compare method where it is compared to all faces that have been detected before. If a match is not found it adds the images to the galleries and then goes back to looking for faces again.



