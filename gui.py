from tkinter import *
import random
import string
from download_report import download_report

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
    # Display input data
    input_data_label.config(text="Input Data: " + str(test_vector))

    # Placeholders #TODO replace with actual data
    encrypted_data = "Encrypted Data Placeholder"
    encrypted_data_label.config(text="Encrypted Data: " + encrypted_data)

    decrypted_data = "Decrypted Data Placeholder"
    decrypted_data_label.config(text="Decrypted Data: " + decrypted_data)

    accuracy = "90%"
    accuracy_label.config(text="Accuracy: " + accuracy)

    time_taken = "0.5s"
    time_taken_label.config(text="Time Taken: " + time_taken)

def attack():
    method = attack_var.get()
    print("Attacker Mode with method:", method)

def generate_text():
    test_vector_length = int(test_vector_length_entry.get())
    test_vector_number = int(test_vector_number_entry.get())

    for _ in range(test_vector_number):
        random_text = ''.join(random.choices(string.ascii_letters + string.digits, k=test_vector_length))
        test_vector.append(random_text)
    
    print("Generated Test Vectors:", test_vector)

if __name__ == "__main__":
    test_vector = []

    # GUI Config
    gui = Tk() 
    gui.configure(background="grey") 
    gui.title("Quantum Permutation Pad Testbed") 
    gui.geometry("1280x720") 

    row, column = gui.grid_size()

    mode_var = IntVar()
    mode_var.set(1)  # Set default mode to Encrypt

    # Mode Options
    mode_label = Label(gui, text="Select Mode:", fg="black")
    mode_label.grid(row=0, column=0, sticky=W, padx=10, pady=10)

    encrypt_mode = Radiobutton(gui, text="Encrypt Mode", variable=mode_var, value=1, command=toggle_mode)
    encrypt_mode.grid(row=1, column=0, sticky=W, padx=10)

    attack_mode = Radiobutton(gui, text="Attacker Mode", variable=mode_var, value=2, command=toggle_mode)
    attack_mode.grid(row=2, column=0, sticky=W, padx=10)

    # Encryption Options
    encrypt_option_label = Label(gui, text="Select Encryption Method:", fg="black")

    encrypt_options = ["QPP", "AES"]
    encrypt_var = StringVar()
    encrypt_var.set(encrypt_options[0])
    encrypt_option_menu = OptionMenu(gui, encrypt_var, *encrypt_options)

    encrypt_option_label.grid(row=3, column=0, sticky=W, padx=10, pady=10)
    encrypt_option_menu.grid(row=4, column=0, sticky=W, padx=10)
    
    # Attack Options
    attack_option_label = Label(gui, text="Select Attack Method:", fg="black")
  
    attack_options = ["man in the middle", "Method 2", "Method 3"]
    attack_var = StringVar()
    attack_var.set(attack_options[0]) 
    attack_option_menu = OptionMenu(gui, attack_var, *attack_options)

    # Test Vector Options 
    test_vector_options_label = Label(gui, text="Enter Test Vector Parameters:", fg="black")
    test_vector_options_label.grid(row=5, column=0, sticky=W, padx=10, pady=10)

    test_vector_length = Label(gui, text="Length of Test Vector:", fg="black")
    test_vector_length.grid(row=6, column=0, sticky=W,  padx=10, pady=2)

    test_vector_length_entry = Entry(gui)
    test_vector_length_entry.grid(row=7, column=0, sticky=W, padx=10, pady=2)
    test_vector_length_entry.insert(0, '8')  # Default value of 8

    test_vector_number = Label(gui, text="Number of Test Vectors:", fg="black")
    test_vector_number.grid(row=8, column=0, sticky=W, padx=10, pady=2)

    test_vector_number_entry = Entry(gui)
    test_vector_number_entry.grid(row=9, column=0, sticky=W, padx=10, pady=2)
    test_vector_number_entry.insert(0, '5')  # Default value of 5


    # Result Labels
    result_label = Label(gui, text="Results: ", fg="black")
    result_label.grid(row=0, column=4, sticky=E, padx=10, pady=10)

    input_data_label = Label(gui, text="Input Data: ", fg="black")
    input_data_label.grid(row=1, column=4, sticky=E, padx=10, pady=10)

    encrypted_data_label = Label(gui, text="Encrypted Data: ", fg="black")
    encrypted_data_label.grid(row=2, column=4, sticky=E, padx=10, pady=10)

    decrypted_data_label = Label(gui, text="Decrypted Data: ", fg="black")
    decrypted_data_label.grid(row=3, column=4, sticky=E, padx=10, pady=10)

    accuracy_label = Label(gui, text="Accuracy: ", fg="black")
    accuracy_label.grid(row=4, column=4, sticky=E, padx=10, pady=10)

    time_taken_label = Label(gui, text="Time Taken: ", fg="black")
    time_taken_label.grid(row=5, column=4, sticky=E, padx=10, pady=10)
    # Buttons
    encrypt_button = Button(gui, text="Encrypt Text", fg="blue", command=encrypt_text)
    encrypt_button.grid(row=4, column=3, padx=100)

    generate_button = Button(gui, text="Generate Text", command=generate_text)
    generate_button.grid(row=3, column=3, sticky=W, padx=100)

    download_button = Button(gui, text="Download Results", command=lambda: download_report(test_vector_length_entry, test_vector_number_entry, test_vector))
    download_button.grid(row=10, column=0, sticky=W, padx=10)
    
    gui.mainloop()
