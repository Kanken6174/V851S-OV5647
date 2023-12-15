import re

def extract_defines(header_file_path):
    # Make the pattern case-insensitive
    define_pattern = re.compile(r'#define\s+([\w_]+)\s+(0x[0-9A-Fa-f]{4})', re.IGNORECASE)
    defines = {}

    with open(header_file_path, 'r') as file:
        for line in file:
            match = define_pattern.search(line)
            if match:
                # Store the define name and address in original case for replacement
                defines[match.group(2).lower()] = match.group(1)
    
    return defines

def replace_registers_in_c_file(c_file_path, defines, output_file_path):
    with open(c_file_path, 'r') as file:
        c_file_content = file.readlines()

    with open(output_file_path, 'w') as file:
        for line in c_file_content:
            # Use a case-insensitive search for each address in the line
            for addr, name in defines.items():
                line = re.sub(re.escape(addr), name, line, flags=re.IGNORECASE)
            file.write(line)

# Usage
header_file_path = './ov5647_mipi_regs.h'  # Replace with the path to your header file
c_file_path = './ov5647_mipi.h'  # Replace with the path to your C file
output_file_path = './ov5647_mipi.h'  # Replace with the path where you want to save the updated C file

defines = extract_defines(header_file_path)
replace_registers_in_c_file(c_file_path, defines, output_file_path)