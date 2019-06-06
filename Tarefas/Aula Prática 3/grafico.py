
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import matplotlib as mpl
import numpy as np


M_100 = [
[0.00417, 0.00292, 0.00317, 0.00436, 0.00304, 0.00451, 0.00271, 0.00271, 0.00306, 0.00269, 0.00270, 0.00262, 0.00274, 0.00277, 0.00285, 0.00285, 0.00277, 0.00274, 0.00273, 0.00278, 0.00426, 0.00296, 0.00295, 0.00410, 0.00292, 0.00431, 0.00455, 0.00430, 0.00426, 0.00426],
[0.00503, 0.00237, 0.00278, 0.00276, 0.00278, 0.00266, 0.00273, 0.00291, 0.00277, 0.00273, 0.00273, 0.00274, 0.00240, 0.00239, 0.00273, 0.00274, 0.00277, 0.00226, 0.00333, 0.00245, 0.00286, 0.00292, 0.00383, 0.00249, 0.00256, 0.00417, 0.00255, 0.00289, 0.00236, 0.00238],
[0.00485, 0.00248, 0.00252, 0.00385, 0.00244, 0.00252, 0.00270, 0.00271, 0.00291, 0.00263, 0.00259, 0.00276, 0.00252, 0.00316, 0.00258, 0.00270, 0.00288, 0.00287, 0.00270, 0.00278, 0.00249, 0.00276, 0.00278, 0.00281, 0.00282, 0.00251, 0.00280, 0.00416, 0.00285, 0.00269],
[0.00270, 0.00275, 0.00272, 0.00280, 0.00289, 0.00282, 0.00282, 0.00400, 0.00397, 0.00408, 0.00414, 0.00288, 0.00258, 0.00253, 0.00226, 0.00339, 0.00283, 0.00374, 0.00395, 0.00424, 0.00430, 0.00342, 0.00285, 0.00260, 0.00248, 0.00270, 0.00484, 0.00257, 0.00319, 0.00329],
[0.00254, 0.00298, 0.00247, 0.00250, 0.00281, 0.00234, 0.00259, 0.00251, 0.00252, 0.00253, 0.00250, 0.00250, 0.00250, 0.00251, 0.00253, 0.00247, 0.00288, 0.00305, 0.00255, 0.00250, 0.00262, 0.00253, 0.00251, 0.00268, 0.00264, 0.00402, 0.00459, 0.00436, 0.00280, 0.00363],
[0.00286, 0.00270, 0.00256, 0.00280, 0.00272, 0.00271, 0.00411, 0.00268, 0.00268, 0.00271, 0.00362, 0.00276, 0.00280, 0.00273, 0.00296, 0.00278, 0.00423, 0.00311, 0.00255, 0.00261, 0.00265, 0.00243, 0.00308, 0.00258, 0.00264, 0.00276, 0.00295, 0.00286, 0.00282, 0.00262],
[0.00263, 0.00288, 0.00284, 0.00301, 0.00271, 0.00269, 0.00275, 0.00289, 0.00276, 0.00302, 0.00280, 0.00279, 0.00281, 0.00309, 0.00263, 0.00307, 0.00276, 0.00251, 0.00400, 0.00296, 0.00406, 0.00299, 0.00298, 0.00293, 0.00265, 0.00267, 0.00274, 0.00250, 0.00252, 0.00273]
]

