college = read.csv("College.csv", header = TRUE, sep = "\t")
summary(college)

# calculate the total number of applications received in the entire data
cumsum(college$Apps)[777]

# remove missing values
college = na.omit(college)

# delete university names column
college = college[ ,-1]

x = model.matrix(Apps ~ ., data = college)[ ,-1]
y = college$Apps

# 50/50 split of the data into train and test sets. Obtain indices for these sets.
set.seed(1)
train = sample(1:nrow(x),  floor(nrow(x)/2))
test = (-train)

# install.packages("pls")
library(pls)

# Principal Components Regression #

# apply PCR on training data (Reference James: page 260)
set.seed(1)
pcrFit = pcr(Apps ~ ., data = college, subset = train, scale = TRUE, validation = "CV")
summary(pcrFit)

# since CV studies 90% of the data, its test MSE estimate will be slightly worse than studying 
# the entire data. AdjCV adjusts for, so its MSE graph will be slightly under the CV MSE graph.
validationplot(pcrFit, val.type = "MSEP")

# predict on test data
pcrPred = predict(pcrFit, x[test, ], ncomp = 4)

# compute test MSE
mean((pcrPred - y[test]) ^ 2)

# Partial Least Squares #

# apply PLS on training data (Reference James: page 261)
set.seed(1)
plsFit = plsr(Apps ~ ., data = college, subset = train, scale = TRUE, validation = "CV")
summary(plsFit)
validationplot(plsFit, val.type = "MSEP")

# predict on test data
plsPred = predict(plsFit, x[test, ], ncomp = 5)

# compute test MSE
mean((plsPred - y[test]) ^ 2)

# Garrote #

# apply Garrote on training data
source("garrote.R")
source("cvGarrote.R")

svals = seq(from = 5, to = 20, length = 100)
garroteFit = garrote(x[train, ], y[train], s = svals)
names(garroteFit)

# obtain best 's' by cross-validation
set.seed(1)
cvOut = cv.garrote(x[train, ], y[train], s = svals)

s = cvOut$s
mse = cvOut$mse
se = cvOut$se
lower = mse - se
upper = mse + se
imin = which.min(mse)
minu = mse[imin] + se[imin]

plot(s, mse, pch = 20, col = "red", ylim = range(c(upper,lower)))
lines(s, lower, col = "gray")
lines(s, upper, col = "gray")
abline(h = minu, col = "red")
abline(v = s[imin], lty = 2)

cvOut$mse[imin] # smallest train MSE
s[imin] # 's' at which the smallest train MSE occurs

# re-fit the train data with the best 's'
garroteFit = garrote(x[train, ], y[train], s = s[imin])

# make prediction on test data using best 's'
garrotePred = predict.garrote(garroteFit, x[test, ])$predicted

# obtain test MSE
mean((garrotePred - y[test]) ^ 2)
