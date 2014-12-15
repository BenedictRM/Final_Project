# CSCI 5229 Project
EXE=Project

# Main target and ode target
all: ode $(EXE)

#  OSX, auto-loads ODE
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations -I$(PWD)/ode/bin/include
LIBS=-framework GLUT -framework OpenGL 
LDFLAGS= -L$(PWD)/ode/bin/lib -lode
else
#  Linux/Unix/Solaris, auto loads ODE
CFLG=-O3 -Wall -funroll-loops -fomit-frame-pointer -I$(PWD)/ode/bin/include
LIBS=-lglut -lGLU -lGL -lm -lode
LDFLAGS= -L$(PWD)/ode/bin/lib
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) rm -rf $(PWD)/ode/ *.o *.a 
endif

#To run, type 'make run' (On OSX or Linux command line)
run: Project
	LD_LIBRARY_PATH=$(PWD)/ode/bin/lib ./Project

#Download ode from internet into its own folder
ode:
	@echo Pulling tar file
	@wget https://bitbucket.org/odedevs/ode/downloads/ode-0.13.1.tar.gz
	@tar xzf ode-0.13.1.tar.gz
	@rm ode-0.13.1.tar.gz
	@mv ode-0.13.1/ ode/
	cd ode/; ./configure --prefix=$(PWD)/ode/bin/ --enable-double-precision --enable-shared; make; make install;

# Dependencies
5229_Project.o: 5229_Project.c 5229_Project.h
fatal.o: fatal.c 5229_Project.h
loadtexbmp.o: loadtexbmp.c 5229_Project.h
print.o: print.c 5229_Project.h
project.o: project.c 5229_Project.h
errcheck.o: errcheck.c 5229_Project.h
doorway.o: doorway.c 5229_Project.h
idle.o: idle.c 5229_Project.h
invertedPyramid.o: invertedPyramid.c 5229_Project.h
keyControl.o: keyControl.c 5229_Project.h
normal.o: normal.c 5229_Project.h
platform.o: platform.c 5229_Project.h
reshape.o: reshape.c 5229_Project.h
spin.o: spin.c 5229_Project.h
tron.o: tron.c 5229_Project.h
uprightPyramid.o: uprightPyramid.c 5229_Project.h
sphere.o: sphere.c 5229_Project.h
ode.o: ode.c 5229_Project.h
skybox.o: skybox.c 5229_Project.h
box.o: box.c 5229_Project.h
simplex.o: simplex.c 5229_Project.h
skyPanels.o: skyPanels.c 5229_Project.h
terrain.o: terrain.c 5229_Project.h
object.o: object.c 5229_Project.h
gun.o: gun.c 5229_Project.h
lightning.o: lightning.c 5229_Project.h
boxTargets.o: boxTargets.c 5229_Project.h
ships.o: ships.c 5229_Project.h

#  Create archive
Project.a:fatal.o loadtexbmp.o print.o project.o errcheck.o doorway.o idle.o invertedPyramid.o keyControl.o normal.o platform.o reshape.o spin.o tron.o uprightPyramid.o sphere.o ode.o skybox.o box.o simplex.o skyPanels.o terrain.o object.o gun.o lightning.o boxTargets.o ships.o
	ar -rcs $@ $^
	
# Compile rules
.c.o:
	gcc -c $(CFLG) $(INCL) $<
.cpp.o:
	g++ -c $(CFLG) $(INCL) $<

#  Compile and link
Project:5229_Project.c Project.a
	gcc -O3 -o $@ $^  $(CFLG) $(LIBS) $(LINKFLAGS) $(INCL) $(LDFLAGS) 

#  Clean
clean:
	$(CLEAN)
