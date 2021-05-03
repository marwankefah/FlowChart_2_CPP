# FlowChart_2_Code_For_Kids



FLowChart_2_Code For Kids is a simple CPP program ,enabling kids to draw a simple programming flowchart to represent the flow of algorithms, workflow or processes.

#  Features

  - Draw a Simple FlowChart
  - Load a FlowChart from a speicifed file
  - Run the FlowChart Drawn.
  - Debug the FlowChart Interactively
  - Export tbe flowchart to a CPP file

# Examples
## Simple FlowChart Drawn 
Toolbar include instruction & drawing set.  
![Image of Simple FlowChart](https://github.com/marwankefah/FlowChart_2_CPP/blob/master/chart1graph.PNG)
## Simple Run for FlowChart
![Image of Simple Run](https://github.com/marwankefah/FlowChart_2_CPP/blob/master/chart1run.PNG)
## Simple Txt File to Load Chart From
 ```sh
8	
start	1	373	88	
WRITE	3	315	157	"enter positive value"	
READ	11	402	229	m	
COND	13	473	315	m	GRT	0	
WRITE	15	703	285	"Wrong  again"	
OP_ASSIGN	17	173	388	m	m	MUL	m	
WRITE	19	196	473	m	
end	25	629	540	
8	
1	3	0	
3	11	0	
15	3	0	
13	15	2	
11	13	0	
13	17	1	
17	19	0	
19	25	0
 ```
### Loaded Chart
 ![Image of Simple Loaded Chart](https://github.com/marwankefah/FlowChart_2_CPP/blob/master/chart2graph.PNG)
## Simple Debug For FlowChart
 ![Image of Simple Debug](https://github.com/marwankefah/FlowChart_2_CPP/blob/master/chart3sim.PNG)
 
 
 
### Installation
Build the solution and execute .exe ,using MS studio or CMD
 ```sh
 msbuild "PT Project.sln"
  ```
