import numpy as np
from scipy import linalg

# Linear regression algorithm: find the best linear fit to the data
# Reference: slide 17 in http://work.caltech.edu/slides/slides03.pdf
# ------------------------------------------------------------------

x = np.vander([2, 3, 4], 3, increasing = True)  # input matrix (vandermonde)
w = np.array([5, 10, 15])  # weight vector
y =  np.dot(x, w)  # output vector


# 1. obtain linear fit by using the existing pseudo-inverse function

xinv = linalg.pinv(x)  # calculate pseudo-inverse of x
np.dot(xinv, y)  # since y = Xw, w = xinv * y
w

# 2. obtain linear fit by calculating the pseudo-inverse of x via SVD: 
# let the SVD of x be x = u * s * v.transpose, then the pseudo-inverse of x is xinv = v * s.inverse * u.transpose

u, s, vT = linalg.svd(x)  # SVD of x
s = np.diag(s)  # convert s to diagonal matrix
temp = np.dot(vT.transpose(), linalg.inv(s))  # v * s.inverse
np.dot(temp, u.transpose())  # v * s.inverse * u.transpose
xinv
