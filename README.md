1) login as apar@adaq3
2) cd into ~/PREX/prompt/collector
3) source ../../setup_japan.tcsh
4) create a list of run number you want to (see for example test.list)
5) run the command: ./collector -d ../results/ -l test.list (Note:replace test with your file name)
6) a root file named prexPrompt_test.root will be stored in the rootfiles directory
7) to produce plots stay in the collector directory and run ./aggregate 
8) you will be asked to enter a test part of the rootfile, enter it and hit Enter
9) a aggregate_plots_test.pdf file will be created in the plots directory.

