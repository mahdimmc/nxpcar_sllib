classdef CAU_SerialSend < matlab.System & coder.ExternalDependency 
    % CAU_SerialSend
    %
    % ===================================
    % Chair of Automatic Control
    % Christian-Albrechts University Kiel
    % Created on: Nov 07, 2016
    % Author: hewe@tf.uni-kiel.de
    
    properties
        quantToTrnf = 2; % Quantity to transfer
    end
    
    
    methods
        function obj = CAU_SerialSend(varargin)
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
                coder.cinclude('CAU_SerialSend_wrapper.h')
                
                % Register init function
                coder.ceval('CAU_SerialSend_Init', floor(obj.quantToTrnf));
            end
        end
        
        % METHODS FOR EVERY STEP
        function stepImpl(~, numVec)
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('CAU_SerialSend_wrapper.h')
                
                % Register get function
                coder.ceval('CAU_SerialSetData', coder.ref(numVec));
            end
            
        end
        
        % DESTRUCTOR
        function releaseImpl(~)
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('CAU_SerialSend_wrapper.h');
                
                % Register release function
                coder.ceval('CAU_SerialSend_Terminate');
            end
        end
    end
    
    methods (Static)
        function name = getDescriptiveName()
            name = 'CAU_SerialSend';
        end
        function b = isSupportedContext(context)
            b = context.isCodeGenTarget('rtw');
        end
        function updateBuildInfo(buildInfo, context)
            % Update the build-time buildInfo
            if context.isCodeGenTarget('rtw')
                blockRoot = getRootPath();
                buildInfo.addIncludePaths({[blockRoot, '/include']});
                buildInfo.addIncludeFiles({'CAU_SerialSend.h'});
                buildInfo.addSourcePaths({[blockRoot, '/src']});
                buildInfo.addSourceFiles({'CAU_SerialSend.cpp',...
                    'CAU_SerialSend_wrapper.cpp'});
            end
        end
    end
end