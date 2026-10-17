import matplotlib.pyplot as plt

procs = [1, 2, 4, 8]
ex3 = [0.478512, 0.247419, 0.125130, 0.091945]
ex6 = [0.479641, 0.247925, 0.126875, 0.093252]
ex7 = [0.481512, 0.248304, 0.127227, 0.094829]

plt.figure()
plt.plot(procs, ex3, 'o-', label='Ex 3: Send, fixed source')
plt.plot(procs, ex6, 's--', label='Ex 6: Send, ANY_SOURCE')
plt.plot(procs, ex7, '^:', label='Ex 7: Bsend, ANY_SOURCE')
plt.xlabel('Number of processors')
plt.ylabel('Time (s)')
plt.title('Monte Carlo Pi: Exercises 3, 6 and 7')
plt.xticks(procs)
plt.legend()
plt.grid(True)
plt.savefig('compare_time.png', dpi=150)
