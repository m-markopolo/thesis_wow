import matplotlib.pyplot as plt
import numpy as np

Iav = np.loadtxt("results/Iav.txt", delimiter =',')
Iav_prime = np.loadtxt("results/Iav_prime.txt", delimiter =',')
pmax = np.loadtxt("results/pmax.txt", delimiter =',')

print(Iav)
print(Iav_prime)
p_val = [ 0.2, 0.3, 0.4, 0.5,  0.55, 0.56, 0.57, 0.585, 0.58, 0.59, 0.595, 0.6, 0.61, 0.615, 0.62, 0.625, 0.63,  0.64, 0.65, 0.7, 0.8 ] 

p_close = [ 0.55, 0.56, 0.57, 0.58, 0.59, 0.6, 0.61, 0.62, 0.63,  0.64, 0.65 ]

p_c = 0.59
p_p = p_val[6:9]
p_m = p_val[10:15]

Iav_p = Iav[6:9]
pmax_p = pmax[6:9]
pmax_m = pmax[11:14]

Iav_m= Iav_prime[10:15]
Iavp_p= Iav_prime[6:9]

p_p = np.array(p_p)
p_m = np.array(p_m)

dp_m = abs(p_m - p_c)
dp_p = abs(p_p - p_c)

'''
#a_p, b_p = np.polyfit(np.log(dp_p), np.log(Iavp_p), 1)
#a_p, b_p = np.polyfit(np.log(dp_p), np.log(Iav_p), 1)
a_p, b_p = np.polyfit(np.log(dp_p), np.log(Iav_p), 1)
plt.plot(np.log(dp_m), np.log(Iav_m))
plt.plot(np.log(dp_p), np.log(Iavp_p))
plt.plot(np.log(dp_p), a_p * np.log(dp_p) + b_p )
'''

print(len(p_val))
print(len(Iav))
#plt.plot( p_val, Iav ) 
#print(a_p, b_p)
#print(43/18)


plt1 = plt.plot(p_val, Iav_prime, label='Iav_prime' ) 
plt.show()
plt2 = plt.plot(p_val, pmax, label='pmax' ) 
plt.show()
plt3 = plt.plot(p_val, Iav, label='Iav' ) 

plt.show()
