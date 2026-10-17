import matplotlib.pyplot as plt

procs = [1, 2, 4, 8]
times = [0.478512, 0.247419, 0.125130, 0.091945]
speedup = [times[0] / t for t in times]

plt.figure()
plt.plot(procs, times, 'o-')
plt.xlabel('Number of processors')
plt.ylabel('Time (s)')
plt.title('Exercise 3: Time vs Processors')
plt.xticks(procs)
plt.grid(True)
plt.savefig('ex3_time.png', dpi=150)

plt.figure()
plt.plot(procs, speedup, 'o-', label='Measured')
plt.plot(procs, procs, '--', label='Ideal')
plt.xlabel('Number of processors')
plt.ylabel('Speedup')
plt.title('Exercise 3: Speedup')
plt.xticks(procs)
plt.legend()
plt.grid(True)
plt.savefig('ex3_speedup.png', dpi=150)
