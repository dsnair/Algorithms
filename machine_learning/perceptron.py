import numpy as np
import sklearn.linear_model.perceptron as p


# Perceptron from scratch
# Reference: slide 12 in http://work.caltech.edu/slides/slides01.pdf
# ------------------------------------------------------------------

# Data: classify grades >= 70 as passing (1) and <70 as failing (-1)
x = np.array([70, 60, 90, 40])
y = np.array([1, -1, 1, -1])

# select 4 random #s between 0 and 1 as initial weights
w = np.random.rand(4)  

# Run perceptron
for i in range(10):	
	wx = np.multiply(w, x)  # take dot product of w and x
	h = np.sign(wx)  # get the sign of dot product
	# update weight, if a misclassified point exists	
	if (np.any(h != y)):
		error = np.where((h != y) == True)
		w[error[0][0]] = w[error[0][0]] + y[error[0][0]] * x[error[0][0]]
	# check that no point is misclassified
	print(y == h)



# Perceptron from scikit-learn package
# ------------------------------------

x = np.array([[70, 1], [60, -1], [90, 1], [40, -1]])
x.shape  # dimension of x must be (# samples, # features)
y = np.array([1, -1, 1, -1])  # pass/fail labels

# perceptron
model = p.Perceptron(n_iter = 10, verbose = 0, shuffle = False)
model.fit(x, y)  # fit perceptron model to data
model.predict(x)  # make predictions
model.score(x, y)  # test the model fit; returns the mean accuracy on the given test data and labels
