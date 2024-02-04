from tkinter import *

def encrypt_text():
    message = field.get()
    print("Encrypted Text:", message)

if __name__ == "__main__": 
    gui = Tk() 
    gui.configure(background="purple") 
    gui.title("Quantum Permutation Pad Testbed") 
    gui.geometry("640x480") 

    # define GUI elements
    encryptButton = Button(gui, text="Encrypt Text", fg="blue", command=encrypt_text)
    encryptButton.pack()

    clearButton = Button(gui, text="Clear", fg="red")
    clearButton.pack()

    label = Label(gui, text="Enter your message: ", fg="black", bg="purple")
    label.pack()

    field = Entry(gui)
    field.pack()
 
    # start the GUI 
    gui.mainloop()
