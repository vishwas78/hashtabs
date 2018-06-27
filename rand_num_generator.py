import random
import matplotlib.pyplot as plt


def HashCalc(key):
    return key % 20000


random_nums = []


i = 10000000
while i < 10020000:
    if not random.randrange(10):
        i += random.randrange(0, 50)
    random_nums.append(i)
    i += 1

# print(random_nums)

hashes = [HashCalc(k) for k in random_nums]

differences = [hashes[x] - hashes[x - 1] for x in range(1, len(hashes))]

# plt.hist(X=k ,bins=[x for x in range(100)], x=k)
plt.scatter([x for x in range(len(differences))], differences)
plt.show()
