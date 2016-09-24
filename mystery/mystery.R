# response (1st column): categorical, predictors: 1st 9 continuous, rest categorical
myst = read.table("mystery.txt", colClasses = "factor")
myst[ ,c(2:10)] = sapply(myst[ ,c(2:10)], as.numeric)
sapply(myst, class)

dim(myst)
set.seed(12345)

# obtain train and test set. Column 29 is dropped since they don't have enough
# variation with only one value to predict the response.
intrain = sample(1:nrow(myst), 9000)
train = myst[intrain, -29]
test = myst[-intrain, -29]

# remove the response variable / only keep predictor variables
testx = test[ ,-1]
trainx = train[ ,-1]

testy = test[ ,1]
trainy = train[ ,1]

# Linear Discriminant Analysis (Reference James: page 163) #
# -------------------------------------------------------- #

library(MASS) # used to fit a LDA model

fitLda = lda(trainy ~ ., data = trainx)
fitLda # by default, prior probabilities are class proportions for train data

# predict on predictors in test set with the fitted model
predLda = predict(fitLda, newdata = testx)$class

# average FALSE values over all TRUE/FALSE values to obtain the test error/generalization error
gerrorLda = mean(predLda != testy)
gerrorLda

# obtain train error / resubstitution error
trainPred = predict(fitLda, newdata = trainx)$class
rerrorLda = mean(trainPred != trainy)
rerrorLda

# compare actual classes (columns) with predicted classes (rows) / confusion matrix
table(predLda, testy)

# MULTICLASS LOGISTIC REGRESSION (using neural networks) #
# ------------------------------------------------------ #

# install.packages("nnet")
library(nnet)

fitLog = multinom(trainy ~ ., data = trainx) 
fitLog # default tuning parameter: decay = 0

predLog = predict(fitLog, newdata = testx)

gerrorLog = mean(predLog != testy)
gerrorLog

trainPred = predict(fitLog, newdata = trainx)
rerrorLog = mean(trainPred != trainy)
rerrorLog

table(predLog, testy)

# CLASSIFICATION TREE (Reference James: page 329) #
# ----------------------------------------------- #

# install.packages("rpart")
# install.packages("rpart.plot")
library(rpart)
library(rpart.plot)

# default tuning parameter: cp = cross-validation
fitTree = rpart(trainy ~ ., data = trainx, method = "class")

predTree = predict(fitTree, newdata = testx, type = "class")

gerrorTree = mean(predTree != testy)
gerrorTree

trainPred = predict(fitTree, newdata = trainx, type = "class")
rerrorTree = mean(trainPred != trainy)
rerrorTree

table(predTree, testy)

# BAGGING (Reference James: page 333) #
# ----------------------------------- #

# install.packages("randomForest")
library(randomForest)

fitBag = randomForest(trainx, trainy, mtry = ncol(train)-1, ntree = 500)
fitBag

predBag = predict(fitBag, newdata = testx, type = "class")

gerrorBag = mean(predBag != testy)
gerrorBag

trainPred = predict(fitBag, newdata = trainx, type = "class")
rerrorBag = mean(trainPred != trainy)
rerrorBag

table(predBag, testy)

# RANDOM FOREST (Reference James: page 334) #
# ----------------------------------------- #

# install.packages("randomForest")
library(randomForest)

fitForest = randomForest(trainx, trainy, ntree = 500)
fitForest # default tuning parameter: mtry = sqrt(number of predictors)

predForest = predict(fitForest, newdata = testx, type = "class")

gerrorForest = mean(predForest != testy)
gerrorForest

trainPred = predict(fitForest, newdata = trainx, type = "class")
rerrorForest = mean(trainPred != trainy)
rerrorForest

table(predForest, testy)

# SUPPORT VECTOR MACHINES (Radial Basis kernel "Gaussian") #
# -------------------------------------------------------- #

# install.packages("kernlab")
library(kernlab)

fitRbf = ksvm(trainy ~ ., data = trainx, kernel = "rbfdot")
fitRbf

predRbf = predict(fitRbf, newdata = testx)

gerrorRbf = mean(predRbf != testy)
gerrorRbf

trainPred = predict(fitRbf, newdata = trainx)
rerrorRbf = mean(trainPred != trainy)
rerrorRbf

table(predRbf, testy)

# BOOSTING (Reference James: page 335) #
# ------------------------------------ #

