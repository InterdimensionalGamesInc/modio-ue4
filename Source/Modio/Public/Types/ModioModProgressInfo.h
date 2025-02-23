/* 
 *  Copyright (C) 2021 mod.io Pty Ltd. <https://mod.io>
 *  
 *  This file is part of the mod.io UE4 Plugin.
 *  
 *  Distributed under the MIT License. (See accompanying file LICENSE or 
 *   view online at <https://github.com/modio/modio-ue4/blob/main/LICENSE>)
 *   
 */

#pragma once

#include "Types/ModioCommonTypes.h"
#include "Types/ModioUnsigned64.h"


#include "ModioModProgressInfo.generated.h"

namespace Modio
{
	class ModProgressInfo;
}

/** 
* Strong type struct representing the progress of a mod installation or update 
**/
USTRUCT(BlueprintType)
struct MODIO_API FModioModProgressInfo
{
	GENERATED_BODY()

	/** 
	* Total size of the downloaded file 
	**/
	UPROPERTY(BlueprintReadOnly,Category="ModProgressInfo")
	FModioUnsigned64 TotalDownloadSize;

	/** 
	* Current amount downloaded in bytes 
	**/
	UPROPERTY(BlueprintReadOnly,Category="ModProgressInfo|Current")
	FModioUnsigned64 CurrentlyDownloadedBytes;

	/** 
	* Total size on disk when fully extracted 
	**/
	UPROPERTY(BlueprintReadOnly,Category="ModProgressInfo")
	FModioUnsigned64 TotalExtractedSizeOnDisk;

	/**
	* Amount of data currently extracted 
	**/
	UPROPERTY(BlueprintReadOnly,Category="ModProgressInfo|Current")
	FModioUnsigned64 CurrentlyExtractedBytes;

	/** 
	* The mod ID of the mod being processed 
	**/
	UPROPERTY(BlueprintReadOnly,Category="ModProgressInfo")
	FModioModID ID;
};

/**
* Struct strong type to wrap an optional value for the ModProgressInfo
**/
USTRUCT(BlueprintType)
struct MODIO_API FModioOptionalModProgressInfo
{
	GENERATED_BODY()

	/**
	* Stored property for the optional ModProgressInfo
	**/
	TOptional<FModioModProgressInfo> Internal;
};

