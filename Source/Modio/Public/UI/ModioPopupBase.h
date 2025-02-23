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
#include "Blueprint/UserWidget.h"

#include "ModioPopupBase.generated.h"

 /**
 * Modio UI element that provides basic functionality to show-up a widget 
 * from an action
 **/
UCLASS()
class UModioPopupBase : public UUserWidget
{
	GENERATED_BODY()
};
