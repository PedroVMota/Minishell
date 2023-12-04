import os

number_of_lines = 0

def remove_first_lines(file_path, num_lines):
    global number_of_lines  # Declare number_of_lines as a global variable
    with open(file_path, 'r') as f:
        lines = f.readlines()
    with open(file_path, 'w') as f:
        f.writelines(lines[num_lines:])
        number_of_lines += 12

def process_files(root_directory):
    for root, _, files in os.walk(root_directory):
        # Skip files in the 'lib/Libft' directory
        if 'lib/Libft' in root:
            continue
        for filename in files:
            if filename.endswith(".c") or filename.endswith(".h"):
                file_path = os.path.join(root, filename)
                remove_first_lines(file_path, 12)
                print(f"Processed: {file_path}")
    print("Number of lines removed: ", number_of_lines)

if __name__ == "__main__":
    root_path = os.getcwd()  # You can replace this with the desired root directory
    process_files(root_path)