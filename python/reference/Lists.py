# Lists - similar to arrays but NOT arrays
names = ["Babs", "Rory", "Sasha", "Bubble", "Shakey"]

# Print from start of the list
print(names[2])

# Print starting from the back of the list
print(names[-2])

# Change an item
names[0] = "Bablet"

# Print with a for loop
for row in names:
    print(row)

# this will create a new list to print out
print(names[0:3])

# methods
names.insert(0, -1)
names.remove()
names.clear()
print("Babs" in names)
