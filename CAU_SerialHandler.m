classdef CAU_SerialHandler < matlab.System & coder.ExternalDependency
    % CAU_SerialHandler Provides the pointer management to avoid two instances of mbeds serial object
    %
    % ===================================
    % Chair of Automatic Control
    % Christian-Albrechts University Kiel
    % Created on: Dec 13, 2016
    % Author: hewe@tf.uni-kiel.de
    
    properties
        switchUART = 0; %TODO...implement this 
    end
    
    methods
        function obj = CAU_SerialHandler(varargin)
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
                coder.cinclude('CAU_SerialHandler_wrapper.h')
                
                % Register init function
                coder.ceval('CAU_SerialHandler_Init');
            end
        end
        
        % METHODS FOR EVERY STEP
        function stepImpl(~)
            if coder.target('Rtw')% done only for code generation
                
            end
        end
        
        % DESTRUCTOR
        function releaseImpl(~)
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('CAU_SerialHandler_wrapper.h');
                
                % Register release function
                coder.ceval('CAU_SerialHandler_Terminate');
            end
        end
    end
    
    methods (Static)
        function name = getDescriptiveName()
            name = 'CAU_SerialHandler';
        end
        function b = isSupportedContext(context)
            b = context.isCodeGenTarget('rtw');
        end
        function updateBuildInfo(buildInfo, context)
            % Update the build-time buildInfo
            if context.isCodeGenTarget('rtw')
                blockRoot = getRootPath();
                buildInfo.addIncludePaths({[blockRoot, '/include']});
                buildInfo.addIncludeFiles({'CAU_SerialHandler.h'});
                buildInfo.addSourcePaths({[blockRoot, '/src']});
                buildInfo.addSourceFiles({'CAU_SerialHandler.cpp',...
                    'CAU_SerialHandler_wrapper.cpp'});
            end
        end
    end
end