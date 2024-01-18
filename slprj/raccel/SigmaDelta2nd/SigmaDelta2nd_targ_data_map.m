    function targMap = targDataMap(),

    ;%***********************
    ;% Create Parameter Map *
    ;%***********************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 1;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc paramMap
        ;%
        paramMap.nSections           = nTotSects;
        paramMap.sectIdxOffset       = sectIdxOffset;
            paramMap.sections(nTotSects) = dumSection; %prealloc
        paramMap.nTotData            = -1;

        ;%
        ;% Auto data (rtP)
        ;%
            section.nData     = 19;
            section.data(19)  = dumData; %prealloc

                    ;% rtP.Carrier_Amp
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.Carrier_Bias
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% rtP.Carrier_Freq
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% rtP.Carrier_Phase
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% rtP.Modulated_Amp
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% rtP.Modulated_Bias
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% rtP.Modulated_Freq
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 6;

                    ;% rtP.Modulated_Phase
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 7;

                    ;% rtP.Integrator1_IC
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 8;

                    ;% rtP.FIRDecimationto128MHz_FILT
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 9;

                    ;% rtP.FIRDecimationto32MHz_FILT
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 105;

                    ;% rtP.FIRDecimationto8MHz_FILT
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 201;

                    ;% rtP.Gain_Gain
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 297;

                    ;% rtP.TransportDelay_Delay
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 298;

                    ;% rtP.TransportDelay_InitOutput
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 299;

                    ;% rtP.Gain2_Gain
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 300;

                    ;% rtP.Gain1_Gain
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 301;

                    ;% rtP.Integrator_IC
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 302;

                    ;% rtP.Gain3_Gain
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 303;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section


            ;%
            ;% Non-auto Data (parameter)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        paramMap.nTotData = nTotData;



    ;%**************************
    ;% Create Block Output Map *
    ;%**************************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 1;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc sigMap
        ;%
        sigMap.nSections           = nTotSects;
        sigMap.sectIdxOffset       = sectIdxOffset;
            sigMap.sections(nTotSects) = dumSection; %prealloc
        sigMap.nTotData            = -1;

        ;%
        ;% Auto data (rtB)
        ;%
            section.nData     = 14;
            section.data(14)  = dumData; %prealloc

                    ;% rtB.lqvljim52a
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.mrrqtpofed
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% rtB.iyb4nnud3n
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% rtB.fglzwg0gpe
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% rtB.dbb1z0mm3j
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% rtB.dblm24swqm
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% rtB.bhb2jtlude
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 6;

                    ;% rtB.cecrguin1q
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 7;

                    ;% rtB.cyljhahbp4
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 8;

                    ;% rtB.koecjb54sh
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 9;

                    ;% rtB.aiuvh1nbjv
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 10;

                    ;% rtB.lu0v52hhki
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 11;

                    ;% rtB.e4dbl2cfl3
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 12;

                    ;% rtB.nwvay2kmxd
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 13;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
            clear section


            ;%
            ;% Non-auto Data (signal)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        sigMap.nTotData = nTotData;



    ;%*******************
    ;% Create DWork Map *
    ;%*******************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 4;
        sectIdxOffset = 1;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc dworkMap
        ;%
        dworkMap.nSections           = nTotSects;
        dworkMap.sectIdxOffset       = sectIdxOffset;
            dworkMap.sections(nTotSects) = dumSection; %prealloc
        dworkMap.nTotData            = -1;

        ;%
        ;% Auto data (rtDW)
        ;%
            section.nData     = 10;
            section.data(10)  = dumData; %prealloc

                    ;% rtDW.n4rivhzg4g
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.feyvwig01o
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.myljyfih4p
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 93;

                    ;% rtDW.dumfjgwxhc
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 94;

                    ;% rtDW.laliiofkj3
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 95;

                    ;% rtDW.nrjeu0zetd
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 187;

                    ;% rtDW.fqos0o4h34
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 188;

                    ;% rtDW.mku35wrylx
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 189;

                    ;% rtDW.ko2zssnvqw
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 281;

                    ;% rtDW.kly3raw3cg.modelTStart
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 282;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtDW.mypftr2o5l.LoggedData
                    section.data(1).logicalSrcIdx = 10;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.kzc2xqxsxo.TUbufferPtrs
                    section.data(2).logicalSrcIdx = 11;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section

            section.nData     = 12;
            section.data(12)  = dumData; %prealloc

                    ;% rtDW.d5k240dd1f
                    section.data(1).logicalSrcIdx = 12;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.bnlws2sh1t
                    section.data(2).logicalSrcIdx = 13;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.o5hyij1dzr
                    section.data(3).logicalSrcIdx = 14;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.eckossjxt3
                    section.data(4).logicalSrcIdx = 15;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.n0gerj2i33
                    section.data(5).logicalSrcIdx = 16;
                    section.data(5).dtTransOffset = 4;

                    ;% rtDW.bjfytdftqo
                    section.data(6).logicalSrcIdx = 17;
                    section.data(6).dtTransOffset = 5;

                    ;% rtDW.n3gfvygdda
                    section.data(7).logicalSrcIdx = 18;
                    section.data(7).dtTransOffset = 6;

                    ;% rtDW.apwo5tufnb
                    section.data(8).logicalSrcIdx = 19;
                    section.data(8).dtTransOffset = 7;

                    ;% rtDW.kurctjxgfu
                    section.data(9).logicalSrcIdx = 20;
                    section.data(9).dtTransOffset = 8;

                    ;% rtDW.gygqelpgtp
                    section.data(10).logicalSrcIdx = 21;
                    section.data(10).dtTransOffset = 9;

                    ;% rtDW.f3whwvtp2b
                    section.data(11).logicalSrcIdx = 22;
                    section.data(11).dtTransOffset = 10;

                    ;% rtDW.ld5rza5xa5
                    section.data(12).logicalSrcIdx = 23;
                    section.data(12).dtTransOffset = 11;

            nTotData = nTotData + section.nData;
            dworkMap.sections(3) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtDW.if4dnc4xux.Tail
                    section.data(1).logicalSrcIdx = 24;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.is1yc1voif
                    section.data(2).logicalSrcIdx = 25;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(4) = section;
            clear section


            ;%
            ;% Non-auto Data (dwork)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        dworkMap.nTotData = nTotData;



    ;%
    ;% Add individual maps to base struct.
    ;%

    targMap.paramMap  = paramMap;
    targMap.signalMap = sigMap;
    targMap.dworkMap  = dworkMap;

    ;%
    ;% Add checksums to base struct.
    ;%


    targMap.checksum0 = 2669508275;
    targMap.checksum1 = 3852389557;
    targMap.checksum2 = 854899528;
    targMap.checksum3 = 2228287752;

