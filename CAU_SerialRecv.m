classdef CAU_SerialRecv < matlab.System & coder.ExternalDependency 
    % CAU_SerialRecv
    %
    % ===================================
    % Chair of Automatic Control
    % Christian-Albrechts University Kiel
    % Created on: Nov 07, 2016
    % Author: hewe@tf.uni-kiel.de
    
    properties
        quantToRecv = 5; % Quantity of expected floating point numbers
        fullDigits = 3; % Integer digits
        deciDigits = 2; % Fractional digits
    end
    
    properties  (Constant)
        outputSize = 5; % Maximal output vector size to work with (fixed)
    end
    
    
    methods
        function obj = CAU_SerialRecv(varargin)
            coder.allowpcode('plain');
            % Support name-value pair arguments
            setProperties(obj,nargin,varargin{:}, 'Length');
        end
    end
    
    methods (Access = protected)  
        % CONSTRUCTOR
        function setupImpl(obj)
            if coder.target('Rtw')% done only for code generation
             
                
                % include the header file that defines our C functions
                coder.cinclude('CAU_SerialRecv_wrapper.h')
                
                % Register init function
                coder.ceval('CAU_SerialRecv_Init', obj.quantToRecv, obj.fullDigits, obj.deciDigits); %obj.quantToTrnf
            end
        end
        
        % METHODS FOR EVERY STEP
        function [res] = stepImpl(obj)
            res = zeros(obj.outputSize, 1);
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('CAU_SerialRecv_wrapper.h')
                
                % Register get function
                coder.ceval('CAU_SerialGetData', coder.ref(res));
            end
            
        end
        
        % DESTRUCTOR
        function releaseImpl(~)
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('CAU_SerialRecv_wrapper.h');
                
                % Register release function
                coder.ceval('CAU_SerialRecv_Terminate');
            end
        end
    end
    
    methods (Static)
        function name = getDescriptiveName()
            name = 'CAU_SerialRecv';
        end
        function b = isSupportedContext(context)
            b = context.isCodeGenTarget('rtw');
        end
        function updateBuildInfo(buildInfo, context)
            % Update the build-time buildInfo
            if context.isCodeGenTarget('rtw')
                blockRoot = getRootPath();
                buildInfo.addIncludePaths({[blockRoot, '/include']});
                buildInfo.addIncludeFiles({'CAU_SerialRecv.h'});
                buildInfo.addSourcePaths({[blockRoot, '/src']});
                buildInfo.addSourceFiles({'CAU_SerialRecv.cpp',...
                    'CAU_SerialRecv_wrapper.cpp'});
            end
        end
    end
end