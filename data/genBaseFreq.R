library(rGDA)
rl <- loadPileup ('mixed_MSSA_78_ratio_0.05_B_1.bam.pileup')
outfile.freq <- 'mixed_MSSA_78_ratio_0.05_B_1.bam.basefreq.ref'
outfile.prob <- 'mixed_MSSA_78_ratio_0.05_B_1.bam.baseprob.ref'

if (file.exists(outfile.freq))
	file.remove(outfile.freq)
	
if (file.exists(outfile.prob))
	file.remove(outfile.prob)
	
for (i in 1:length(rl$read_group)) {
	if (length(rl$read_group[[i]]) == 0){
		cat('\n', file = outfile.freq, append = TRUE)
		cat('\n', file = outfile.prob, append = TRUE)
	}else {
		cur.seq <- unlist(rl$read_group[[i]])
		cur.group <- split(cur.seq, cur.seq)
		cur.freq <- sapply(cur.group, length)
		if (i==2*floor(i/2))
			cur.prob <- cur.freq / length(cur.seq)
		else
			cur.prob <- cur.freq / length(rl$read_group[[i+1]])
		for (j in 1:length(cur.freq)){
			cat(names(cur.freq)[j],':', cur.freq[j],',', file = outfile.freq, sep='', append = TRUE)
		} 
		cat('\n', file = outfile.freq, append = TRUE)
		
		for (j in 1:length(cur.prob)){
			cat(names(cur.prob)[j],':', cur.prob[j],',', file = outfile.prob, sep='', append = TRUE)
		} 
		cat('\n', file = outfile.prob, append = TRUE)
	}
	
}

