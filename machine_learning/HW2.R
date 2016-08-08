# DIVYA NAIR
# STAT 6650 HW2

train = read.table("train.txt")
test = read.table("test.txt")

summary(train)
summary(test)

dim(train)
dim(test)

train = as.matrix(train)
test = as.matrix(test)

# subset predictor variables
trainx = train[ ,-101]
testx = test[ ,-101]

# subset the response variable
trainy = train[ ,101]
testy = test[ ,101]

# create RMSE variable
rmseTrain = rep(0, 100)
rmseTest = rep(0, 100)

for(i in 1:100) {
	traini = data.frame(x = train[ ,1:i], y = trainy)
	# regress y onto the first i columns of x, i=1,...,100
	linReg = lm(y ~ ., data = traini)
	# residual mean squared error on training set
	rmseTrain[i] = sqrt(mean(linReg$residual^2))
	# predict y for test set using linear models from training set
	p = predict(linReg, newdata = data.frame(x = test[ ,1:i]))
	# residual mean squared error on test set
	rmseTest[i] = sqrt(sum((p - testy)^2) / length(p))
}

# 10-fold cross-validation on training set
x = as.matrix(trainx)
y = train[ ,101]

source("tenFold.R")
cv = tenfold(x, y)
rmseCV = sqrt(cv$mse)

pdf("rmse_plots.pdf")
# green: RMSE for training set
plot(rmseTrain, type = "l", col = "green", ylim = c(0.9,1.2), 
	 ylab = "Residual Mean Squared Error (RMSE)", 
	 xlab = "Number of Predictor Variables")
# red: RMSE for 10-fold cross validation
lines(1:100, rmseCV, col = "red")
# blue: RMSE for testing set
lines(1:100, rmseTest, col = "blue")
# position and text of legend
legend("topright", legend = c("Train RMSE", "X-validation RMSE", "Test RMSE"),
       text.col = c("green", "red", "blue"))
dev.off()