M_200 = [
[0.01499, 0.01672, 0.01857, 0.01435, 0.01432, 0.01436, 0.01419, 0.01474, 0.01864, 0.01390, 0.01431, 0.01409, 0.01430, 0.01425, 0.01389, 0.01417, 0.01461, 0.01439, 0.01404, 0.01386, 0.01581, 0.01505, 0.02021, 0.01423, 0.01430, 0.01394, 0.01434, 0.01533, 0.01472, 0.01433],
[0.01399, 0.01390, 0.01341, 0.01519, 0.01568, 0.01644, 0.01368, 0.01399, 0.01398, 0.01348, 0.01411, 0.01384, 0.01162, 0.01536, 0.01391, 0.01219, 0.01299, 0.01481, 0.01838, 0.01319, 0.01624, 0.01640, 0.01094, 0.01377, 0.01489, 0.01491, 0.01341, 0.01439, 0.01095, 0.01413],
[0.01275, 0.01338, 0.01180, 0.01175, 0.01234, 0.01234, 0.01158, 0.01176, 0.01267, 0.01268, 0.01182, 0.01266, 0.01436, 0.01873, 0.01200, 0.01331, 0.01166, 0.01515, 0.01193, 0.01314, 0.01179, 0.01175, 0.01161, 0.01170, 0.01325, 0.01155, 0.01336, 0.01257, 0.01267, 0.01166],
[0.01089, 0.01231, 0.01220, 0.01445, 0.01991, 0.01677, 0.01827, 0.02162, 0.01380, 0.01733, 0.01855, 0.02364, 0.02027, 0.01883, 0.01320, 0.01830, 0.01672, 0.01513, 0.01945, 0.01100, 0.01328, 0.01409, 0.01319, 0.01150, 0.01355, 0.01316, 0.01193, 0.01247, 0.01477, 0.01625],
[0.01246, 0.01189, 0.01302, 0.01353, 0.01227, 0.01208, 0.01231, 0.01303, 0.01320, 0.01404, 0.01353, 0.01332, 0.01247, 0.01437, 0.01310, 0.01412, 0.01269, 0.01196, 0.01221, 0.01321, 0.01302, 0.01255, 0.01388, 0.01248, 0.01256, 0.01203, 0.01172, 0.01313, 0.01298, 0.01192],
[0.01438, 0.01249, 0.01184, 0.01195, 0.01201, 0.01775, 0.01395, 0.01189, 0.01417, 0.01502, 0.01494, 0.01162, 0.01376, 0.01142, 0.01462, 0.01501, 0.01131, 0.01190, 0.01526, 0.01345, 0.01490, 0.01218, 0.01328, 0.01330, 0.01325, 0.01198, 0.01324, 0.01290, 0.01546, 0.01569],
[0.01678, 0.02422, 0.01726, 0.01727, 0.01485, 0.01565, 0.01836, 0.01690, 0.02016, 0.01639, 0.01545, 0.01564, 0.01274, 0.01447, 0.01469, 0.02272, 0.01402, 0.01127, 0.01144, 0.01367, 0.01207, 0.01735, 0.01431, 0.01072, 0.01066, 0.01137, 0.01075, 0.01074, 0.01286, 0.01300]
]

M_300 = [
[0.04810, 0.04858, 0.03879, 0.04525, 0.03899, 0.04792, 0.04057, 0.04318, 0.04148, 0.04186, 0.04568, 0.04174, 0.04613, 0.05626, 0.05580, 0.04123, 0.04534, 0.04068, 0.04185, 0.04496, 0.05200, 0.04144, 0.04330, 0.04092, 0.04043, 0.03894, 0.04444, 0.06474, 0.04602, 0.04390],
[0.03873, 0.03996, 0.03811, 0.04317, 0.03945, 0.03951, 0.06310, 0.06469, 0.03796, 0.03962, 0.03955, 0.04170, 0.03603, 0.03570, 0.04174, 0.04177, 0.03395, 0.04342, 0.03843, 0.03168, 0.03872, 0.04161, 0.02959, 0.04386, 0.03927, 0.03580, 0.03222, 0.03357, 0.03148, 0.03332],
[0.03217, 0.03690, 0.03526, 0.03533, 0.03283, 0.03659, 0.03417, 0.03482, 0.03145, 0.03345, 0.03435, 0.03512, 0.04155, 0.03863, 0.03435, 0.03538, 0.03309, 0.03287, 0.03342, 0.05985, 0.03533, 0.03590, 0.03710, 0.03506, 0.03254, 0.04242, 0.03278, 0.03355, 0.03708, 0.03630],
[0.04374, 0.03183, 0.03026, 0.03104, 0.02987, 0.03713, 0.04035, 0.03634, 0.03137, 0.03049, 0.03226, 0.02927, 0.03565, 0.03168, 0.02910, 0.02935, 0.03584, 0.05065, 0.05848, 0.06260, 0.05034, 0.03272, 0.03855, 0.03175, 0.03051, 0.03398, 0.03213, 0.03050, 0.03446, 0.03475],
[0.03209, 0.03033, 0.03331, 0.03177, 0.03243, 0.03017, 0.03659, 0.04462, 0.04368, 0.03534, 0.03599, 0.03516, 0.03816, 0.03271, 0.03142, 0.03238, 0.03462, 0.03200, 0.03078, 0.03199, 0.03484, 0.03207, 0.03770, 0.03238, 0.03235, 0.03348, 0.03238, 0.03277, 0.03711, 0.03192],
[0.03296, 0.02954, 0.03205, 0.03131, 0.03272, 0.03320, 0.03001, 0.03433, 0.03041, 0.03510, 0.03322, 0.03144, 0.03235, 0.02988, 0.03543, 0.03178, 0.03016, 0.03014, 0.03241, 0.03371, 0.03304, 0.03243, 0.03206, 0.03074, 0.03526, 0.03643, 0.03175, 0.03264, 0.03196, 0.03133],
[0.03351, 0.03151, 0.03034, 0.03286, 0.03115, 0.03066, 0.03428, 0.03281, 0.03219, 0.03076, 0.03186, 0.03164, 0.03259, 0.03455, 0.03383, 0.03167, 0.03113, 0.03136, 0.03312, 0.03028, 0.03255, 0.03374, 0.03207, 0.03419, 0.03834, 0.03047, 0.03493, 0.03623, 0.05112, 0.03751]
]

