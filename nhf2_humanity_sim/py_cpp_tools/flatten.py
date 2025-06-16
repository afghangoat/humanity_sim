import os
import shutil
import re

def flatten_includes(file_path, base_dir):
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.readlines()

    new_content = []
    for line in content:
        if '#include' in line:
            match = re.search(r'#include\s+"(.*?)"', line)
            if match:
                include_path = match.group(1)
                abs_include_path = os.path.normpath(os.path.join(base_dir, include_path))
                new_include = f'#include "{os.path.basename(abs_include_path)}"\n'
                line = line.replace(include_path, os.path.basename(abs_include_path))
        new_content.append(line)

    return new_content

def scan_directory(src_dir, dest_dir):
    os.makedirs(dest_dir, exist_ok=True)

    for root, dirs, files in os.walk(src_dir):
        for file in files:
            if file.endswith('.hpp') or file.endswith('.h') or file.endswith('.cpp') or file.endswith('.c'):
                src_file_path = os.path.join(root, file)
                dest_file_path = os.path.join(dest_dir, file)

                new_content = flatten_includes(src_file_path, root)

                with open(dest_file_path, 'w') as dest_file:
                    dest_file.writelines(new_content)
                print(f"Copied and flattened: {src_file_path} -> {dest_file_path}")

src_directory = './src'
dest_directory = './flattened'

scan_directory(src_directory, dest_directory)