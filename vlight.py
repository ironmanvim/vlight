import serial

import string
morse_list = ['01', '1000', '1010', '100', '0', '0010', '110', '0000', '00', '0111', '101', '0100', '11',
              '10', '111', '0110', '1101', '010', '000', '1', '001', '0001', '011', '1001', '1011', '1100',
              '11111', '01111', '00111', '00011', '00001', '00000', '10000', '11000', '11100', '11110',
              '3', '4', '']

alphabet_list = list(string.ascii_lowercase + string.digits + ' \n ')

morse_decode = dict(zip(
    morse_list,
    alphabet_list
))

k = 'Connect'


def decode_string(morse):
    v = list(map(lambda x: morse_decode[x], morse))
    return ''.join(v)


print("Welcome to VLight Decoder")


while True:
    try:
        a = input(k + " to VLight (Press Y to connect)? ")
        if a.upper() == "Y":
            arduinoData = serial.Serial("COM3", 9600)
            print("VLight connection established")
            while True:
                input("Press Enter to read data ")
                size = arduinoData.inWaiting()
                if size:
                    a = arduinoData.read(size)
                    a = str(a, 'utf-8')
                    a = a.split('2')
                    size = len(a)
                    if a[size-1] == '' and a[size-2] == '4':
                        print(decode_string(a))
                    else:
                        print("Error while reading data. Send data again!")
                else:
                    print("No data received to read")
        else:
            break
    except serial.SerialException as e:
        input("Connection Failed (Press Enter to continue)")
        k = 'Reconnect'

    finally:
        try:
            arduinoData.close()
        except NameError as e:
            pass
