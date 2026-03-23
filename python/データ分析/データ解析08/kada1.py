import numpy as np
import matplotlib.pyplot as plt
import csv
from collections import Counter

hairstyles = ['LongHairCurly', 'LongHairStraight',
         'LongHairBob', 'ShortHairShortCurly',
         'ShortHairShortFlat', 'ShortHairFrizzle']
haircolors = ['Black', 'Blonde', 'Brown']
glasses = ['Blank', 'Round', 'Sunglasses']
cloths = ['BlazerSweater', 'Hoodie', 'Overall', 'ShirtVNeck']
clothcolors = ['Black', 'Green', 'Orange', 'Pink', 'White']

hair_style_count = Counter()
hair_color_count = Counter()
glasses_count = Counter()
cloths_count = Counter()
clothcolor_count = Counter()

with open("08_data.csv", newline="") as f:
    reader = csv.reader(f)
    count = 0
    for row in reader:
        hair_style_count[row[0]]+=1
        hair_color_count[row[1]]+=1
        glasses_count[row[2]]+=1
        cloths_count[row[3]]+=1
        clothcolor_count[row[4]]+=1
        count += 1
'''
d,add = 0,0
style='LongHairStraight'
hcolor='Brown'
glass='Blank'
cloth='ShirtVNeck'
ccolor='White'
'''
d,add=21,1
style='LongHairBob'
hcolor='Black'
glass='Sunglasses'
cloth='Hoodie'
ccolor='Orange'

count = count + d
hc = hair_style_count[style] + add
hcc=hair_color_count[hcolor] + add
gc =glasses_count[glass] + add
cc=cloths_count[cloth] + add
ccc=clothcolor_count[ccolor] + add
prob = hc*hcc*gc*cc*ccc/(count**5)
print(f"確率={prob}")
#print(hair_style_count[style])
#print(hair_color_count[hcolor])
#print(glasses_count[glass])
#print(cloths_count[cloth])
#print(clothcolor_count[ccolor])

'''for style in hairstyles:
    print(f"{style}:{hair_style_count[style]}")
print("-------")
for hcolor in haircolors:
    print(f"{hcolor}:{hair_color_count[hcolor]}")
print("-------")
for glass in glasses:
    print(f"{glass}:{glasses_count[glass]}")
print("-------")
for cloth in cloths:
    print(f"{cloth}:{cloths_count[cloth]}")
print("-------")
for ccolor in clothcolors:
    print(f"{ccolor}:{clothcolor_count[ccolor]}")
'''