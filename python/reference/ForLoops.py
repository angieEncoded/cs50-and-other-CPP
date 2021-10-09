names = ["Babs", "Rory", "Sasha", "Bubble", "Shakey"]

# For loops
for item in names:
    print(item)

# while loops
i = 0;
while i < len(names):
    print(names[i])
    i += 1;

# range objects
print("----------------------------")
numbers = range(5) # 0-4
for number in numbers:
    print(number)
print("----------------------------")

print("----------------------------")
numbers2 = range(5, 10) # 5-9
for number in numbers2:
    print(number)
print("----------------------------")

print("----------------------------")
numbers3 = range(0,11,2) # 0-10 step 2
for number in numbers3:
    print(number)
print("----------------------------")


