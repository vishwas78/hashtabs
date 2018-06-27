import random

random_nums = []

for i in range(50):
    x = random.randrange(1, 10000)
    if x not in random_nums:
        random_nums.append(x)
        # if x not in random_nums:
        #     random_nums[x] = 0
        # random_nums[x] += 1

print(random_nums)
# for k in random_nums.keys():
#     print("{}: {}".format(k, random_nums[k]))


{3658, 1829, 7236, 728, 1088, 4022, 3469, 2889, 1550, 3814, 1906, 6297, 9620, 4910, 5963, 6391, 8062, 2150, 1282, 4342,
 2086, 85, 643, 9603, 1958, 2057, 7650, 7838, 9846, 821, 4418, 4993, 1277, 9192, 8777, 6595, 1714, 483, 4998, 7703,
 8744, 6200, 2204, 7457, 1479, 4607, 455, 6581, 2743, 8798}
