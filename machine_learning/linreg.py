import numpy as np

# Linear regression algorithm: find the best linear fit to the data
# Reference: slide 17 in http://work.caltech.edu/slides/slides03.pdf
# ------------------------------------------------------------------

x = np.vander([2, 3, 4], 3, increasing = True)  # input matrix (vandermonde)
w = np.array([5, 10, 15])  # weight vector
y =  np.dot(x, w)  # output vector


# 1. obtain linear fit by using the existing pseudo-inverse function

xinv = np.linalg.pinv(x)  # calculate pseudo-inverse of x
np.dot(xinv, y)  # since y = Xw, w = xinv * y
w


# 2. obtain linear fit by calculating the pseudo-inverse of x via SVD: 
# let the SVD of x be x = u * s * v.transpose, then the pseudo-inverse of x is xinv = v * s.inverse * u.transpose

u, s, vT = np.linalg.svd(x)  # SVD of x
s = np.diag(s)  # convert s to diagonal matrix
temp = np.dot(vT.transpose(), np.linalg.inv(s))  # v * s.inverse
np.dot(temp, u.transpose())  # v * s.inverse * u.transpose
xinv


# 3. calculate SVD of x from scratch

xxT = np.dot(x, x.transpose())  # x * x.transpose
u = np.linalg.eig(xxT)[1]  # u is eigenvectors of x * x.transpose
s = np.sqrt(np.linalg.eig(xxT)[0])  # s is square root of eigenvalues of x * x.transpose or x.transpose * x
s = np.diag(s)  # convert s to diagonal matrix

xTx = np.dot(x.transpose(), x)  # x.transpose * x
v = np.linalg.eig(xTx)[1]  # v is eigenvectors of x.transpose * x

temp = np.dot(u, s)
np.dot(temp, v.transpose())  # x = u * s * v.transpose
