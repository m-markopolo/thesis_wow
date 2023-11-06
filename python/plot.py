import matplotlib.pyplot as plt
import numpy as np

Iav = np.loadtxt("results/Iav.txt", delimiter =',')
Iav_prime = np.loadtxt("results/Iav_prime.txt", delimiter =',')
pmax = np.loadtxt("results/pmax.txt", delimiter =',')

print(Iav)
print(Iav_prime)
p_val = np.loadtxt("data/probability_values.txt", delimiter =',')




plt1 = plt.plot(p_val, Iav_prime)
plt.title("Iav_prime")
plt.show()

plt3 = plt.plot(p_val, Iav)
plt.title("Iav")
plt.show()

plt2 = plt.plot(p_val, pmax)
plt.title("pmax")
plt.show()
