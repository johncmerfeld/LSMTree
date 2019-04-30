library(data.table)
library(ggplot2)

data <- fread("results.csv")

ggplot(data,
       aes(x = memrun_size,
           y = insertion_time_millisecs / 1000)) +
  geom_point(size = 5) + 
  geom_line() +
  xlab("Number of entries in the memory run") + 
  ylab("Time (s)") +
  ggtitle("Larger memory runs improve write performance")

ggplot(data,
       aes(x = memrun_size,
           y = gets_millisecs / 1000)) +
  geom_point(size = 5) + 
  geom_line() +
  xlab("Number of entries in the memory run") + 
  ylab("Time (s)") +
  ggtitle("The relationship between run size and read performance is less clear")