trait = read.csv("PCA1_data.csv", header = F)  # trait information
trait = as.vector(trait[ ,1] * 1000)
marker = read.csv("marker_data.csv", header = F)  # marker information
n = nrow(marker)
m = ncol(marker)

# step 1: initialize parameters (lecture4, slide 56)
# --------------------------------------------------
Omega0 = function(q, D) {
	mu2 = mean(trait) + sd(trait)  # mean of observed marker MM (2)
	mu1 = mean(trait)  # mean of observed marker Mm (1)
	mu0 = mean(trait) - sd(trait)  # mean of observed marker mm (0)
	var = sd(trait) ^ 2  # sample variance

	# for use in Omega1
	mu2 = rep(mu2, m)	
	mu1 = rep(mu1, m)
	mu0 = rep(mu0, m)
	var = rep(var, m)
	logLik = rep(50, m)  # log likelihood

	# allele M frequency for all 16 observed markers, i.e. prob(MM) = p or prob(Mm) = p
	p = sapply(1:m, function(i) (2 * sum(marker[ ,i] == 22) + sum(marker[ ,i] == 12) + sum(marker[ ,i] == 21))/ (2 * n))

	# slide 48 formulae applied for all 16 markers
	p11 = p * q + D  # prob(MM and AA) for each 16 observed markers
	p10 = p * (1 - q) - D  # prob(Mm and qq)
	p01 = (1 - p) * q - D  # prob(mm and Qq)
	p00 = (1 - p) * (1 - q) + D  # prob(mm and aa)

	phi = (p11 * p00) / ((p11 * p00) + (p10 * p01))  # slide 54
	oldOmega = list(mu2 = mu2, mu1 = mu1, mu0 = mu0, var = var, 
				   p11 = p11, p10 = p10, p01 = p01, p00 = p00, 
				   p = p, q = q, D = D, phi = phi, logLik = logLik)  # initial parameters
	return(oldOmega)
}

