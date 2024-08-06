import csv
import re

# Input and output file paths
input_file = 'data.txt'
output_file = 'data_time.csv'

# Regex pattern to match the entire time and angle data
pattern = re.compile(r'(\d{2}:\d{2}:\d{2}\.\d{3}) Angulo Z:(\d+\.\d+)')

# Initialize lists to store the extracted data
time_data = []
angle_data = []

# Read the input file and extract the data
with open(input_file, 'r') as file:
    for line in file:
        match = pattern.search(line)
        if match:
            full_time = match.group(1)
            time_without_first_two_parts = ':'.join(full_time.split(':')[2:])  # Remove first two parts of the time
            time_data.append(time_without_first_two_parts)
            angle_data.append(match.group(2))

# Write the extracted data to a CSV file
with open(output_file, 'w', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)
    csvwriter.writerow(['Time', 'Angle'])
    for time, angle in zip(time_data, angle_data):
        csvwriter.writerow([time, angle])

print(f"Data has been successfully written to {output_file}")
