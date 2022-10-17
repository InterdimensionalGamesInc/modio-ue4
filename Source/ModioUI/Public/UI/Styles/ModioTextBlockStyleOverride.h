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

#include "Containers/Map.h"
#include "Core/ModioNewPropertyHelpers.h"
#include "Styling/SlateTypes.h"
#include "UObject/NameTypes.h"

#include "ModioTextBlockStyleOverride.generated.h"

/// @brief derived class to make details customization easier
/// details customization will place a checkbox next to every property (including nested properties) in StyleProperties
/// if ticked, details customization will save the path of the property, and the value of the checkbox, in
/// OverriddenProperties
USTRUCT(BlueprintType)
struct MODIOUI_API FModioTextBlockStyleOverride : public FSlateWidgetStyle
{
	GENERATED_BODY()
	/**
	* Static stored property of the type name
	**/
	static const FName TypeName;
	
	/**
	* Function to retrieve the type name stored property
	* @return FName with the type
	**/
	virtual const FName GetTypeName() const override
	{
		return TypeName;
	};

	/**
	* Retrieve the base text block style
	* @return The default text bloc style
	**/
	static const FModioTextBlockStyleOverride& GetDefault()
	{
		static FModioTextBlockStyleOverride Default;
		return Default;
	}

	/**
	* Stored property to the text block style 
	**/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ShowOnlyInnerProperties), Category = "Widgets")
	FTextBlockStyle StyleProperties;

	/**
	* Stored property that maps between property names and their overridden status
	**/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "true!=false", EditConditionHides),
			  Category = "Widgets")
	TMap<FName, bool> OverriddenProperties;

	/// @brief Applies the overrides to the specified input style
	/// @returns New copy of the passed in style with the specified properties overridden
	FTextBlockStyle ApplyToStyle(const FTextBlockStyle& InStyle) const
	{
		FTextBlockStyle ComputedStyle = InStyle;
		// Iterate through our list of properties where the user has ticked the box indicating they want to override a
		// value
		for (const TPair<FName, bool> Property : OverriddenProperties)
		{
			// If a user ticks the box and then temporarily disables the override by unticking it, we just skip the
			// property
			if (Property.Value)
			{
				FCachedPropertyPath PropertyPath = FCachedPropertyPath(Property.Key.ToString());
				FString PropertyValue;
				// Cheap trick to copy the property value from one struct to the other
				if (PropertyPathHelpers::GetPropertyValueAsString(
						(void*) &StyleProperties, FTextBlockStyle::StaticStruct(), PropertyPath, PropertyValue))
				{
					PropertyPathHelpers::SetPropertyValueFromString(&ComputedStyle, FTextBlockStyle::StaticStruct(),
																	PropertyPath, PropertyValue);
				}
			}
		}
		return ComputedStyle;
	}
};