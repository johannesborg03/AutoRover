import re

input_file = 'log.txt'  #chooses input file

#read all lines from the file
with open(input_file, 'r') as f:
    lines = f.readlines()

output = [] #list to store tne ouput lines for the valid pairs
current_timestamp = None # temporary stores the timestamp from group line
current_ground_steering = None #temporary stores the ground steering line

for line in lines: #llops through each line in the file
    group_match = re.match(r'my-template-opencv-1\s+\|\s+group_14;(\d+);([-\d.e]+)', line) #matches group line
    if group_match:
        #saves timestamp amnd ground steering
        current_timestamp = group_match.group(1)
        current_ground_steering = group_match.group(2)
        continue #moves to the next line

    #looks for log lines with steering values and gets the value after groundsteering
    steering_match = re.match(r'my-template-opencv-1\s+\|\s+main: groundSteering = ([-\d.e]+)', line) 
    if steering_match and current_timestamp is not None: # makes sure current_timestamp is not None
        computed_steering = steering_match.group(1) # stores computed value for pairing wiht ground truth
        # SKIP pairs where computed steering is "-0" or "0"
        if computed_steering not in ['-0', '0', '-0.0', '0.0']:
            # format the pair and add to output
            output_line = f'group_14;{current_timestamp};{current_ground_steering};{computed_steering}'
            output.append(output_line)
        # reset for the next pair    
        current_timestamp = None
        current_ground_steering = None
#prints all the valid pairs
for line in output:
    print(line)
