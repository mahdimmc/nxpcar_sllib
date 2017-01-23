classdef TextLCD < matlab.System & coder.ExternalDependency
    % TextLCD: print two floating numbers to the two lines of a HD44780 display, connected to the PINs {PTC0}RS, {PTC7}E, {PTB8,PTB9,PTB10,PTB11}Data. To reduce the cables to two use a I2C implementation
    
    %#codegen
    %#ok<*EMCA>
  
     
    properties (Hidden)
        % simSampleNum - tracks which sample we are on in a simulation
        simSampleNum = 0;
    end
    methods
        function obj = TextLCD(varargin)
            coder.allowpcode('plain');
            % Support name-value pair arguments
            setProperties(obj,nargin,varargin{:}, 'Length');
        end
    end
    methods (Access = protected)
        function setupImpl(~)
            if coder.target('Rtw')% done only for code generation
                % include the header file that defines our C functions
                coder.cinclude('TextLCD_wrapper.h')
                % initialize the touch sensor
                coder.ceval('MW_TextLCD_Init');
                elseif ( coder.target('Sfun') )
                %
            end
        end
        function [] = stepImpl(obj, line1, line2) %  stepImpl(obj,text)
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('TextLCD_wrapper.h')
                % print text to the TextLCD
                coder.ceval('MW_TextLCD_print',1,line1);     
                coder.ceval('MW_TextLCD_print',2,line2);
            elseif ( coder.target('Sfun') )
                obj.simSampleNum = obj.simSampleNum + 1;
            end
        end
        function releaseImpl(~)
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('TextLCD_wrapper.h');
                % free dynamically allocated memory
                coder.ceval('MW_TextLCD_Terminate');
            end
        end
    end
    methods (Static)
        function name = getDescriptiveName()
            name = 'TextLCD';
        end
        function b = isSupportedContext(context)
            b = context.isCodeGenTarget('rtw');
        end
        function updateBuildInfo(buildInfo, context)
            % Update the build-time buildInfo
            if context.isCodeGenTarget('rtw')
                blockRoot = getRootPath();
                buildInfo.addIncludePaths({[blockRoot, '/include']});
                buildInfo.addIncludeFiles({'TextLCD.h',...
                                           'TextLCD_wrapper.h'});
                buildInfo.addSourcePaths({[blockRoot, '/src']});
                buildInfo.addSourceFiles({'TextLCD.cpp',...
                                          'TextLCD_wrapper.cpp'});
            end
        end
    end
end