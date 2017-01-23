classdef CAU_SpeedSensor < matlab.System & coder.ExternalDependency
    % CAU_SpeedSensor
    % ChrTPT1 := 0, turns filter off
    %
    % ===================================
    % Chair of Automatic Control
    % Christian-Albrechts University Kiel
    % Created on: Jan 27, 2016
    % Author: hewe@tf.uni-kiel.de, gefr@tf.uni-kiel.de
    
    
    % BEWARE ON INPUT CONSTRAINTS!
    
    
    properties
        SgmntWdth = 36;  % Segement width between two magnets in mm
        ElpsdTMax = 400; % Maximum elapsed time in ms before stillstand detection, [300, 800]
        ChrTPT1 = 5;    % PT1 low pass: characteristic factor in respect to the block sample time [0, 10]      
    end
    
    properties (Nontunable)
        % Select Sensor
        WhichSensor = 'Left';
    end
    properties (Hidden,Transient,Constant)
        % dropdown menu
        WhichSensorSet = matlab.system.StringSet({'Left','Right'});
    end
    properties  (Hidden, Nontunable)
        % Which Scale is used
        SensorNum = 0;
        minChrTPT1 = 0;
        maxChrTPT1 = 10;
        minElpsdTMax = 300;
        maxElpsdTMax = 800;
    end
    
    
    methods
        function obj = CAU_SpeedSensor(varargin)
            coder.allowpcode('plain');
            % Support name-value pair arguments
            setProperties(obj,nargin,varargin{:}, 'Length');
        end
    end
    
    methods (Access = protected)
        % CONSTRUCTOR
        function setupImpl(obj,~)

            if coder.target('Rtw')% done only for code generation                
                switch obj.WhichSensor
                    case 'Left'
                        obj.SensorNum = 0;
                    case 'Right'
                        obj.SensorNum = 1;
                end
                
                % include the header file that defines our C functions
                coder.cinclude('CAU_SpeedSensor_wrapper.h')
                
                % --- CONSTRAINS ON INPUT ---
                obj.ElpsdTMax = min(max(round(abs(obj.ElpsdTMax)),obj.minElpsdTMax), obj.maxElpsdTMax);
                obj.ChrTPT1 = min(max(obj.ChrTPT1,obj.minChrTPT1), obj.maxChrTPT1);

                % Register init function
                coder.ceval('CAU_SpeedSensor_Init', uint16(obj.SgmntWdth), uint16(obj.ElpsdTMax), obj.ChrTPT1, uint8(obj.SensorNum));
            end
        end
        % METHODS FOR EVERY STEP
        function [speed, stillstand] = stepImpl(obj)
            speed = 0.0;
            stillstand = 0.0;
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('CAU_SpeedSensor_wrapper.h')
                % Register get function 
                speed = coder.ceval('CAU_Get_Speed', obj.SensorNum);
                stillstand = coder.ceval('CAU_Get_Stillstand', obj.SensorNum);
                % cast 
                speed = double(speed);
                stillstand = double(stillstand);
            end
        end
        % DESTRUCTOR
        function releaseImpl(obj)
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('CAU_SpeedSensor_wrapper.h');
                % Register release function
                coder.ceval('CAU_SpeedSensor_Terminate',obj.SensorNum);
            end
        end
    end
    
    methods (Static)
        function name = getDescriptiveName()
            name = 'CAU_SpeedSensor';
        end
        function b = isSupportedContext(context)
            b = context.isCodeGenTarget('rtw');
        end
        function updateBuildInfo(buildInfo, context)
            % Update the build-time buildInfo
            if context.isCodeGenTarget('rtw')
                blockRoot = getRootPath();
                buildInfo.addIncludePaths({[blockRoot, '/include']});
                buildInfo.addIncludeFiles({'CAU_SpeedSensor.h'});
                buildInfo.addSourcePaths({[blockRoot, '/src']});
                buildInfo.addSourceFiles({'CAU_SpeedSensor.cpp',...
                                          'CAU_SpeedSensor_wrapper.cpp'});
            end
        end
    end
end