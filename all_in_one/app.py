from flask import Flask, render_template, Response, json, request

# Raspberry Pi camera module (requires picamera package, developed by Miguel Grinberg)
from camera_pi import Camera
import RPi.GPIO as GPIO
from i2c_pwm import *

app = Flask(__name__)

GPIO.setmode(GPIO.BCM)

# Create a dictionary called pins to store the pin number, name, and pin state:
pins = {
   23 : {'name' : 'GPIO 23', 'state' : GPIO.LOW},
   24 : {'name' : 'GPIO 24', 'state' : GPIO.LOW}
   }

# Set each pin as an output and make it low:
for pin in pins:
   GPIO.setup(pin, GPIO.OUT)
   GPIO.output(pin, GPIO.LOW)

@app.route('/')
def index():
    """Video streaming home page."""
    return render_template('index.html')

def gen(camera):
    """Video streaming generator function."""
    while True:
        frame = camera.get_frame()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(gen(Camera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/turn_on_LED1')
def turn_on_LED1():
    GPIO.output(23, GPIO.HIGH)
    # return json.dump({'status: ok'})

@app.route('/turn_off_LED1')
def turn_off_LED1():
    GPIO.output(23, GPIO.LOW)
    # return json.dump({'status: ok'})

@app.route('/turn_on_LED2')
def turn_on_LED2():
    GPIO.output(24, GPIO.HIGH)
    # return json.dump({'status: ok'})

@app.route('/turn_off_LED2')
def turn_off_LED2():
    GPIO.output(24, GPIO.LOW)
    # return json.dump({'status: ok'})

@app.route('/set_pwm', methods=['POST'])
def set_pwm():
    # request.get_data()

    i2c = I2C(1)
    motor = ServoMotor(0, i2c, 0x05)
    motor.turn_to_angle(int(request.get_data()))
    # return json.dump({'status: ok'})


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80, debug=True, threaded=True)
