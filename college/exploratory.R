college = read.csv("College.csv", header = TRUE, sep = "\t")

rownames(college) = college[ ,1] # values from 1st column are used to name rows
fix(college) # invokes edit on data

college = college[ ,-1] # delete 1st column
fix(college)

out = summary(college)
capture.output(out, file = "problem3.txt") # save the output in a file

pdf("problem4.pdf")
pairs(college[ ,1:10], main = "Scatterplot matrix of the first ten variables")
dev.off()

attach(college)

pdf("problem5_1.pdf")
plot(Outstate ~ Private, main = "Boxplot of Outstate vs Private", , xlab = "Private", ylab = "Outstate")
dev.off()

Elite = rep("No", nrow(college))
Elite[Top10perc > 50] = "Yes"
Elite = as.factor(Elite) # convert from class character to factor
college = data.frame(college, Elite)
summary(college)
pdf('problem6_1.pdf')
plot(Outstate ~ Elite, main = "Boxplot of Outstate vs Elite", xlab = "Elite", ylab = "Outstate")
dev.off()

pdf("problem7.pdf")
par(mfrow = c(2,2))
hist(Room.Board, breaks = 50, main = "Room and board cost")
hist(Personal, breaks = 35, main = "Estimated personal spending")
hist(Enroll, main = "Number of new students enrolled")
hist(Books, breaks = 20, main = "Estimated book cost")
dev.off()
Contact GitHub API Training Shop Blog About
