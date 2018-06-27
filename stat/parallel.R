# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# CONCEPT: looping #
	# Exercise 1: multiply a list of matrices with a constant matrix, 
	# 			  then calculate the trace of the resultant matrices.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# serial run-time
# ---------------
MatTrace <- function(mat1, mat2) {
	sum(diag(mat1 %*% mat2))  # trace of the matrix
}
const = matrix(1:1000000, ncol = 1000)
system.time({
	mat = lapply(1:10, function(i) i * const)
	traceList = lapply(1:10, function(i) MatTrace(mat[[i]], const))
})
traceList

# parallel run-time for forking (not available on Windows) on local host
# ----------------------------------------------------------------------
library(parallel)  # comes in base R package
cl = makeForkCluster(10)  # fork 10 identical clones of the master
system.time({
	matFork = parLapply(cl, 1:10, function(i) i * const)
	traceFork = parLapply(cl, 1:10, function(i) MatTrace(matFork[[i]], const))	
})
stopCluster(cl)  # shut down workers
traceFork

# would the program run-time be slower or faster if there are 2 workers instead of 10?
library(parallel)
cl = makeForkCluster(2)
system.time({
	matFork2 = parLapply(cl, 1:10, function(i) i * const)
	traceFork2 = mclapply(1:10, function(i) MatTrace(matFork2[[i]], const), mc.cores = 10)
		# mclapply() not available on Windows; can only be used for forking, not clustering
})
stopCluster(cl)
traceFork2

# parallel run-time for clustering on local host
# -----------------------------------------------

library(parallel)
cl = makePSOCKcluster(10)
clusterExport(cl, c("MatTrace", "const"))
system.time({
	matClust = parLapply(cl, 1:10, function(i) i * const)
	clusterExport(cl, "matClust")
	traceClust = parLapply(cl, 1:10, function(i) MatTrace(matClust[[i]], const))
})
stopCluster(cl)
traceClust

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# CONCEPT: using packages, its built-in functions, and random numbers #
	# Exercise 2 
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# serial run-time
# ---------------
library(ElemStatLearn)
#?spam
x = spam[ ,1:57]
y = spam[ ,58]
data = cbind(y, x)

set.seed(123)
inTrain = sample(1:nrow(data), 3000)
train = data[inTrain, ]
test = data[-inTrain, ]

trainX = train[ ,-1]
testX = test[ ,-1]
trainY = train[ ,1]
testY = test[ ,1]

library(randomForest)
system.time({
	fitBag = randomForest(trainX, trainY, mtry = ncol(train) - 1, ntree = 500)
	predBag = predict(fitBag, newdata = testX, type = "class")
	genError = mean(predBag != testY)
})
genError

# parallel run-time for forking on remote host
# --------------------------------------------
library(parallel)
numCores = detectCores()  # 16
cl = makeForkCluster(numCores)
clusterSetRNGStream(cl, 123)
system.time({
	fitFork = clusterCall(cl, randomForest, trainX, trainY, mtry = ncol(train) - 1, ntree = floor(500 / numCores))
	fitAll = combine(fitFork[[1]], fitFork[[2]], fitFork[[3]], fitFork[[4]], fitFork[[5]], fitFork[[6]],
					 fitFork[[7]], fitFork[[8]], fitFork[[9]], fitFork[[10]], fitFork[[11]], fitFork[[12]],
					 fitFork[[13]], fitFork[[14]], fitFork[[15]], fitFork[[16]])
	predFork = predict(fitAll, newdata = testX, type = "class")  # only accepts objects of class 'randomForest', and not 'list'
	genErrorFork = mean(predFork != testY)
})
stopCluster(cl)
genErrorFork

# parallel run-time for clustering on remote host
# -----------------------------------------------
library(parallel)
numCores = detectCores()  # 16
cl = makePSOCKcluster(numCores)
clusterSetRNGStream(cl, 123)
junk = clusterEvalQ(cl, c(library(ElemStatLearn), library(randomForest)))
clusterExport(cl, c("numCores", "data", "inTrain", "train", "test", "trainX", "trainY", "testX", "testY"))
system.time({
	#fitClust = clusterCall(cl, randomForest, trainX, trainY, mtry = ncol(train) - 1, ntree = floor(500 / numCores))
	fitClust = clusterEvalQ(cl, randomForest(trainX, trainY, mtry = ncol(train) - 1, ntree = floor(500 / numCores)))
	fit = combine(fitClust[[1]], fitClust[[2]], fitClust[[3]], fitClust[[4]], fitClust[[5]], fitClust[[6]],
				  fitClust[[7]], fitClust[[8]], fitClust[[9]], fitClust[[10]], fitClust[[11]], fitClust[[12]],
				  fitClust[[13]], fitClust[[14]], fitClust[[15]], fitClust[[16]])
	predClust = predict(fit, newdata = testX, type = "class")  # only accepts objects of class 'randomForest', and not 'list'
	genErrorClust = mean(predClust != testY)
})
stopCluster(cl)
genErrorClust

# ~~~~~~~~~~~~~~~~~~~~~~~~~
# CONCEPT: load balancing #
	# Exercise 3 
# ~~~~~~~~~~~~~~~~~~~~~~~~~
library(parallel)
cl = makeForkCluster(2)
# load balanced
system.time(clusterApplyLB(cl, 1:100000, sqrt))
# load unbalanced
system.time(clusterApply(cl, 1:100000, sqrt))
stopCluster(cl)
