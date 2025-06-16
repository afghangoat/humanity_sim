import os

def find_todos(file_path):
    try:
    
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
            i=1;
            for line in file:
                if "TODO" in line:
                    print(file_path+": TODO found in line "+str(i)+"\n")
                i+=1
    except PermissionError:
        print(f"Skipping file: {file_path} (Permission Denied)")
        return 0

def process_file(file_name):
    extensions_mapping = {
        '.cpp': 'Source',
        '.hpp': 'Header'
    }
    for ext, lang in extensions_mapping.items():
        if file_name.endswith(ext):
            find_todos(file_name)

def process_directory(root_dir):

    for root, _, files in os.walk(root_dir):
        for file in files:
            file_path = os.path.join(root, file)
            process_file(file_path)


if __name__ == "__main__":
    folder_path = input("Enter the folder path: ")
    
    print("Checking for todos...\n")

    process_directory(folder_path)
