# Automatic RGB565 Color Tracking Example
#
# This example shows off single color automatic RGB565 color tracking using the OpenMV Cam.

import sensor, image, time, math
import pyb
#print("Letting auto algorithms run. Don't put anything in front of the camera!")

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 500)
sensor.set_auto_gain(False,gain_db_ceiling = 10.880774) # must be turned off for color tracking
#sensor.set_auto_gain(False) # must be turned off for color tracking
#sensor.set_auto_whitebal(False,  (-0.06828868, -6.02073, -5.119987)) # must be turned off for color tracking
clock = time.clock()
led = pyb.LED(3)
led2 = pyb.LED(2)

# Capture the color thresholds for whatever was in the center of the image.
rsi = [(320//6)-(50//2), (240//6)-(20//2), 50, 20] # izquierda
rsd = [((320//6)*5)-((50//2)), ((240//6))-((20//2)), 50, 20] #derecha
rsc = [((320//8)*4)-((50//2)), ((240//24))-((20//2)), 50, 20] #centro

#print("Auto algorithms done. Hold the object you want to track in front of the camera in the box.")
#print("MAKE SURE THE COLOR OF THE OBJECT YOU WANT TO TRACK IS FULLY ENCLOSED BY THE BOX!")
for i in range(30):
    img = sensor.snapshot()
    img.draw_rectangle(rsc)

#print("Learning thresholds...")

threshold = [50, 50, 0, 0, 0, 0] # Middle L, A, B values.
#centro
for i in range(30):
    img = sensor.snapshot()
    hist = img.get_histogram(roi=rsc)
    lo = hist.get_percentile(0.01) # Get the CDF of the histogram at the 1% range (ADJUST AS NECESSARY)!
    hi = hist.get_percentile(0.99) # Get the CDF of the histogram at the 99% range (ADJUST AS NECESSARY)!
    # Average in percentile values.
    threshold[0] = (threshold[0] + lo.l_value()) // 2
    threshold[1] = (threshold[1] + hi.l_value()) // 2
    threshold[2] = (threshold[2] + lo.a_value()) // 2
    threshold[3] = (threshold[3] + hi.a_value()) // 2
    threshold[4] = (threshold[4] + lo.b_value()) // 2
    threshold[5] = (threshold[5] + hi.b_value()) // 2
    for blob in img.find_blobs([threshold], pixels_threshold=200, area_threshold=200, merge=True, margin=20):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())
        img.draw_rectangle(rsc)

for i in range(30):
    img = sensor.snapshot()
    img.draw_rectangle(rsi)

led2.on()
print("cambio")
time.sleep(1250)
led2.off()
#izquierda
for i in range(30):
    img = sensor.snapshot()
    hist = img.get_histogram(roi=rsi)
    lo = hist.get_percentile(0.01) # Get the CDF of the histogram at the 1% range (ADJUST AS NECESSARY)!
    hi = hist.get_percentile(0.99) # Get the CDF of the histogram at the 99% range (ADJUST AS NECESSARY)!
    # Average in percentile values.
    threshold[0] = (threshold[0] + lo.l_value()) // 2
    threshold[1] = (threshold[1] + hi.l_value()) // 2
    threshold[2] = (threshold[2] + lo.a_value()) // 2
    threshold[3] = (threshold[3] + hi.a_value()) // 2
    threshold[4] = (threshold[4] + lo.b_value()) // 2
    threshold[5] = (threshold[5] + hi.b_value()) // 2
    for blob in img.find_blobs([threshold], pixels_threshold=200, area_threshold=200, merge=True, margin=20):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())
        img.draw_rectangle(rsi)

for i in range(30):
    img = sensor.snapshot()
    img.draw_rectangle(rsd)

led2.on()
print("cambio")
time.sleep(1250)
led2.off()
#derecha
for i in range(30):
    img = sensor.snapshot()
    hist = img.get_histogram(roi=rsd)
    lo = hist.get_percentile(0.01) # Get the CDF of the histogram at the 1% range (ADJUST AS NECESSARY)!
    hi = hist.get_percentile(0.99) # Get the CDF of the histogram at the 99% range (ADJUST AS NECESSARY)!
    # Average in percentile values.
    threshold[0] = (threshold[0] + lo.l_value()) // 2
    threshold[1] = (threshold[1] + hi.l_value()) // 2
    threshold[2] = (threshold[2] + lo.a_value()) // 2
    threshold[3] = (threshold[3] + hi.a_value()) // 2
    threshold[4] = (threshold[4] + lo.b_value()) // 2
    threshold[5] = (threshold[5] + hi.b_value()) // 2
    for blob in img.find_blobs([threshold], pixels_threshold=200, area_threshold=200, merge=True, margin=20):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())
        img.draw_rectangle(rsd)

led2.on()
time.sleep(100)
led2.off()

#print("Thresholds learned...")
#print("Tracking colors...")

#threshold = [58, 74, 28, 65, 59, 71]
print(threshold)
while(True):
    clock.tick()
    img = sensor.snapshot()
    img.draw_line(160,0,160,240, color=(0,255,0))
    led.off()
    for blob in img.find_blobs([threshold], pixels_threshold=100, area_threshold=100, merge=True, margin=5):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())
        angle= int((blob.cx()-160)*.22123)
        img.draw_line(160,240,blob.cx(),blob.cy(), color=(255,0,0))
        print(angle)
        led.on()