M_500 = [
[0.20272, 0.19774, 0.19119, 0.19551, 0.22616, 0.18636, 0.20510, 0.21883, 0.20564, 0.19235, 0.18521, 0.18121, 0.18302, 0.23956, 0.24638, 0.21942, 0.22472, 0.19062, 0.22105, 0.18650, 0.18633, 0.18543, 0.19252, 0.20737, 0.19584, 0.19692, 0.18255, 0.18861, 0.18405, 0.18863],
[0.14376, 0.13503, 0.13109, 0.13482, 0.13135, 0.13057, 0.13301, 0.13496, 0.14073, 0.14266, 0.18775, 0.18449, 0.13548, 0.17668, 0.16177, 0.15908, 0.15502, 0.14347, 0.16915, 0.11904, 0.16074, 0.14781, 0.14232, 0.17191, 0.14288, 0.16712, 0.14849, 0.12611, 0.17598, 0.14463],
[0.13297, 0.13477, 0.12935, 0.13051, 0.13271, 0.13568, 0.14199, 0.14231, 0.12479, 0.13715, 0.14262, 0.14256, 0.14523, 0.12954, 0.12624, 0.13172, 0.13215, 0.13689, 0.14013, 0.12593, 0.13520, 0.13629, 0.15238, 0.15017, 0.15205, 0.13883, 0.12776, 0.14146, 0.12996, 0.13973],
[0.12025, 0.13167, 0.13204, 0.13438, 0.12908, 0.15515, 0.12931, 0.12368, 0.13606, 0.13507, 0.12733, 0.12662, 0.12972, 0.12877, 0.14166, 0.12794, 0.14271, 0.13512, 0.12670, 0.11565, 0.12304, 0.11971, 0.13453, 0.12965, 0.12677, 0.12969, 0.12701, 0.12540, 0.12795, 0.12726],
[0.15613, 0.16209, 0.15360, 0.13167, 0.13568, 0.13201, 0.13860, 0.12481, 0.13098, 0.14163, 0.13430, 0.12594, 0.13555, 0.12269, 0.13203, 0.13300, 0.12624, 0.15154, 0.13238, 0.12967, 0.12403, 0.12951, 0.12191, 0.12974, 0.12565, 0.13756, 0.13745, 0.13222, 0.12467, 0.15058],
[0.17285, 0.17942, 0.15483, 0.12802, 0.12888, 0.12800, 0.12913, 0.12773, 0.12518, 0.13355, 0.12645, 0.11796, 0.12452, 0.14546, 0.16217, 0.12268, 0.12943, 0.12943, 0.12475, 0.12804, 0.12748, 0.11575, 0.11970, 0.12629, 0.12020, 0.13028, 0.13109, 0.12283, 0.12660, 0.11889],
[0.12523, 0.12045, 0.12926, 0.12545, 0.13212, 0.12108, 0.13437, 0.12434, 0.12133, 0.12761, 0.12287, 0.12404, 0.12891, 0.12420, 0.12244, 0.12489, 0.12919, 0.11963, 0.12672, 0.12429, 0.12069, 0.12740, 0.12019, 0.12882, 0.12810, 0.12355, 0.12798, 0.12213, 0.11975, 0.11751]
]

