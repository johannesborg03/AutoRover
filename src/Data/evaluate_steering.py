pairs = [] # Creates list to hold the pairs of ground truth and steering vlaues
with open('log.txt') as f: #Open the log file
    lines = f.readlines() #Read all lines
    #loops through each line in the log file
    for i in range(len(lines)):
        # Remove log prefix if present so everything before the first '|' is ignored
        line = lines[i]
        if '|' in line:
            line = line.split('|', 1)[1].strip()
        else:
            line = line.strip()

        #logic to create the pairs of ground truth and steering values
        if line.startswith('group_14') and (i+1) < len(lines):
            next_line = lines[i+1]
            if '|' in next_line:
                next_line = next_line.split('|', 1)[1].strip()
            else:
                next_line = next_line.strip()
            try:
                # Extract ground truth value from the line
                # Assuming ground truth is the last value in the line after ';'
                ground_truth = float(line.split(';')[-1])
                if "main: groundSteering" in next_line: #checks if the next line contains the steering value
                    steering_str = next_line.split('=')[1].strip()
                    steering_val = float(steering_str) # Convert predicted steering value to float
                    # Skip if it's exactly -0, 0, or 0.0
                    if steering_val not in ['-0', '0', '-0.0', '0.0']:
                        pairs.append((ground_truth, steering_val))
            except Exception as e:
                continue

# Calculate percentage with abs difference < 0.09
close_count = 0
for gt, pred in pairs:
    if abs(gt - pred) < 0.09:
        close_count += 1

#Calculates and print the result as percentage
if pairs:
    percent = 100 * close_count / len(pairs)
    print(f"Percentage of pairs within 0.09: {percent:.2f}%")
    print(f"{close_count} out of {len(pairs)} pairs")
else:
    print("No valid pairs found!")
