import re
import string
import os.path
from os import path


#Description:
#       To call this function, pass the function name into the CallProcedure function.
#Example:
#       callProcedure("CountAll");
#Output:
#       Returns a list of all unique items in CS210, and prints all of their occurrances.
#Return:
#       None
def CountAll():
    #Open the file in read mode
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Create an empty dictionary to store "found" words
    dictionary = dict()

    #Check each line of the input file