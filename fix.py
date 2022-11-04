import math
import os

MAX_SIZE = 110

print('Input lab\'s directory: ', end ='')

lab_num = input()
fr = open(f'{lab_num}/protocol.txt', 'r')
fw = open(f'{lab_num}/temp.txt', 'w')

for line in fr.readlines():
    line = line.replace('\t', '    ')
    l = len(line)
    for i in range(math.ceil(l / MAX_SIZE) + 1):
        nl = line[i * MAX_SIZE:min((i + 1) * MAX_SIZE, l)]
        if len(nl) != 0:
            fw.write(nl)
            if nl[-1] != '\n':
                fw.write('\n')

fr.close()
fw.close()

os.rename(f'{lab_num}/temp.txt', f'{lab_num}/protocol.txt')