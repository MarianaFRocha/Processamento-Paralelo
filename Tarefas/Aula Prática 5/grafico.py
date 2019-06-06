
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import matplotlib as mpl
import numpy as np


thread = [
[0.25591, 0.25733, 0.25742, 0.25439, 0.25353, 0.25397, 0.25969, 0.25295, 0.26470, 0.25582, 0.25990, 0.25703, 0.25577, 0.25594, 0.25724, 0.25945, 0.26498, 0.26792, 0.26612, 0.26226, 0.26239, 0.26210, 0.26074, 0.25416, 0.25526, 0.25486, 0.26126, 0.26023, 0.25467, 0.25817],
[0.14033, 0.15018, 0.15114, 0.14371, 0.13901, 0.14204, 0.14163, 0.13910, 0.17047, 0.14077, 0.14521, 0.16750, 0.14235, 0.14370, 0.14033, 0.16861, 0.14201, 0.14076, 0.14105, 0.13976, 0.14341, 0.14101, 0.14082, 0.13847, 0.17672, 0.17308, 0.17219, 0.14090, 0.13846, 0.14218],
[0.12912, 0.12716, 0.12169, 0.12735, 0.12344, 0.13525, 0.12412, 0.12599, 0.12130, 0.12330, 0.12877, 0.11993, 0.12399, 0.12441, 0.12613, 0.12349, 0.12189, 0.12622, 0.11879, 0.12364, 0.11970, 0.11882, 0.11978, 0.12048, 0.13330, 0.12684, 0.12321, 0.13481, 0.12485, 0.12397],
[0.10113, 0.10469, 0.11396, 0.10303, 0.10309, 0.10162, 0.09658, 0.09699, 0.11109, 0.10786, 0.09934, 0.09789, 0.10331, 0.12470, 0.11155, 0.10635, 0.10107, 0.09926, 0.09901, 0.09815, 0.10218, 0.10029, 0.11355, 0.10416, 0.11164, 0.09938, 0.10225, 0.11867, 0.10032, 0.10083],
[0.10407, 0.10786, 0.11013, 0.10355, 0.10748, 0.11174, 0.11141, 0.11517, 0.11024, 0.10625, 0.10758, 0.11289, 0.11286, 0.11414, 0.11355, 0.11242, 0.11128, 0.10672, 0.11219, 0.11625, 0.10834, 0.11338, 0.11572, 0.11128, 0.14488, 0.12338, 0.14969, 0.12343, 0.10447, 0.10736],
[0.10623, 0.09715, 0.09649, 0.09968, 0.10242, 0.10320, 0.10973, 0.09880, 0.10786, 0.09942, 0.12273, 0.10068, 0.10198, 0.10527, 0.09753, 0.10398, 0.10326, 0.10319, 0.09845, 0.10338, 0.10401, 0.10015, 0.10174, 0.10349, 0.09871, 0.10190, 0.09913, 0.11110, 0.09971, 0.11045],
[0.10178, 0.10578, 0.09955, 0.10272, 0.10718, 0.10246, 0.10558, 0.10380, 0.09660, 0.10552, 0.09767, 0.09946, 0.09802, 0.10171, 0.10148, 0.09689, 0.10620, 0.10129, 0.09856, 0.09893, 0.09913, 0.10596, 0.10737, 0.11616, 0.09814, 0.10502, 0.09579, 0.09768, 0.10104, 0.09980]
]


mediathread = []
stdthread = []

for i in range(7):
	mediathread.append(np.mean(thread[i]))
	stdthread.append(np.std(thread[i]))


fig = plt.figure(figsize=(10,5))
ax1 = fig.add_subplot(111)


## Média e desvio padrão ##

plt.errorbar(np.array(range(len(mediathread)))*2, mediathread, stdthread,label=r'thread', color='#1F77B4', fmt='o', lw=1, capsize=4, markersize=8, markeredgecolor='#1F77B4', markerfacecolor='#8FBBD9')
plt.plot(np.array(range(len(mediathread)))*2, mediathread, color='#1F77B4',lw=2)



ax1.yaxis.grid(True, linestyle='-', linewidth=0.5, which='major', color='lightgrey',alpha=1.0)
# ax1.xaxis.grid(True, linestyle='-', linewidth=0.5, which='major', color='lightgrey',alpha=1.0)

fontSize=12

ax1.set_axisbelow(True)
# ax1.set_title('Titulo', fontsize=fontSize+3, fontweight='bold')
ax1.set_xlabel(r'Número de Thread', fontsize=fontSize+2)
ax1.set_ylabel('Tempo médio (em seg)', fontsize=fontSize+2)
ax1.xaxis.set_label_coords(0.5, -0.08)
#ax1.set_facecolor('white')


handles, labels = ax1.get_legend_handles_labels()
leg = ax1.legend(handles, labels, bbox_to_anchor=(0.01, 0.98), loc=2, borderaxespad=0., fontsize=fontSize)
leg.get_frame().set_facecolor('#FFFFFF')
# plt.legend(title=r'Compilador')


ticks = ['1', '2', '3', '4', '5', '7', '8']
plt.xticks(range(0, len(ticks)*2, 2), ticks, fontsize=fontSize)
plt.yticks(fontsize=fontSize)
plt.xlim(-1, len(ticks)*2-1)
#plt.ylim(-10, 40)


plt.tight_layout()
# plt.show()

plt.savefig('Grafico.pdf',bbox_inches='tight')
