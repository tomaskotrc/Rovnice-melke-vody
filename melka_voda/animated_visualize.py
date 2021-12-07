import pandas as pd
import matplotlib.pyplot as plt
import os

df = pd.read_csv('output_LF.txt', sep=';');
lw = pd.read_csv('endtime_LW.txt', sep=';')

def plot_data(ax, x, y, data, ylim: list, lw=2):
	ax.plot(data[x], data[y], lw=lw)
	ax.set_ylabel(y, fontsize=18)
	ax.set_ylim(ylim)
	ax.grid(True)

times = df['t'].unique()
# print(times)

# sns.set_style('darkgrid')
fig, ax = plt.subplots(2, 1, figsize=(8, 6), sharex=True)

all_data = []
for t in times:
	all_data.append(df[df['t'] == t])

del df

it = 0
for data in all_data[:-1]:
	plot_data(ax[0], 'x', 'h', data, [0, 1])
	plot_data(ax[1], 'x', 'u', data, [-0.1, 1.8])
	ax[1].set_xlabel('x', fontsize=18)
	plt.pause(0.00001)
	if it == 0:
		os.system('pause')
		plt.savefig('pocatecni.png', dpi=300)
		it = 1
	ax[0].clear()
	ax[1].clear()

fig.suptitle(f't_end = {t} s')
plot_data(ax[0], 'x', 'h', data, [0, 1])
plot_data(ax[1], 'x', 'u', data, [-0.1, 1.8])
plot_data(ax[0], 'x', 'h', lw, [0, 1], 1)
plot_data(ax[1], 'x', 'u', lw, [-0.1, 1.8], 1)
ax[1].set_xlabel('x', fontsize=18)
plt.savefig('vysledek.png', dpi=300)

plt.show()