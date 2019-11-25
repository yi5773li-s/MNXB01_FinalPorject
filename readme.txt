Final project repository for group E.


Environment setups:

  ROOT version: 6.18

  Python version: 3.7.4
  Numpy 1.17.2
  Pandas 0.25.1


Reasons to use the softwares listed above:

  ROOT -- used for data analysis and visualization
  Python -- used for data cleaning
  Numpy -- used for processing the data arrays
  Pandas -- used for load the raw data into Python


To reproduce the result:

  Please compile /project/project.C in root using the command .L project.C+

  there are 7 functions that can be called:

  oneDayMDI(filePath, month, day, plot=0) has inputs:
  filepath in the form "../clean_data/lund_clean.dat" for any data file in the clean_data folder.
  month and day are the month and day of the desired analysis.
  plot is whether you want a plot or not, 1 for plot 0 for no plot (gives pointer to array containing mean and standard deviation of distribution).
  eg. oneDayMDI("../clean_data/lund_clean.dat", 1, 1, 1)

  oneDay(filePath, dayNo, plot=0) has inputs:
  filepath in the form "../clean_data/lund_clean.dat" for any data file in the clean_data folder.
  dayNo is the integer value of the day number of the date of the desired analysis.
  plot works the same as above.
  eg. oneDay("../clean_data/lund_clean.dat", 275, 1)

  oneDayProb(filePath, month, day, temp, errorRange) has inputs:
  filepath in the form "../clean_data/lund_clean.dat" for any data file in the clean_data folder.
  month and day are the month and day of the desired analysis.
  temp is the mean temperature of the desired analysis.
  errorRange is the desired range of error allowed for testing the probability
  eg. oneDayProb("../clean_data/lund_clean.dat", 1, 1, 20, 5)

  WarmColdDay(loc) has the input:
  loc in the form "uppsala" and works for any of the locations with cleaned data (lund, lulea, umea, uppsala, visby)
  eg. WarmColdDay("uppsala")

  everyDay(filePath) has the input:
  filepath in the form "../clean_data/uppsala_clean.dat" for any data file in the clean_data folder.
  eg. everyDay("../clean_data/uppsala_clean.dat")

  void LattDiff() has no inputs
  eg. LattDiff()
  Important Note this function has efficiancy issues and for us has taken anywhere between 20mins to 1hour to complete

  getTemperature(loc) has the input:
  loc in the form "lund" and works for all data provided (lund, boras, falsterbo, falun, karlstad, lulea, soderarm, umea, uppsala, visby)
  eg. getTemperature("lund")
