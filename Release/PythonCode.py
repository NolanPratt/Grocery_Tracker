import re
import string
import numpy as np


# C++ Integration:
# This block can be accessed within the second code block of the C++ file. 
# It integrates C++ calls into the Python functions, which 
# allow for data interpretation between the two languages

def CppInterface(selection = -1):
    # Declare item list
    items = FileReader();

    # Convert to set to filter out recursion and sort by letter
    itemSet = sorted(set(items))

    # Declare blank list container template for item quantities
    numItems = [0] * len(itemSet)

    # Gather item quantities
    numItems = GetFreq(items, itemSet, numItems)

    # Enter process based on user selection
    match int(selection): 
        case 1:
            # Calling Python function to print out the file data
            DisplayBoth(itemSet, numItems)
        case 2:
            # CppDisplaySingle function case call passed to C++
            selection = 2
        case 3:
            # Frequency.dat file created in GetFreq() and return passed to C++
            selection = 3
        case 4:
            print("Thank you for using this program!")
            exit()
        case _:
            print("\nSelection must be within range\n")

    return selection

# Displays the total quantity of the specified item
def CppDisplaySingle(userItem):
    # Declare item list
    items = FileReader();

    # Convert to set to filter out recursion and sort by letter
    itemSet = sorted(set(items))

    # Declare blank list container template for item quantities
    numItems = [0] * len(itemSet)

    # Gather item quantities
    numItems = GetFreq(items, itemSet, numItems)

    # Checker for item found
    i = 0
    # Return value index
    j = 0
    # Iterate through list for desired item
    for item in itemSet:
        # Compare lower casings for easy input validation
        if item.lower() == userItem.lower():
            j = i
            i = -1
    # Check whether the input is in the list
    if i != -1:
        print("This item has not been sold today")

    # Return desired item quantity to C++
    return numItems[j]

# ---------------------------------------------------------------

# Fully Python:
# This block can be called from the second code block within the 
# C++ program to execute the entire program strictly within Python

# Interface handles the user selection for the desired process
def Interface(selection = 0):
    # Declare item list
    items = FileReader()

    # Declare menu items
    menuItems = ["Return unfiltered list of purchased items",
		"Return filtered list of purchased items",
		"Return filtered list of purchased items with corresponding quantities",
		"Return total quantity of only a specific item",
		"Return histogram of purchased items to quantity purchased"]
    
    # Convert to set to filter out recursion and sort by letter
    itemSet = sorted(set(items))

    # Declare blank list container template for item quantities
    numItems = [0] * len(itemSet)

    # Gather item quantities
    numItems = GetFreq(items, itemSet, numItems)

    # Enter interface loop
    while selection != 6:
        # Display menu interface
        selection = DisplayMenu(menuItems)

        # Enter process based on user selection
        match selection: 
            case 1:
                DisplayItems(items)
            case 2:
                DisplayItems(sorted(set(items)))
            case 3:
                DisplayBoth(itemSet, numItems)
            case 4:
                DisplaySingle(itemSet, numItems)
            case 5:
                DisplayHistogram(itemSet, numItems)
            case 6:
                print("Thank you for using this program!")
                exit()
            case _:
                print("\nSelection must be within range\n")

    return 0
    
# Displays the list of items
def DisplayItems(items):
    # List header
    print("\nItems sold today:")

    # Iterate through list to print corresponding name
    for item in items:
        print(item)
    print()

# Displays the list of items and quantities
def DisplayBoth(itemSet, numItems):
    # List header
    print("\nItems and quantities sold today: ")
    
    i = 0
    # Iterate through list to print corresponding name & quantity
    for num in numItems:
        # Std spacing for easier reading
        print(itemSet[i],":" + (" " * (14 - len(itemSet[i]))), num)
        i += 1
    print()

# Displays the total quantity of the specified item
def DisplaySingle(itemSet, numItems):
    # Prompt
    print("Enter an item name to view its purchase history: ")

    # Gather user item and strip any inputted spaces
    userItem = str(input()).lstrip(' ').rstrip(' ')

    i = 0
    # Iterate through list for desired item
    for item in itemSet:
        # Compare lower casings for easy input validation
        if item.lower() == userItem.lower():
            print("The total number of " + item + " sold today is", numItems[i], "\n")
            i = -1

    # Check whether the input is in the list
    if i != -1:
        print("This item has not been sold today")
        i += 1

# Displays a histogram of the data
def DisplayHistogram(items, nums):
    # Header
    print("\nHistogram of data:")

    # Find the maximum quantity
    max_quantity = max(nums)

    i = 0
    # For each item and its corresponding quantity
    for item in items:
        # Print item name
        print(item + ":" + (" " * (14 - len(items[i]))), end='')
        
        # Calculate the number of character bars to print based on 
        # the quantity and max quantity
        num_bars = nums[i] * 20 / max_quantity

        chars = 0
        # Print the character bars
        while chars <= num_bars:
            print('*', end='')
            chars += 1

        i += 1
        print()
    print()

# Tallies the frequencies of each item
def GetFreq(items, itemSet, numItems):
    # Counts through each element within the two sets to detect matches
    itemTracker = 0
    for setItem in itemSet:
        for listItem in items:
            if listItem == setItem:
                numItems[itemTracker] += 1
        itemTracker += 1

    # Send frequencies to FileOutput function
    FileOutput(itemSet, numItems)

    # Return the list of frequencies
    return numItems

# Opens the InputFile within the directory and returns the items as a list
def FileReader():
    # Open the input file for reading
    f = open("InputFile.txt", 'r')

    # Create list container for storing lines
    itemsList = []

    # Iterate through each line to collect items
    for item in f:
        # Appending each line to list container without the '\n' tag
        itemsList.append(item.rstrip('\n ',))

    # Finalize and close file
    f.close()

    # Return list of items
    return itemsList

# Creates and opens the Frequency file for writing
def FileOutput(items, freqs, fileName = "Frequency.dat"):
    # Create and open file for writing
    o = open(fileName, 'w')

    n = 0
    # Iterate through frequencies list
    for num in freqs:
        # Write frequencies into file lines
        o.write(items[n] + ":" + (" " * (14 - len(items[n]))) + str(num) + "\n")
        n += 1

    # Finalize and close file
    o.close()

# Creates menu to prompt user to process
def DisplayMenu(menuItems):
    option = 1
    # Iterate through menu options
    for prompt in menuItems:
        # Print items in menu format
        print(str(option) + ": " + prompt)
        option += 1
        # Check for end of list
        if option == (len(menuItems) + 1):
            print(str(option) + ": Exit")
            print("Please enter desired menu option with corresponding number: ")
            selection = str(input()).rstrip(' ').lstrip(' ')
            return int(selection)

# Reads file contents and returns histogram of values
def HistogramFromFile():
    # Open file for reading
    f = open("Frequency.dat", 'r')

    # Create list container for storing lines
    itemsList = []

    # Iterate through each line to collect items
    for item in f:
        # Appending each line to list container without the '\n' tag
        itemsList.append(item.rstrip('\n ',))

    # Finalize and close file
    f.close()

    # Return list of items
    return itemsList