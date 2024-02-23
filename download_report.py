def download_report(test_vector_length_entry, test_vector_number_entry, test_vector):
    file_path = "report.txt"
    with open(file_path, "w") as file:
        test_vector_length = test_vector_length_entry.get()
        test_vector_number = test_vector_number_entry.get()
        file.write(f"Test Vector Length: {test_vector_length}\n")
        file.write(f"Number of Test Vectors: {test_vector_number}\n")

        file.write("Data to be encrypted:\n")
        for vector in test_vector:
            file.write(f"{vector}\n")
        file.write("\n")

        file.write("encrypted data: \n\n")
        file.write("decrypted data: \n\n")
        file.write("accuracy: \n")
        file.write("time taken: \n")