# install.packages("gbm")
library(gbm)

# default tuning parameters: interaction.depth = 1, shrinkage = 0.001, n.trees = 100
fitBoost = gbm(trainy ~ ., data = trainx, distribution = "multinomial", n.trees = 5000,
               interaction.depth = 6, shrinkage = 0.001) 
summary(fitBoost)

predBoost = predict(fitBoost, newdata = testx, n.trees = 5000, type = "response") # gives predicted probabilities for each class
predBoost = apply(predBoost[ , ,1], 1, which.max) # gives predicted classes

gerrorBoost = mean(predBoost != as.numeric(testy))
gerrorBoost

trainPred = predict(fitBoost, newdata = trainx, n.trees = 5000, type = "response")
trainPred = apply(trainPred[ , ,1], 1, which.max)
rerrorBoost = mean(trainPred != as.numeric(trainy))
rerrorBoost

table(predBoost, testy)

# RIDGE (Reference James: page 254) #
# --------------------------------- #

library(glmnet)

ridgeTrainx = model.matrix(trainy ~ ., data = trainx)[ ,-1]
ridgeTestx = model.matrix(testy ~ ., data = testx)[ ,-1]

grid = 10 ^ seq (from = 10 , to = -2 , length = 10) # a grid of tuning parameters

# alpha = 1 fits the ridge classification model
fitRidge = glmnet(ridgeTrainx, trainy, alpha = 0, lambda = grid, family = "multinomial")

# obtain lambdas by cross validation
set.seed(1)
cvLambda = cv.glmnet(ridgeTrainx, as.numeric(trainy), alpha = 0)

# select the best lambda
bestLambda = cvLambda$lambda.min

# make prediction on test data using best lambda
predRidge = predict(fitRidge, s = bestLambda, newx = ridgeTestx, type = "response")
predRidge = apply(predRidge[ , ,1], 1, which.max)

# generalization error
gerrorRidge = mean(predRidge != testy)
gerrorRidge

# make prediction on train data using best lambda
trainPred = predict(fitRidge, s = bestLambda, newx = ridgeTrainx, type = "response")
trainPred = apply(trainPred[ , ,1], 1, which.max)

# resubstitution error
rerrorRidge = mean(trainPred != trainy)
rerrorRidge

table(predRidge, testy)

# SUPPORT VECTOR MACHINES (Laplace kernel) #
# --------------------------------------- #

# install.packages("kernlab")
library(kernlab)

fitLaplace = ksvm(trainy ~ ., data = trainx, kernel = "laplacedot", C = 15, cross = 10)
fitLaplace

predLaplace = predict(fitLaplace, newdata = testx)

gerrorLaplace = mean(predLaplace != testy)
gerrorLaplace

trainPred = predict(fitLaplace, newdata = trainx)
rerrorLaplace = mean(trainPred != trainy)
rerrorLaplace

table(predLaplace, testy)

# ERROR SUMMARY #
# ------------- #

genError = c(gerrorLda, gerrorLog, gerrorTree, gerrorBag, gerrorForest, gerrorRbf, gerrorBoost, 
             gerrorRidge, gerrorLaplace)
resubError = c(rerrorLda, rerrorLog, rerrorTree, rerrorBag, rerrorForest, rerrorRbf, rerrorBoost,
               rerrorRidge, rerrorLaplace)
error = cbind(genError, resubError)
rownames(error) = c("LDA", "Logistic", "Tree", "Bag", "Forest", "Rbfdot", "Boost", "Ridge",
                    "Laplacedot")
error

# PART 2 #
# ------ #

mystTest = read.table("mystery.txt", colClasses = "factor")
BestClassifier = function(myst = read.table("mystery.txt", colClasses = "factor"),
                          mystTest = read.table("mystery.txt", colClasses = "factor")) {
  myst[ ,c(2:10)] = sapply(myst[ ,c(2:10)], as.numeric)
  mystTest[ ,c(2:10)] = sapply(mystTest[ ,c(2:10)], as.numeric)
  
  set.seed(12345)
  library(randomForest)  
  fitBag = randomForest(myst[ ,-1], myst[ ,1], mtry = ncol(train) - 1, ntree = 500)
  predBag = predict(fitBag, newdata = mystTest, type = "class")
  return(predBag)
}
BestClassifier(myst, mystTest)
