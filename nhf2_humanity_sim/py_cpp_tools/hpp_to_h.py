import os
import re
import argparse

def file_contains_template(filepath):
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        return 'template' in f.read()

def find_and_replace_includes(project_dir, old_filename, new_filename):
    pattern = re.compile(rf'#include\s*["<]{re.escape(old_filename)}[">]')
    for root, _, files in os.walk(project_dir):
        for file in files:
            if file.endswith(('.cpp', '.hpp', '.h', '.c', '.cc')):
                filepath = os.path.join(root, file)
                with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()

                new_content = pattern.sub(f'#include "{new_filename}"', content)
                if new_content != content:
                    print(f"Updating includes in {filepath}")
                    with open(filepath, 'w', encoding='utf-8') as f:
                        f.write(new_content)

def process_headers(project_dir):
    for root, _, files in os.walk(project_dir):
        for file in files:
            if file.endswith('.hpp'):
                full_path = os.path.join(root, file)
                if not file_contains_template(full_path):
                    new_filename = file[:-4] + '.h'
                    new_full_path = os.path.join(root, new_filename)

                    print(f"Renaming {file} -> {new_filename}")
                    os.rename(full_path, new_full_path)

                    find_and_replace_includes(project_dir, file, new_filename)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Convert .hpp files (that don't use templates) to .h")
    parser.add_argument("project_directory", help="Path to the project directory")
    args = parser.parse_args()

    process_headers(args.project_directory)
