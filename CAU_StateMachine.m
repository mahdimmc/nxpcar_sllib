classdef CAU_StateMachine < matlab.System & coder.ExternalDependency
    % CAU_StateMachine
    %
    % ===================================
    % Chair of Automatic Control
    % Christian-Albrechts University Kiel
    % Created on: Dec 07, 2016
    % Author: hewe@tf.uni-kiel.de
    
    properties (Hidden,Constant)
        stateSwDelay = 10;
    end
    
    properties (Hidden,Transient)
        state = 1;
        nextState = 1;
        delayCount = 10; % init with stateSwDelay
        stateSwitchNotice = 0; % blinking of state LED during delay phase
    end
    
    methods
        function obj = CAU_StateMachine(varargin)
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
                coder.cinclude('CAU_StateMachine_wrapper.h')
                coder.ceval('CAU_StateMachine_Init');
                coder.cinclude('CAU_BattLED_onlyWrapper.h')
                coder.ceval('CAU_BattLEDs_Init');
            end
        end
        
        % METHODS FOR EVERY STEP
        function [status, enableFlags, currState, cntrls]=stepImpl(obj, nextFlags_, errFlags_)
            % Def vars
            status = -1;
            cntrls = zeros(1,3);
            enableFlags = zeros(1,3);
            
            % Handle the errors
            if(sum(errFlags_) ~= 0)
                cntrls(1) = 1; % Raise ERR/STOP flag
            end
            
            % Act only if there is no error raised
            if (cntrls(1) == 0)
                % Handle switching demand
                if obj.state == 1 && nextFlags_(1) > 0
                    obj.nextState = 2; % change to: do
                    obj.stateSwitchNotice = 1;
                elseif obj.state == 2 && nextFlags_(2) > 0
                    obj.nextState = 3; % change to: exit
                    obj.stateSwitchNotice = 1;
                elseif obj.state == 3 && nextFlags_(3) > 0
                    obj.nextState = 3; % stay in: exit
                    % obj.stateSwitchNotice = 1;
                end                  
            else
                % Return to idle state instantly
                obj.state = 1;
            end
            
            % Handle switch delay
            if obj.state ~= obj.nextState
                obj.delayCount = obj.delayCount - 1;
                if obj.delayCount == 0
                    obj.state = obj.nextState;
                    obj.delayCount = obj.stateSwDelay;
                    obj.stateSwitchNotice = 0;
                end
            end
            
            % Change state with enableFlags
            enableFlags(obj.state) = 1;
            currState = obj.state;
            
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('CAU_StateMachine_wrapper.h')
                status = coder.ceval('CAU_StateMachine_ReadStatus');
                
                coder.cinclude('CAU_BattLED_onlyWrapper.h')
                coder.ceval('CAU_BattLEDs_ShowState', obj.state, cntrls(1), obj.stateSwitchNotice);
            end
        end
        
        % DESTRUCTOR
        function releaseImpl(~)
            if coder.target('Rtw')% done only for code generation
                coder.cinclude('CAU_StateMachine_wrapper.h');
                coder.ceval('CAU_StateMachine_Terminate');
                
                coder.cinclude('CAU_BattLED_onlyWrapper.h')
                coder.ceval('CAU_BattLEDs_Terminate');
            end
        end
    end
    
    methods (Static)
        function name = getDescriptiveName()
            name = 'CAU_StateMachine';
        end
        function b = isSupportedContext(context)
            b = context.isCodeGenTarget('rtw');
        end
        function updateBuildInfo(buildInfo, context)
            % Update the build-time buildInfo
            if context.isCodeGenTarget('rtw')
                blockRoot = getRootPath();
                buildInfo.addIncludePaths({[blockRoot, '/include']});
                buildInfo.addIncludeFiles({'CAU_StateMachine.h'});
                buildInfo.addSourcePaths({[blockRoot, '/src']});
                buildInfo.addSourceFiles({'CAU_StateMachine.cpp',...
                    'CAU_StateMachine_wrapper.cpp',...
                    'CAU_BattLED_onlyWrapper.cpp'});
            end
        end
    end
end