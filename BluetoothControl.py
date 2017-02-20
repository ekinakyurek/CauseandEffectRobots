from Tkinter import *
import bluetooth
import sys
import os
bd_addr = "00:06:66:71:59:42" #itade address

main = Tk()

port = 1
sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
sock.connect((bd_addr, port))
print 'Connected'
sock.settimeout(5.0)
os.system('xset r off')

def leftKey(event):
    print event.type
    sock.send('A')
    print "Left key pressed"

def rightKey(event):
    sock.send('B')
    print "Right key pressed"

def upKey(event):
    sock.send('C')
    print "Up key pressed"

def downKey(event):
    sock.send('D')
    print "Down key pressed"

def keyRelease(event):
    sock.send('E')
    print "keyRelease"

frame = Frame(main, width=400, height=100)
main.bind('<Left>', leftKey)
main.bind('<Right>', rightKey)
main.bind('<Up>', upKey)
main.bind('<Down>', downKey)
main.bind('<KeyRelease>', keyRelease)
frame.pack()

def on_closing():
    os.system('xset r on')
    main.destroy()
        

main.protocol("WM_DELETE_WINDOW", on_closing)
main.mainloop()
