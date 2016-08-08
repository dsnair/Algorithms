
# DIVYA NAIR
# STAT 6650 HW1

## COLLEGE ##

college = read.csv("College.csv", header = TRUE, sep = "\t")

rownames(college) = college[ ,1] # values from 1st column are used to name rows
fix(college) # invokes edit on data

college = college[ ,-1] # delete 1st column
fix(college)

out = summary(college)
capture.output(out, file = "problem3.txt") # save the output in a file

pairs(college[ ,1:10], main = "Scatterplot matrix of the first ten variables")

attach(college)

plot(Outstate ~ Private, main = "Boxplot of Outstate vs Private", , xlab = "Private", ylab = "Outstate")

Elite = rep("No", nrow(college))
Elite[Top10perc > 50] = "Yes"
Elite = as.factor(Elite) # convert from class character to factor
college = data.frame(college, Elite)
summary(college)
plot(Outstate ~ Elite, main = "Boxplot of Outstate vs Elite", xlab = "Elite", ylab = "Outstate")

par(mfrow = c(2,2))
hist(Room.Board, breaks = 50, main = "Room and board cost")
hist(Personal, breaks = 35, main = "Estimated personal spending")
hist(Enroll, main = "Number of new students enrolled")
hist(Books, breaks = 20, main = "Estimated book cost")

## AUTO ##

auto = read.csv("Auto.csv", header = TRUE, sep = "\t", na.strings = "?")
auto = na.omit(auto) # remove missing values
attach(auto)

# range of all quantitative variables
max(mpg) - min(mpg)
max(displacement) - min(displacement)
max(horsepower) - min(horsepower)
max(weight) - min(weight)
max(acceleration) - min(acceleration)

summary(auto) # note the mean of all quantitative variables

sd(mpg)
sd(displacement)
sd(horsepower)
sd(weight)
sd(acceleration)

newauto = auto[-(10:85), ] # delete 10th through 85th rows
fix(newauto)

max(newauto$mpg) - min(newauto$mpg)
max(newauto$displacement) - min(newauto$displacement)
max(newauto$horsepower) - min(newauto$horsepower)
max(newauto$weight) - min(newauto$weight)
max(newauto$acceleration) - min(newauto$acceleration)

summary(newauto)

sd(newauto$mpg)
sd(newauto$displacement)
sd(newauto$horsepower)
sd(newauto$weight)
sd(newauto$acceleration)

pairs(auto[ ,1:8])

par(mfrow = c(2,2))
plot(displacement ~ weight)
plot(acceleration ~ weight)
plot(horsepower ~ weight)
plot(horsepower ~ acceleration)

par(mfrow = c(3,3))
plot(mpg ~ weight)
plot(mpg ~ displacement)
plot(mpg ~ acceleration)
plot(mpg ~ horsepower)
boxplot(mpg ~ cylinders, xlab = "cylinders", ylab = "mpg")
boxplot(mpg ~ year, xlab = "year", ylab = "mpg")
boxplot(mpg ~ origin, xlab = "origin", ylab = "mpg")
