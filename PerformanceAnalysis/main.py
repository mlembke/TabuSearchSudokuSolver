import numpy as np
import matplotlib.pyplot as plt

def plot_histograms(data):
	tabu_list_lengths = np.unique(data[:, 0])
	tabu_list_fixed = np.unique(data[:, 1])
	print(data[:, 0])
	print(data[0, :])
	f, ax_arr = plt.subplots(np.size(tabu_list_lengths), np.size(tabu_list_fixed))
	l_idx = 0
	f_idx = 0
	for idx, ax in enumerate(ax_arr.ravel()):
			ax.hist(data[:, ])
def main():
	test_data = np.array([[10, 20, 34],
					 [10, 20, 28],
					 [10, 20, 36],

					 [10, 30, 24],
					 [10, 30, 32],
					 [10, 30, 33],

					 [10, 40, 18],
					 [10, 40, 24],
					 [10, 20, 30],

					 [9, 20, 36],
					 [9, 20, 29],
					 [9, 20, 37],

					 [9, 30, 25],
					 [9, 30, 33],
					 [9, 30, 35],

					 [9, 40, 19],
					 [9, 40, 26],
					 [9, 20, 32]])
	plot_histograms(test_data)
	#file_name = 'results.txt'
	#raw_data = np.loadtxt(file_name)
	## data [tabuListLength, fixedFields, iterationCount]
	#tabuListLength = np.unique(raw_data[:, 0])
	#print(tabuListLength)

	#n = np.shape(raw_data)[0]
	#data = np.zeros((n/m, 2))
	#for i in range(0, n, m):
	#	data[i / m, 1] = np.mean(raw_data[i:i+m, 0])
	#	data[i / m, 0] = np.mean(raw_data[i:i+m, 1])
	#plt.plot(data[:, 0], data[:, 1])
	#plt.show()
			

if __name__ == '__main__':
	main()