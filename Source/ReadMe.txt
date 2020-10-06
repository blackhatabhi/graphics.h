%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%   Summary   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

This model implements a network of 100 mitral cells connected with
asynchronous inhibitory "synapses" that is meant to reproduced the
GABAergic transmission of ensembles of connected granule cells.  For
appropriate parameters of this special synapse the model generates
gamma oscillations with properties very similar to what is observed in
olfactory bulb slices (See Bathellier et al. 2006, Lagier et
al. 2007).  Mitral cells are modeled as single compartment neurons
with a small number of different voltage gated channels. Parameters
were tuned to reproduce the fast subthreshold oscillation of the
membrane potential observed experimentally (see Desmaisons et
al. 1999).
   


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%% Technical details to run the model %%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

The model is written in C++, and was compiled by an old version of the
Dev C++ software (4.9.7.0) running on Windows, which uses an old C++
library. I have observed that compilation with other more commonly
used software required few adaptations.

The main file of the code is obviously "main.cpp", but require most
(if not all) attached ".cpp" and ".h" files to be compiled.

The structure of the code is rather complex, with each current
(synaptic or voltage gated channels) implement by a variety of
different C++ classes with attached methods.  It is in fact based on
the structure of the CONICAL library (The Computational Neuroscience
Class Library http://www.strout.net/conical/) whose web page can be
consulted to get some help.  I have kept the same names for classes as
in CONICAL but with some extensions for the modified classes I have
built.

The program outputs several files some containing the parameters of
each simulation and some the results (e.g. LFP, traces of some
selected neurons, LFP and spike timing analysis etc...)

Running the code as it stands should produce in particular a
Results.txt file containing all measurements necessary to build figure
8A (Bathellier et al. J. Neurophysiol. 2006).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Edited by Brice Bathellier in May 2007
