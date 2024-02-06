from tkinter import *
import random
import string

def toggle_mode():
    mode = mode_var.get()
    if mode == 1:
        encrypt_button.config(text="Encrypt Text", command=encrypt_text)

        encrypt_option_label.grid(row=3, column=0, sticky=W, padx=10, pady=10)
        encrypt_option_menu.grid(row=4, column=0, sticky=W, padx=10)

        attack_option_menu.grid_forget()
        attack_option_label.grid_forget()
        
    elif mode == 2:
        encrypt_button.config(text="Attack", command=attack)

        attack_option_menu.grid(row=4, column=0, sticky=W, padx=10)
        attack_option_label.grid(row=3, column=0, sticky=W, padx=10, pady=10)

        encrypt_option_label.grid_forget()
        encrypt_option_menu.grid_forget()

def encrypt_text():
    message = field.get()
    print("Encrypted Text:", message)

def attack():
    method = attack_var.get()
    print("Attacker Mode with method:", method)

def generate_text():
    random_text = ''.join(random.choices(string.ascii_letters + string.digits, k=10))
    field.delete(0, END)
    field.insert(0, random_text)

def clear_text():
    field.delete(0, END)

if __name__ == "__main__": 
    gui = Tk() 
    gui.configure(background="grey") 
    gui.title("Quantum Permutation Pad Testbed") 
    gui.geometry("640x480") 

    row, column = gui.grid_size()

    mode_var = IntVar()
    mode_var.set(1)  # Set default mode to Encrypt

    mode_label = Label(gui, text="Select Mode:", fg="black")
    mode_label.grid(row=0, column=0, sticky=W, padx=10, pady=10)

    encrypt_mode = Radiobutton(gui, text="Encrypt Mode", variable=mode_var, value=1, command=toggle_mode)
    encrypt_mode.grid(row=1, column=0, sticky=W, padx=10)

    attack_mode = Radiobutton(gui, text="Attacker Mode", variable=mode_var, value=2, command=toggle_mode)
    attack_mode.grid(row=2, column=0, sticky=W, padx=10)

    encrypt_option_label = Label(gui, text="Select Encryption Method:", fg="black")

    encrypt_options = ["QPP", "AES"]
    encrypt_var = StringVar()
    encrypt_var.set(encrypt_options[0])
    encrypt_option_menu = OptionMenu(gui, encrypt_var, *encrypt_options)

    attack_option_label = Label(gui, text="Select Attack Method:", fg="black")
  
    attack_options = ["man in the middle", "Method 2", "Method 3"]
    attack_var = StringVar()
    attack_var.set(attack_options[0]) 
    attack_option_menu = OptionMenu(gui, attack_var, *attack_options)

    encrypt_button = Button(gui, text="Encrypt Text", fg="blue", command=encrypt_text)
    encrypt_button.grid(row=3, column=3, padx=10)

    clear_button = Button(gui, text="Clear", fg="red", command=clear_text)
    clear_button.grid(row=4, column=3, sticky=W, padx=10)

    message_label = Label(gui, text="Enter your message: ", fg="black")
    message_label.grid(row=3, column=1, sticky=W, padx=1)

    field = Entry(gui)
    field.grid(row=3, column=2, sticky=W, padx=1)

    generate_button = Button(gui, text="Generate Text", command=generate_text)
    generate_button.grid(row=4, column=2, sticky=W, padx=10)

    gui.mainloop()
