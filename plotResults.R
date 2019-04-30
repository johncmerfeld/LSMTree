library(data.table)
library(ggplot2)
library(sqldf)
library(reshape2)

data <- fread("results.csv")

data_update <- sqldf("

SELECT 

  memrun_size,
  run_per_level,
  AVG(insertion_time_millisecs) AS write_time,
  AVG(gets_millisecs) AS read_time

FROM data
GROUP BY memrun_size, run_per_level
                     ")

mdf <- melt(data_update,
            value = "write_time",
            id = "run_per_level")

ggplot(data_update,
       aes(x = memrun_size,
           y = write_time / 1000)) +
  geom_point(size = 5,
             alpha = 0.7,
             aes(color = as.factor(run_per_level))) + 
  xlab("Number of entries in the memory run") + 
  ylab("Time (s)") +
  ggtitle("Larger memory runs improve write performance") +
  labs(color = "Runs per level")
ggplot(data_update,
       aes(x = memrun_size,
           y = read_time / 1000)) +
  geom_point(size = 5,
             alpha = 0.7,
             aes(color = as.factor(run_per_level))) + 
  xlab("Number of entries in the memory run") + 
  ylab("Time (s)") +
  ggtitle("The relationship with read performance is less clear") +
  labs(color = "Runs per level")