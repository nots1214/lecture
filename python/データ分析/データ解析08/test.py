import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import csv
from collections import Counter

hairstyles = ['LongHairCurly', 'LongHairStraight',
         'LongHairBob', 'ShortHairShortCurly',
         'ShortHairShortFlat', 'ShortHairFrizzle']
haircolors = ['Black', 'Blonde', 'Brown']
glasses = ['Blank', 'Round', 'Sunglasses']
cloths = ['BlazerSweater', 'Hoodie', 'Overall', 'ShirtVNeck']
clothcolors = ['Black', 'Green', 'Orange', 'Pink', 'White']

face_count = Counter()

with open("08_data.csv", newline="") as f:
    reader = csv.reader(f)
    count = 0
    for row1,row2,row3,row4,row5 in reader:
        face_count[(row1,row2,row3,row4,row5)]+=1
        count += 1
#print(f"{face_count['ShortHairFrizzle', 'Blonde', 'Blank', 'ShirtVNeck', 'Black']}")
prob = face_count['ShortHairFrizzle', 'Blonde', 'Blank', 'ShirtVNeck', 'Black']/count
print(f"確率={prob}")