# Name: Matthew Huang
# Email: myh160030@utdallas.edu
# Course number: CS 3377.501

# Flags for the C implicit rules
CXX = g++
CPPFLAGS = -Wall -I/scratch/perkins/include
LDFLAGS = -L /scratch/perkins/lib
LDLIBS  = -lcdk -lcurses

PROJECTNAME = CS3377.501.Program6_myh160030

EXECFILE = Program6_myh160030

# Makes the executable file:
all: $(EXECFILE)

OBJS = Program6_myh160030.o

# Removes the executable file and its objects:
clean:
	rm -f $(EXECFILE) $(OBJS) *~ \#*

# cs3377dirmond is the target
$(EXECFILE):	$(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

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
