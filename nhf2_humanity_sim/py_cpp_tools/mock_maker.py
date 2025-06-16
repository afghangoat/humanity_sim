import os
import argparse

def create_empty_files_flat(src_dir, dest_dir):
    os.makedirs(dest_dir, exist_ok=True)
    
    for root, _, files in os.walk(src_dir):
        for file in files:
            dest_file_path = os.path.join(dest_dir, file)
            # Avoid overwriting if same filename exists
            if os.path.exists(dest_file_path):
                print(f"Skipped (exists): {dest_file_path}")
                continue

            with open(dest_file_path, 'w', encoding='utf-8') as f:
                pass  # Create empty file
            print(f"Created: {dest_file_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Create flat empty file copies from a recursive folder")
    parser.add_argument("source", help="Source directory (recursive)")
    parser.add_argument("destination", help="Destination directory (flat)")
    args = parser.parse_args()

    create_empty_files_flat(args.source, args.destination)