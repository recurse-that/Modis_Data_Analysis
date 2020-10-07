# set working directory
setwd("~/Documents/dev/Workspace/MODIS_Data_Analysis/Workspace/analyze_results_r")

#A function to read a text file and return a plot of colorized MXBI vals
#conditions of text file:
#	-NO header
#	-NO column names
#	-NO row names
#	-values separated by spaces
#colorize_grid

colorize_grid <- function(z) {
	colorize_griddf <- read.table(z)
	
	x <- 1:nrow(colorize_griddf)
	y <- 1:ncol(colorize_griddf)
	#length and width of plot equal number of columns and rows
	
	plot(y~x, ylim=rev(range(y)),type ='n', main="colorized mxbi values")
	
	colors <- c("tomato2","yellow","chartreuse1","dodgerblue") #colors
	cix <- c(rep(1,26),rep(2,25),rep(3,25),rep(4,25)) 
	#color index for converting mxvi vals
	
	for(i in x){
		for(j in y){
			polygon(c(x[i]-1,x[i],x[i],x[i]-1), c(y[j]-1,y[j]-1,y[j],y[j]), col=colors[cix[round(colorize_griddf[i,j]*100)+1]], border=NA)
		}	
	}
	legend("topright", bg=c("snow1"),legend = c("0.00-0.25","0.26-0.50","0.51-0.75","0.76-1.00"), fill = colors)
}

colorize_grid('test_file.txt')
