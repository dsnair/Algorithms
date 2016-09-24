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
