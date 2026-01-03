import matplotlib.pyplot as plt

with open('input', 'r') as f:
    vectors = [tuple(map(int, v.strip().split(','))) for v in f]

    sum_c = [sum(c) for c in zip(*vectors)]
    n = len(vectors)
    com = tuple(map(int, [c / n for c in sum_c]))
    print(f"Centre of Mass: {com}.")
    print(f"Biggest Coord: {max([max(v) for v in vectors])}.")
    print(f"Smallest Coord: {min([min(v) for v in vectors])}.")

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.scatter(*zip(*vectors))
plt.savefig('space.png')
plt.show()

