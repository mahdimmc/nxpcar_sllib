classdef FXOS8700C < matlab.System & coder.ExternalDependency
    % Accelerometer
    % This class will be used to read data from the accelerometer
    % on the Freescale FRDM-STBC-AGM01 board.
    %
    
    %#codegen
    %#ok<*EMCA>
    
    properties (Nontunable)
        % Full Scale
        WhichScale = '+-2G';
    end
    properties (Hidden,Transient,Constant)
        % this StringSet object creates a dropdown menu
        WhichScaleSet = matlab.system.StringSet({'+-2G','+-4G','+-8G'});
    end
    properties (Hidden)
        % Which Scale is used
        ScaleNum = 1;
        % simSampleNum - tracks which sample we are on in a simulation
        simSampleNum = 0;
    end
    
    methods
        function obj = FXOS8700C(varargin)
            coder.allowpcode('plain');
            % Support name-value pair arguments
            setProperties(obj,nargin,varargin{:}, 'Length');
        end
        
    end
    methods (Access = protected)
        function setupImpl(obj,~)
            if coder.target('Rtw')% done only for code generation
                switch obj.WhichScale
                    case '+-2G'
                        obj.ScaleNum = 1;
                    case '+-4G'
                        obj.ScaleNum = 2;
                    case '+-8G'
                        obj.ScaleNum = 3;
                end
                % include the header file that defines our C functions
                coder.cinclude('FXOS8700_wrapper.h')
                % initialize the touch sensor
                coder.ceval('MW_acc_Init',obj.ScaleNum);
            elseif ( coder.target('Sfun') )
                %
            end
        end
        function [accel_x, accel_y, accel_z, mag_x, mag_y, mag_z] = stepImpl(obj)
            accel_x = 0;
            accel_y = 0;
            accel_z = 0;
            mag_x = 0;
            mag_y = 0;
            mag_z = 0;
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('FXOS8700_wrapper.h')
                % get the current accel values in x, y and z direction
                accel_x = coder.ceval('MW_accel_getX');
                accel_y = coder.ceval('MW_accel_getY');
                accel_z = coder.ceval('MW_accel_getZ');
                % get the current mag values in x, y and z direction
                mag_x = coder.ceval('MW_mag_getX');
                mag_y = coder.ceval('MW_mag_getY');
                mag_z = coder.ceval('MW_mag_getZ');
            elseif ( coder.target('Sfun') )
                obj.simSampleNum = obj.simSampleNum + 1;
            end
        end
        function releaseImpl(~)
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('FXOS8700_wrapper.h');
                % free dynamically allocated memory
                coder.ceval('MW_acc_Terminate');
            end
        end
    end
    methods (Static)
        function name = getDescriptiveName()
            name = '6-axis integrated e-compass';
        end
        function b = isSupportedContext(context)
            b = context.isCodeGenTarget('rtw');
        end
        function updateBuildInfo(buildInfo, context)
            % Update the build-time buildInfo
            if context.isCodeGenTarget('rtw')
                blockRoot = getRootPath();
                buildInfo.addIncludePaths({[blockRoot, '/include']});
                buildInfo.addIncludeFiles({'FXOS8700.h'});
                buildInfo.addSourcePaths({[blockRoot, '/src']});
                buildInfo.addSourceFiles({'FXOS8700.cpp',...
                    'FXOS8700_wrapper.cpp'});
            end
        end
    end
end