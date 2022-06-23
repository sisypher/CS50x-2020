from sys import exit, argv
import csv


# checks that if the user has entered command line arguments 
if len(argv) != 3:
    print("Missing command line argument.")
    exit(1)

# naming each command line argument for simplicity
database = argv[1]
sequence = argv[2]

# a list of STRS in the csv file
strands = []

# the dna data of each given person that will search for later in our databases
persons = {}

# opens the csv file for reading
with open(database, "r") as db:
    for ind, row in enumerate(db):
        # read the first row without the first column
        if ind == 0:
            strands = [strand for strand in row.strip().split(',')][1:]
        else:
            curr_row = row.strip().split(',')
            
            # curr_row >> is the name which we will make the key, 
            # and curr_row[1:] >> is the dna data which we'll assign to the kay as a list
            persons[curr_row[0]] = [int(x) for x in curr_row[1:]]

with open(sequence, "r") as sq:
    dna = sq.read().strip()
    
    # for the algorithm that i implemented here is a window which looks for the str moving char by char
    final_strands = []
    for strand in strands:
        i = 0
        temp_count = 0
        max_count = 0
        while i < len(dna):
            curr_window = dna[i:i + len(strand)]
            if curr_window == strand:
                temp_count += 1
                max_count = max(max_count, temp_count)
                i += len(strand)
            
            else:
                # reset the temp_count to 0
                temp_count = 0
                
                # move the window by 1 character
                i += 1
                
        final_strands.append(max_count)
        
for name, dna_data in persons.items():
    if dna_data == final_strands:
        print(name)
        exit(1)

print('No match')