# step 2 (slide 56)
# -----------------
Omega1 = function(omega) {
	# normal density function (slide 52) for all 16 markers
	f2 = sapply(1:m, function(i) dnorm(trait, mean = omega$mu2[i], sd = sqrt(omega$var[i])))  # missing QTL genotype AA (2)
	f1 = sapply(1:m, function(i) dnorm(trait, mean = omega$mu1[i], sd = sqrt(omega$var[i])))  # missing QTL genotype Aa (1)
	f0 = sapply(1:m, function(i) dnorm(trait, mean = omega$mu0[i], sd = sqrt(omega$var[i])))  # missing QTL genotype aa (0)

	# slide 49 cell entries
	cp22 = sapply(1:m, function(i) omega$p11[i] ^ 2 / omega$p[i] ^ 2)  # prob(AA | MM)
	cp21 = sapply(1:m, function(i) (omega$p11[i] * omega$p01[i]) / (omega$p[i] * (1 - omega$p[i])))  # prob(AA | Mm)
	cp20 = sapply(1:m, function(i) omega$p01[i] ^ 2 / (1 - omega$p[i]) ^ 2)  # prob(AA | mm)
	cp12 = sapply(1:m, function(i) (2 * omega$p11[i] * omega$p10[i]) / omega$p[i] ^ 2)   # prob(MM | Aa)
	cp11 = sapply(1:m, function(i) ((omega$p11[i] * omega$p00[i]) + (omega$p10[i] * omega$p01[i])) / (omega$p[i] * (1 - omega$p[i])))  # prob(Aa | Mm)
	cp10 = sapply(1:m, function(i) (2 * omega$p01[i] * omega$p00[i]) / (1 - omega$p[i]) ^ 2) # prob(Aa | mm)
	cp02 = sapply(1:m, function(i) omega$p10[i] ^ 2 / omega$p[i] ^ 2)  # prob(aa | MM)
	cp01 = sapply(1:m, function(i) (omega$p10[i] * omega$p00[i]) / (omega$p[i] * (1 - omega$p[i])))  # prob(aa | Mm)
	cp00 = sapply(1:m, function(i) omega$p00[i] ^ 2 / (1 - omega$p[i]) ^ 2)  # prob(aa | mm)
	
	# cond. prob (small pi's) of missing QTL geno. given observed geno. (slide 49)
	pi2 = matrix( ,nrow = n, ncol = m)
	pi1 = matrix( ,nrow = n, ncol = m)
	pi0 = matrix( ,nrow = n, ncol = m)
	for (i in 1:m) {
		pi2[marker[ ,i] == 22, i] = cp22[i]
		pi2[marker[ ,i] == 11, i] = cp20[i]
		pi2[marker[ ,i] == 12 | marker[ ,i] == 21, i] = cp21[i]

		pi1[marker[ ,i] == 22, i] = cp12[i]
		pi1[marker[ ,i] == 11, i] = cp10[i]
		pi1[marker[ ,i] == 12 | marker[ ,i] == 21, i] = cp11[i]

		pi0[marker[ ,i] == 22, i] = cp02[i]
		pi0[marker[ ,i] == 11, i] = cp00[i]
		pi0[marker[ ,i] == 12 | marker[ ,i] == 21, i] = cp01[i]
	}

	# capital Pi's for all 16 markers (slide 53)
	deno = (pi2 * f2) + (pi1 * f1) + (pi0 * f0)
	logLik = sapply(1:m, function(i) sum(log(deno[ ,i])))
	Pi2 = sapply(1:m, function(i) (pi2[ ,i] * f2[ ,i]) / deno[ ,i])  # equation 1
	Pi1 = sapply(1:m, function(i) (pi1[ ,i] * f1[ ,i]) / deno[ ,i])  # equation 2
	Pi0 = sapply(1:m, function(i) (pi0[ ,i] * f0[ ,i]) / deno[ ,i])  # equation 3

	# new mu2, mu1, mu0, var for all 16 markers (slide 53)
	mu2 = sapply(1:m, function(i) sum(Pi2[ ,i] * trait) / sum(Pi2[ ,i]))  # equation 4
	mu1 = sapply(1:m, function(i) sum(Pi1[ ,i] * trait) / sum(Pi1[ ,i]))  # equation 5
	mu0 = sapply(1:m, function(i) sum(Pi0[ ,i] * trait) / sum(Pi0[ ,i]))  # equation 6
	var = sapply(1:m, function(i) sum((Pi2[ ,i] * (trait - omega$mu2[i]) ^ 2) + 
									  (Pi1[ ,i] * (trait - omega$mu1[i]) ^ 2) + 
			  						  (Pi0[ ,i] * (trait - omega$mu0[i]) ^ 2)) / n) # equation 7

	# posterior probabilities (slide 55)
	Pi22 = matrix(rep(0, n), nrow = n, ncol = m)
	Pi21 = matrix(rep(0, n), nrow = n, ncol = m)
	Pi20 = matrix(rep(0, n), nrow = n, ncol = m)
	Pi12 = matrix(rep(0, n), nrow = n, ncol = m)
	Pi11 = matrix(rep(0, n), nrow = n, ncol = m)
	Pi10 = matrix(rep(0, n), nrow = n, ncol = m)
	Pi02 = matrix(rep(0, n), nrow = n, ncol = m)
	Pi01 = matrix(rep(0, n), nrow = n, ncol = m)
	Pi00 = matrix(rep(0, n), nrow = n, ncol = m)
	for (i in 1:m) {
		Pi22[marker[ ,i] == 22, i] = Pi2[marker[ ,i] == 22, i]
		Pi21[marker[ ,i] == 12 | marker[ ,i] == 21, i] = Pi2[marker[ ,i] == 12 | marker[ ,i] == 21, i]
		Pi20[marker[ ,i] == 11, i] = Pi2[marker[ ,i] == 11, i]

		Pi12[marker[ ,i] == 22, i] = Pi1[marker[ ,i] == 22, i]		
		Pi11[marker[ ,i] == 12 | marker[ ,i] == 21, i] = Pi1[marker[ ,i] == 12 | marker[ ,i] == 21, i]
		Pi10[marker[ ,i] == 11, i] = Pi1[marker[ ,i] == 11, i]

		Pi02[marker[ ,i] == 22, i] = Pi0[marker[ ,i] == 22, i]
		Pi01[marker[ ,i] == 12 | marker[ ,i] == 21, i] = Pi0[marker[ ,i] == 12 | marker[ ,i] == 21, i]
		Pi00[marker[ ,i] == 11, i] = Pi0[marker[ ,i] == 11, i]
	}

	# new phi, p11, p10, p01, p00 (slide 54) for all 16 markers	
	phiPi11 = sapply(1:m, function(i) omega$phi[i] * Pi11[ ,i])
	phiCompPi11 = sapply(1:m, function(i) (1 - omega$phi[i]) * Pi11[ ,i])		
	p11 = sapply(1:m, function(i) (sum(2 * Pi22[ ,i] + Pi12[ ,i]) + sum(Pi21[ ,i] + phiPi11[ ,i])) / (2 * n))  # equation 8
	p10 = sapply(1:m, function(i) (sum(2 * Pi02[ ,i] + Pi12[ ,i]) + sum(Pi01[ ,i] + phiCompPi11[ ,i])) / (2 * n))  # equation 9
	p01 = sapply(1:m, function(i) (sum(2 * Pi20[ ,i] + Pi10[ ,i]) + sum(Pi21[ ,i] + phiCompPi11[ ,i])) / (2 * n))  # equation 10
	p00 = sapply(1:m, function(i) (sum(2 * Pi20[ ,i] + Pi10[ ,i]) + sum(Pi01[ ,i] + phiPi11[ ,i])) / (2 * n))  # equation 11	
	phi = (p11 * p00) / ((p11 * p00) + (p10 * p01))

	# new p, q, D (slide 48) for all 16 markers
	p = p11 + p10  
	q = p11 + p01  # frequency of allele A (missing) for QTL i.e., prob(A) = q
	D = (p11 * p00) - (p10 * p01)  # Hardy-Weinberg equilibrium

	newOmega = list(mu2 = mu2, mu1 = mu1, mu0 = mu0, var = var, 
					p11 = p11, p10 = p10, p01 = p01, p00 = p00, 
					p = p, q = q, D = D, phi = phi, logLik = logLik)  # new parameters
	return(newOmega)
}

