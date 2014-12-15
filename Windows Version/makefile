# CSCI 5229 Project
EXE=Project

# Main target
all: $(EXE)

#  MinGW, path defined in CFLG is the path to ODE header files on your system
#  The ode_singled.dll MUST be in the same directory as your executable!!!! Copy and paste it in there
ifeq "$(OS)" "Windows_NT"
INCL=-I"C:\Users\Russ Mehring\adt-bundle-windows-x86_64-20130522\ode-0.13\include"
CFLG=-O3 -Wall 
LIBS=-lglut32cu -lglu32 -lopengl32 -lode_singled 
LINKFLAGS=-L"C:\Users\Russ Mehring\adt-bundle-windows-x86_64-20130522\ode-0.13\lib\DebugSingleDLL" 
CLEAN=del *.exe *.o *.a
endif

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
	gcc -O3 -o $@ $^   $(LIBS) $(LINKFLAGS) $(INCL)

#  Clean
clean:
	$(CLEAN)