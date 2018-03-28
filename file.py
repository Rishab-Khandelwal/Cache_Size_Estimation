import matplotlib.pyplot as plt
import sys

def plot(file):
    # 4,8,16
    # 0.6
    f = open('result.txt', 'r')
    x = []
    y = []
    count = 0;
    for line in f.readlines():
        if (count == 0):
            x = line.split(',')
            count += 1
        elif count == 1:
            y = line.split(',')
        else: break
    plt.plot(x,y)
    plt.show()



if __name__ == '__main__':
    plot(sys.argv[1])
