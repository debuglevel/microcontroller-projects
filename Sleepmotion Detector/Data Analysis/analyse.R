#!/usr/bin/r -i
print("Analysing using R...")

#install.packages("tidyverse")
library(tidyverse)

print("Reading from stdin....")
csv <- readLines()

print("Reading as CSV...")
df <- read_csv(I(csv))

print("Processing...")
print(summary(df))

#fsizes <- as.integer(readLines())
#print(summary(fsizes))
#stem(fsizes)
