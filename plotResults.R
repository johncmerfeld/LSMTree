library(data.table)
library(ggplot2)

data <- fread("results.csv")

ggplot(data,
       aes(x = V1,
           y = V2)) +
  geom_point(size = 5) + 
  geom_line() +
  xlab("Size of run") + 
  ylab("Time (ms)")