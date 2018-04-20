# Name: Matthew Huang
# Email: myh160030@utdallas.edu
# Course number: CS 3377.501

# Flags for the C implicit rules
CXX = g++
CXXFLAGS = -Wall -I /scratch/perkins/include

LDFLAGS = -L /scratch/perkins/lib
LDLIBS  = -lcdk

PROJECTNAME = CS3377.501.Program6_myh160030

EXECFILE = cs3377dirmond

# Makes the executable file:
all: $(EXECFILE)

OBJS = cs3377dirmond.o parseCmdLine.o parseConfigFile.o inotifyFunctions.o loggingFunctions.o signalHandler.o

# Removes the executable file and its objects:
clean:
	rm -f $(OBJS) *~ \#*

# cs3377dirmond is the target
$(EXECFILE):	$(OBJS)
	$(CXX) -static -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

# backup target
backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
