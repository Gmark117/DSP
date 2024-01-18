clear variables;
clc;

%%
load DecFir.mat
sim = sim("SigmaDelta.slx");
signal = timeseries2timetable(sim.ERR_S01);
signalAnalyzer(signal);