M_700 = [
[0.50599, 0.50035, 0.52189, 0.51072, 0.51334, 0.50071, 0.50008, 0.51779, 0.53589, 0.51226, 0.50308, 0.49437, 0.49853, 0.50738, 0.50648, 0.49873, 0.52744, 0.50535, 0.49778, 0.50103, 0.49422, 0.51209, 0.48149, 0.49989, 0.48332, 0.50816, 0.48555, 0.50458, 0.49289, 0.50065],
[0.66858, 0.31715, 0.39466, 1.12253, 0.46445, 0.31349, 0.50880, 0.43569, 0.43146, 0.61019, 0.33181, 0.43612, 0.30131, 0.31741, 0.30959, 0.30199, 0.31076, 0.31091, 0.42805, 0.40978, 0.30444, 0.30846, 0.43219, 0.31252, 0.36527, 0.46540, 0.38631, 0.33409, 0.42519, 0.36247],
[0.79209, 0.52725, 0.68368, 0.53664, 0.76215, 0.48141, 0.45380, 0.42373, 0.87318, 0.39987, 0.97654, 0.46952, 0.43125, 0.45433, 0.48342, 0.38436, 0.48596, 1.33286, 0.44590, 0.77621, 0.66081, 0.47690, 0.48092, 0.99313, 0.38355, 0.74878, 0.61675, 0.38655, 0.47809, 0.60796],
[1.03025, 1.20466, 1.18609, 0.98738, 1.11099, 1.16011, 1.04222, 0.98957, 1.13286, 1.22094, 1.20952, 1.00256, 1.07001, 0.90513, 1.07107, 1.21500, 0.91594, 1.03868, 0.98632, 1.06875, 1.15672, 1.24906, 1.23310, 1.21399, 1.04765, 1.09311, 1.00262, 1.12706, 1.19080, 1.07535],
[1.13150, 1.11821, 1.10504, 1.23529, 1.15559, 1.15701, 1.12030, 1.17770, 1.14988, 1.08139, 1.24016, 0.87912, 1.04312, 0.93523, 1.05619, 1.07930, 1.16606, 1.01478, 1.17515, 1.14672, 1.05466, 0.97332, 1.28628, 1.16322, 1.19011, 1.17151, 1.28145, 0.94233, 1.05316, 1.17483],
[0.88757, 0.94167, 1.16338, 1.08701, 1.07444, 1.08975, 1.11872, 1.31959, 1.22270, 1.03496, 1.24664, 1.19713, 1.09974, 1.03923, 1.11999, 1.20301, 1.08260, 1.21385, 1.15281, 1.21600, 1.21387, 1.12558, 1.01247, 1.06148, 1.14370, 1.09396, 1.10923, 1.17402, 1.00829, 1.08274],
[1.13763, 1.14641, 1.06084, 1.08024, 0.86554, 1.23601, 1.21981, 1.21542, 1.18525, 1.15623, 1.00918, 1.08067, 1.04188, 1.14495, 0.98650, 1.11770, 1.02818, 0.99532, 1.07922, 0.99062, 1.15959, 1.23108, 1.13891, 0.99994, 1.15413, 1.07329, 0.94924, 1.10728, 1.11268, 0.94372]
]


mediaM_100 = []
stdM_100 = []
mediaM_200 = []
stdM_200 = []

mediaM_300 = []
stdM_300 = []
mediaM_500 = []
stdM_500 = []

mediaM_700 = []
stdM_700 = []

for i in range(7):
	mediaM_100.append(np.mean(M_100[i]))
	stdM_100.append(np.std(M_100[i]))
	mediaM_200.append(np.mean(M_200[i]))
	stdM_200.append(np.std(M_200[i]))

	mediaM_300.append(np.mean(M_300[i]))
	stdM_300.append(np.std(M_300[i]))
	mediaM_500.append(np.mean(M_500[i]))
	stdM_500.append(np.std(M_500[i]))

	mediaM_700.append(np.mean(M_700[i]))
	stdM_700.append(np.std(M_700[i]))

fig = plt.figure(figsize=(10,5))
ax1 = fig.add_subplot(111)


## Média e desvio padrão ##

plt.errorbar(np.array(range(len(mediaM_100)))*2, mediaM_100, stdM_100,label=r'Matriz 100', color='#1F77B4', fmt='o', lw=1, capsize=4, markersize=8, markeredgecolor='#1F77B4', markerfacecolor='#8FBBD9')
plt.plot(np.array(range(len(mediaM_100)))*2, mediaM_100, color='#1F77B4',lw=2)

plt.errorbar(np.array(range(len(mediaM_200)))*2, mediaM_200, stdM_200,label=r'Matriz 200', color='#D62728', fmt='s', lw=1, capsize=4, markersize=8, markeredgecolor='#D62728', markerfacecolor='#EA9393')
plt.plot(np.array(range(len(mediaM_200)))*2, mediaM_200, color='#D62728',lw=2)


plt.errorbar(np.array(range(len(mediaM_300)))*2, mediaM_300, stdM_300,label=r'Matriz 300', color='#2CA02C', fmt='v', lw=1, capsize=4, markersize=8, markeredgecolor='#2CA02C', markerfacecolor='#95CF95')
plt.plot(np.array(range(len(mediaM_300)))*2, mediaM_300, color='#2CA02C',lw=2)

plt.errorbar(np.array(range(len(mediaM_500)))*2, mediaM_500, stdM_500,label=r'Matriz 500', color='#FF7F0E', fmt='D', lw=1, capsize=4, markersize=8, markeredgecolor='#FF7F0E', markerfacecolor='#FFBF86')
plt.plot(np.array(range(len(mediaM_500)))*2, mediaM_500, color='#FF7F0E',lw=2)

plt.errorbar(np.array(range(len(mediaM_700)))*2, mediaM_700, stdM_700,label=r'Matriz 700', color='#B20EFF', fmt='x', lw=1, capsize=4, markersize=8, markeredgecolor='#B20EFF', markerfacecolor='#B20EFF')
plt.plot(np.array(range(len(mediaM_700)))*2, mediaM_700, color='#B20EFF',lw=2)




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
