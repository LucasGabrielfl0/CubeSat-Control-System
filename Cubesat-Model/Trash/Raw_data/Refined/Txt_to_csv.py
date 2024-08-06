import re
import csv

# Function to clean the line and extract the required values
def extract_values(line):
    # Clean up any special characters if needed
    line = line.replace('Â°', '°')
    # Using regular expression to find time, angle, setpoint, and Dc
    match = re.search(r'Time: (\d+) \| Angle ([\-.\d]+)° \| Setpoint: ([\-.\d]+) \| Dc= ([\d.]+)', line)
    if match:
        return match.groups()
    return None

# Read the text file
with open('data.txt', 'r') as file:
    lines = file.readlines()

# Extract values from each line
extracted_values = [extract_values(line) for line in lines]

# Print lines that did not match to help debug
for line, values in zip(lines, extracted_values):
    if values is None:
        print(f"No match for line: {line.strip()}")

# Filter out None values (lines that did not match the pattern)
extracted_values = [values for values in extracted_values if values is not None]

# Write the extracted values to a CSV file
with open('data.csv', 'w', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)
    # Writing the header
    csvwriter.writerow(['Time', 'Angle', 'Setpoint', 'Dc'])
    # Writing the extracted values
    csvwriter.writerows(extracted_values)

print("Values have been extracted and saved to data.csv")
