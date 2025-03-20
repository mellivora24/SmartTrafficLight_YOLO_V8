from serial import Serial

def send_data_to(port, data):
    ser = Serial(port, 9600)
    ser.write(data)
    ser.close()

def receive_data_from(port):
    ser = Serial(port, 9600)
    data = ser.read()
    ser.close()
    return data

if __name__ == "__main__":
    send_data_to('COM3', "Hello, World!")
    print(receive_data_from('COM3'))