# step 3: (slide 56)
# ------------------

# update parameters and obtain convergence for all q's
q = seq(0.1, 0.9, by = 0.1)
ConvergeOmega = function(i) {
	counter = 1
	tolerance = 10 ^ -8
	error = 10 * tolerance  # makes while() run at least once
	oldOmega = Omega0(q[i], -0.01)
	while (error > tolerance) {
		newOmega = Omega1(oldOmega)
		error = abs(oldOmega$mu2 - newOmega$mu2)
		oldOmega = newOmega
		counter = counter + 1
	}
	return(newOmega)
}
system.time({
	newOmega = lapply(1:length(q), function(i) ConvergeOmega(i))
})  # converged parameters and convergence time

# select best q for each marker
logLikDf = as.data.frame(sapply(1:length(q), function(i) newOmega[[i]]$logLik))
logLikMax = apply(logLikDf, 1, which.max)  # index of max logLik (best q) for each row/marker

# print results
# -------------

# collect all parameters (columns = q's, rows = markers)
mu2Df = as.data.frame(sapply(1:length(q), function(i) newOmega[[i]]$mu2))
mu1Df = as.data.frame(sapply(1:length(q), function(i) newOmega[[i]]$mu1))
mu0Df = as.data.frame(sapply(1:length(q), function(i) newOmega[[i]]$mu0))
varDf = as.data.frame(sapply(1:length(q), function(i) newOmega[[i]]$var))
p11Df = as.data.frame(sapply(1:length(q), function(i) newOmega[[i]]$p11))
p10Df = as.data.frame(sapply(1:length(q), function(i) newOmega[[i]]$p10))
p01Df = as.data.frame(sapply(1:length(q), function(i) newOmega[[i]]$p01))
p00Df = as.data.frame(sapply(1:length(q), function(i) newOmega[[i]]$p00))
pDf = as.data.frame(sapply(1:length(q), function(i) newOmega[[i]]$p))
qDf = as.data.frame(sapply(1:length(q), function(i) newOmega[[i]]$q))
D_Df = as.data.frame(sapply(1:length(q), function(i) newOmega[[i]]$D))

# collect parameters by best q's (rows = markers)
unique(logLikMax)
q1 = cbind("mu2" = mu2Df[ ,1], "mu1" = mu1Df[ ,1], "mu0" = mu0Df[ ,1], "var" = varDf[ ,1],
			"p11" = p11Df[ ,1], "p10" = p10Df[ ,1], "p01" = p01Df[ ,1], "p00" = p00Df[ ,1],
			"p" = pDf[ ,1], "q" = qDf[ ,1], "D" = D_Df[ ,1], "logLik" = logLikDf[ ,1])  # q = 0.1

q2 = cbind("mu2" = mu2Df[ ,2], "mu1" = mu1Df[ ,2], "mu0" = mu0Df[ ,2], "var" = varDf[ ,2],
			"p11" = p11Df[ ,2], "p10" = p10Df[ ,2], "p01" = p01Df[ ,2], "p00" = p00Df[ ,2],
			"p" = pDf[ ,2], "q" = qDf[ ,2], "D" = D_Df[ ,2], "logLik" = logLikDf[ ,2])  # q = 0.2

q7 = cbind("mu2" = mu2Df[ ,7], "mu1" = mu1Df[ ,7], "mu0" = mu0Df[ ,7], "var" = varDf[ ,7],
			"p11" = p11Df[ ,7], "p10" = p10Df[ ,7], "p01" = p01Df[ ,7], "p00" = p00Df[ ,7],
			"p" = pDf[ ,7], "q" = qDf[ ,7], "D" = D_Df[ ,7], "logLik" = logLikDf[ ,7])  # q = 0.7

q9 = cbind("mu2" = mu2Df[ ,9], "mu1" = mu1Df[ ,9], "mu0" = mu0Df[ ,9], "var" = varDf[ ,9],
			"p11" = p11Df[ ,9], "p10" = p10Df[ ,9], "p01" = p01Df[ ,9], "p00" = p00Df[ ,9],
			"p" = pDf[ ,9], "q" = qDf[ ,9], "D" = D_Df[ ,9], "logLik" = logLikDf[ ,9])  # q = 0.9

# print best q parameter values for each marker
logLikMax
results = rbind(q9[1, ], q1[2, ], q1[3, ], q2[4, ], q2[5, ], q7[6, ], q2[7, ], q1[8, ], 
				q2[9, ], q9[10, ], q9[11, ], q1[12, ], q1[13, ], q9[14, ], q9[15, ], q2[16, ])
markerID = 1:m
qInitial = sapply(1:m, function(i) q[logLikMax[i]])
results = cbind(markerID, qInitial, results)
write.csv(results, file = "EM_algorithm_results.csv")
