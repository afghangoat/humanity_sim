import os

def scan_directory_for_string(directory, search_string):
    for root, _, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            try:
                with open(file_path, 'r', encoding='utf-8') as f:
                    content = f.read()
                    if search_string in content:
                        print(f"Found in: {file_path}")
            except (UnicodeDecodeError, PermissionError) as e:
                print(f"Skipped (cannot read): {file_path} ({e})")

if __name__ == "__main__":
    input_dir = input("Enter the directory to scan: ")
    search_str = input("Enter the string to search for: ")

    if not os.path.isdir(input_dir):
        print("Invalid directory.")
    else:
        scan_directory_for_string(input_dir, search_str)
