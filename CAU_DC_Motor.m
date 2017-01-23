classdef CAU_DC_Motor < matlab.System & coder.ExternalDependency
    % DC Motor
    % This class will be used to set the speed of a DC Motor connected
    % to the TFC-SHIELD provided in the Freescale Cup Kit by Freescale,
    % when used with the FRDM-KL25Z board.
    %
    % Copyright 2014 - 2015 The MathWorks, Inc.
    
    %#codegen
    %#ok<*EMCA>
    
    properties (Nontunable)
        % WhichMotor - DC Motor
        WhichMotor = 'A';
    end
    
    properties (Hidden,Transient,Constant)
        % this StringSet object creates a dropdown menu
        WhichMotorSet = matlab.system.StringSet({'A','B'});
    end
    
    properties (Hidden, Nontunable)
        % keeps track of the selected Motor
        motorNum = 0;
    end
    
    methods
        function obj = dcMotor(varargin)
            coder.allowpcode('plain');
            % Support name-value pair arguments
            setProperties(obj,nargin,varargin{:}, 'Length');
        end
    end
    
    methods (Access = protected)
        function setupImpl(obj,~)
            % find out which motor to initialize
            switch obj.WhichMotor
                case 'A'
                    obj.motorNum = 0;
                case 'B'
                    obj.motorNum = 1;
            end
            if coder.target('Rtw')% done only for code gen                
                coder.cinclude('CAU_DC_Motor_wrapper.h');
                % initialize the DC Motor
                coder.ceval('CAU_DC_Motor_Init', obj.motorNum);
            elseif ( coder.target('Sfun') )
                % do nothing in simulation
            end
        end
        
        function stepImpl(obj, speed)
            if coder.target('Rtw')% done only for code gen
                coder.cinclude('CAU_DC_Motor_wrapper.h');
                % set the speed for this DC Motor
                coder.ceval('CAU_DC_Motor_SetSpeed', obj.motorNum, speed);
            elseif ( coder.target('Sfun') )
                % do nothing in simulation
            end
        end
        
        function releaseImpl(obj)
            if coder.target('Rtw')% done only for code gen
                coder.cinclude('CAU_DC_Motor_wrapper.h');
                % free dynamically allocated memory
                coder.ceval('CAU_DC_Motor_Terminate', obj.motorNum);
            elseif ( coder.target('Sfun') )
                % do nothing in simulation
            end
        end
    end
    
    methods (Static)
        function name = getDescriptiveName()
            name = 'DC Motor';
        end
        
        function b = isSupportedContext(context)
            b = context.isCodeGenTarget('rtw');
        end
        
        % Update the build-time buildInfo
        function updateBuildInfo(buildInfo, context)
            if context.isCodeGenTarget('rtw')
                sppkgroot = strrep(codertarget.freedomboard.internal.getSpPkgRootDir(),'\','/');
                buildInfo.addIncludeFiles({'CAU_DC_Motor.h'});
                buildInfo.addSourcePaths({[sppkgroot, '/src']});
                buildInfo.addSourceFiles({ 'CAU_DC_Motor.cpp', 'CAU_DC_Motor_wrapper.cpp'});
            end
        end
    end
end
