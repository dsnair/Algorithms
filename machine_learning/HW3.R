# DIVYA NAIR
# STAT 6650 HW3

# QUESTION 3 #
college = read.csv("College.csv", header = TRUE, sep = "\t")
summary(college)

# remove missing values
college = na.omit(college)

# delete university names column
college = college[ ,-1]

# Part a #

# 50/50 split of the data into train and test sets
set.seed(1)
intrain = sample(1:nrow(college), floor(nrow(college)/2))
train = college[intrain, ]
test = college[-intrain, ]

# subset the response variable
trainy = train[ ,2]
testy = test[ ,2]

# subset the predictor variables
trainx = train[ ,-2]
testx = test[ ,-2]

# Part b #

# Fit a linear model on the training set
linearModel = lm(Apps ~ ., data = train)
summary(linearModel)

# predict the response variable for the test set using the above model
linearYhat = predict(linearModel, newdata = testx)

# obtain test MSE
testMse = mean((testy - linearYhat)^2 )
testMse

# Part c (Reference James: page 254, 257) #

trainx = model.matrix(Apps ~ ., data = train)[ ,-1]
trainy = train$Apps

testx = model.matrix(Apps ~ ., data = test)[ ,-1]
testy = test$Apps

# set a grid of tunning parameters lambda
grid = 10 ^ seq (from = 10 , to = -2 , length = 100)

# install.packages("glmnet")
library(glmnet)

# alpha = 0 fits the rigde regression model
ridgeModel = glmnet(trainx, trainy, alpha = 0, lambda = grid)

# obtain lambdas by cross validation
set.seed(1)
cvLambda = cv.glmnet(trainx, trainy, alpha = 0)
plot(cvLambda)

# select the best lambda
bestLambda = cvLambda$lambda.min
bestLambda

# make prediction on test data using best lambda
ridgeYhat = predict(ridgeModel, s = bestLambda, newx = testx)

# obtain test MSE
mean((testy - ridgeYhat) ^ 2)

# Part d (Reference James: page 258) #

# alpha = 1 fits the lasso regression model
lassoModel = glmnet(trainx, trainy, alpha = 1, lambda = grid)

# obtain lambdas by cross validation
set.seed(1)
cvLambda = cv.glmnet(trainx, trainy, alpha = 1)
plot(cvLambda)

# select the best lambda
bestLambda = cvLambda$lambda.min
bestLambda

# make prediction on test data using best lambda
lassoYhat = predict(lassoModel, s = bestLambda, newx = testx)

# obtain test MSE
mean((testy - lassoYhat) ^ 2)

# obtain coefficient estimates
out = glmnet(trainx, trainy, alpha = 1)
lassoCoef = predict(out, type = "coefficients", s = bestLambda)[1:16, ]

# print non-zero coefficient estimates
lassoCoef[lassoCoef != 0]

# QUESTIOIN 4 #

# part a #

# install.packages("MASS")
library(MASS)

# generate nxm data matrix. y depends on the 1st m out of p columns. x are independent multivariate normals.
getdata = function(n = 100, m = 10, p = 10, rho = 0, beta = rep(1, p) / p, signoise = 2) {
	Sigma = matrix(rho, m, m) # mxm covariance matrix with entries 0
	diag(Sigma) = 1 # change diagonal entries to 1
	x = mvrnorm(n, mu = rep(0, m), Sigma) # multivariate normals
	y = 500 + rnorm(n, sd = signoise) # 2 standard deviations
	if (p > 0) y = y + x[ ,1:p, drop = F] %*% beta
	list(x = x, y = y)
}

# generate data
data = getdata(n = 1000, m = 20, p = 10, rho = 0, beta = rep(5, 10))
data = as.data.frame(data)

# Part b #

# split the data into training and testing set
set.seed(1)
intrain = sample(1:1000, 100) 
train = data[intrain, ] # 100 obs in training set
test = data[-intrain, ] # 900 obs in testing set

# Part c (Reference James: page 248) #

# install.packages("leaps")
library(leaps)

# perform best subset selection
bsFit = regsubsets(y ~ ., data = train, nvmax = 19)
bsSummary = summary(bsFit)
bsSummary

# obtain train MSE associated to each model as p increments from 1 to 20
names(bsSummary)
trainMse = bsSummary$rss / 100

# plot train mse for each model
plot("problem4_train.pdf")
plot(trainMse, xlab = "Number of Predictors", ylab = "Train MSE")
dev.off()

# Part d #

# write a function for making predictions using the model
predict.regsubsets = function(object, newdata, id) {
	form = as.formula( object$call[[2]] )
	mat = model.matrix(form, newdata)
	coefi = coef(object, id = id)
	xvars = names(coefi)
	mat[, xvars] %*% coefi
}

# obtain test MSE for each model
testMse = rep(NA, 19)

for(i in 1:19) {
	bsYhat = predict(bsFit, test, i)
	testMse[i] = mean((bsYhat - test$y) ^ 2)
	print(testMse[i])
}

plot("problem4_test.pdf")
plot(testMse, xlab = "Number of Predictors", ylab = "Test MSE")
dev.off()

# Part e #

bestModelSize = which(testMse == min(testMse)) # return the index number for which the logical statement is true
bestModelSize

# fit to the entire data
bsFull = regsubsets(y ~ ., data, nvmax = 19)

# look at the coefficients estimates of the best model
coef(bsFull, bestModelSize)
