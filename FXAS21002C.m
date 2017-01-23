classdef FXAS21002C < matlab.System & coder.ExternalDependency
    % Gyro sensor

    properties (Nontunable)
        % Full Scale
        WhichScale = '+-2000rad/s';
    end
    properties (Hidden,Transient,Constant)
        % this StringSet object creates a dropdown menu
        WhichScaleSet = matlab.system.StringSet({'+-250rad/s','+-500rad/s',...
            '+-1000rad/s','+-2000rad/s'});
    end
    properties (Hidden)
        % Which Scale is used
        ScaleNum = 4;
        % simSampleNum - tracks which sample we are on in a simulation
        simSampleNum = 0;
    end
    methods
        function obj = FXAS21002C(varargin)
            coder.allowpcode('plain');
            % Support name-value pair arguments
            setProperties(obj,nargin,varargin{:}, 'Length');
        end
    end
    methods (Access = protected)
        function setupImpl(obj,~)
            if coder.target('Rtw')% done only for code generation
                switch obj.WhichScale
                    case '+-250rad/s'
                        obj.ScaleNum = 1;
                    case '+-500rad/s'
                        obj.ScaleNum = 2;
                    case '+-1000rad/s'
                        obj.ScaleNum = 3;
                    case '+-2000rad/s'
                        obj.ScaleNum = 4;
                end
                % include the header file that defines our C functions
                coder.cinclude('FXAS21002_wrapper.h')
                % initialize the gyro
                coder.ceval('MW_gyro_Init',obj.ScaleNum);
            end
        end
        function [gyro_x, gyro_y, gyro_z] = stepImpl(obj)
            gyro_x = 0;
            gyro_y = 0;
            gyro_z = 0;
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('FXAS21002_wrapper.h')
                % get the current gyro values in x, y and z direction
                % from the sensor
                gyro_x = coder.ceval('MW_gyro_getX',obj.ScaleNum);
                gyro_y = coder.ceval('MW_gyro_getY');
                gyro_z = coder.ceval('MW_gyro_getZ');
            end
        end
        function releaseImpl(~)
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('FXAS21002_wrapper.h');
                % free dynamically allocated memory
                coder.ceval('MW_gyro_Terminate');
            end
        end
    end
    methods (Static)
        function name = getDescriptiveName()
            name = '3-axis gyroscope';
        end
        function b = isSupportedContext(context)
            b = context.isCodeGenTarget('rtw');
        end
        function updateBuildInfo(buildInfo, context)
            % Update the build-time buildInfo
            if context.isCodeGenTarget('rtw')
                blockRoot = getRootPath();
                buildInfo.addIncludePaths({[blockRoot, '/include']});
                buildInfo.addIncludeFiles({'FXAS21002.h'});
                buildInfo.addSourcePaths({[blockRoot, '/src']});
                buildInfo.addSourceFiles({'FXAS21002.cpp',...
                                          'FXAS21002_wrapper.cpp'});
            end
        end
    end
end