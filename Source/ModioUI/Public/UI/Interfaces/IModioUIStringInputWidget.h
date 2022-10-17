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

#include "UObject/Interface.h"

#include "IModioUIStringInputWidget.generated.h"

UINTERFACE(BlueprintType)
class MODIOUI_API UModioUIStringInputWidget : public UInterface
{
	GENERATED_BODY()
};

class MODIOUI_API IModioUIStringInputWidget : public IInterface
{
	GENERATED_BODY()
protected:
	virtual FString NativeGatherInput()
	{
		return FString {};
	}

	virtual void NativeSetHintText(FText InHintText) {};
	virtual void NativeSetInput(const FString& Input) {};

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ModioUIStringInputWidget")
	void SetHint(const FText& HintText);

	void SetHint_Implementation(const FText& HintText);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ModioUIStringInputWidget")
	FString GatherInput();

	FString GatherInput_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ModioUIStringInputWidget")
	void SetInput(const FString& Input);

	void SetInput_Implementation(const FString& Input);
};