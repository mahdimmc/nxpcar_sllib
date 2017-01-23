function blkStruct = slblocks
		% This function specifies that the library should appear
		% in the Library Browser
		% and be cached in the browser repository

		Browser.Library = 'CAU_NXP_Car_Lib';
		% 'lib_gyro' is the name of the library
        
		Browser.Name = 'CAU NXP Car';
		% 'My Library' is the library name that appears in the Library Browser

		blkStruct.Browser = Browser;