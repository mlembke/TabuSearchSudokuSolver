import numpy as np
import matplotlib.pyplot as plt

def main():
	file_name = 'results.txt'
	raw_data = np.loadtxt(file_name)
	n = np.shape(raw_data)[0]
	m = 10
	data = np.zeros((n/m, 2))
	for i in range(0, n, m):
		data[i / m, 1] = np.mean(raw_data[i:i+m, 0])
		data[i / m, 0] = np.mean(raw_data[i:i+m, 1])
	plt.plot(data[:, 0], data[:, 1])
	plt.show()
			


if __name__ == '__main__':
	main()