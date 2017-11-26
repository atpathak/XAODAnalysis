all : plot_fit plot_all 
plot_fit: plot_fit.cc
	g++ -g -O2 -fPIC -Wno-deprecated -D__USE_XOPEN2K8 -o plot_fit plot_fit.cc `root-config --cflags --libs --ldflags` -L${ROOTSYS}/lib -lHistFactory -lXMLParser -lRooStats -lRooFit -lRooFitCore -lThread -lMinuit -lFoam -lMathMore -lHtml -lGpad -lm
plot_all: plot_all.cc
	g++ -g -O2 -fPIC -Wno-deprecated -D__USE_XOPEN2K8 -o plot_all plot_all.cc `root-config --cflags --libs --ldflags` -L${ROOTSYS}/lib -lHistFactory -lXMLParser -lRooStats -lRooFit -lRooFitCore -lThread -lMinuit -lFoam -lMathMore -lHtml -lGpad -lm
clean: 
	rm -f plot_fit plot_all
