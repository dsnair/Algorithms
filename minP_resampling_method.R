# This R code demonstrates the minP single-step permutation resampling method described in
# Westfall-Young, 1993; Algorithm 2.5, page 47. It uses the Cochran Armitage trend test on a 2x3 
# contingency table. The results can be verified in PROC MULTTEST in SAS.

library(DescTools)
set.seed(36607)

# the data is from Example 43.1 in SAS PROC MULTTEST documentation
S1 = c(0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1)
S2 = c(1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0)
x = data.frame(S1, S2)
y = c(rep(1, 5), rep(2, 4), rep(3, 5))

B = 10
ny = length(y)
nx = length(x)

# raw/unadjusted p-value for observed/unpermuted data
rawP = sapply(1:nx, function(i) CochranArmitageTest(table(y, x[ ,i]), "increasing")$p.value)

# permutation resampling is always without replacement; Westfall-Young page 142
id = sapply(1:B, function(b) sample(1:ny, replace = F))

# permute data under H0: there is no association between y and x
permX = lapply(1:nx, function(j) sapply(1:B, function(b) x[id[ ,b], j]))

# calculate p-values for each permuted data
pvals = lapply(1:nx, function(j) sapply(1:B, function(b) CochranArmitageTest(table(y, permX[[j]][ ,b]), "increasing")$p.value))
pvals = matrix(unlist(pvals), ncol = nx)

# adjust p-values for multiplicity
minP = apply(pvals, 1, min)
adjP = sapply(1:nx, function(i) mean(minP < rawP[i]))  # minP adjusted p-value
data.frame(rawP, adjP, row.names = c("S1", "S2"))
