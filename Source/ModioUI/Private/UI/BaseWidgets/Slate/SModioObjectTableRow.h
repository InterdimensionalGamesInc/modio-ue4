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

#include "Slate/SObjectTableRow.h"
#include "UI/Interfaces/IModioUIUserStringListEntry.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SWidget.h"

template<typename ItemType>
class SModioObjectTableRow : public SObjectTableRow<ItemType>
{
	virtual void InitializeObjectRow() override;
	void InitObjectRowInternal(UUserWidget& ListEntryWidget, TSharedPtr<FString> ListItemObject)
	{
		if (ListEntryWidget.Implements<UModioUIUserStringListEntry>())
		{
			IModioUIUserStringListEntry::Execute_SetListItemString(&ListEntryWidget, *ListItemObject.Get());
		}
	}
	virtual bool SupportsKeyboardFocus() const override
	{
		return SObjectWidget::SupportsKeyboardFocus();
	}
};

template<>
FORCEINLINE void SModioObjectTableRow<UObject*>::InitializeObjectRow()
{
	SObjectTableRow<UObject*>::InitializeObjectRow();
}
template<>
FORCEINLINE void SModioObjectTableRow<TSharedPtr<FString>>::InitializeObjectRow()
{
	TSharedRef<ITypedTableView<TSharedPtr<FString>>> OwnerTable = OwnerTablePtr.Pin().ToSharedRef();
	if (const TSharedPtr<FString>* MyItemPtr = GetItemForThis(OwnerTable))
	{
		if (WidgetObject->Implements<UModioUIUserStringListEntry>())
		{
			IModioUIUserStringListEntry::Execute_SetListItemString(WidgetObject, *MyItemPtr->Get());
		}

		// Unselectable items should never be selected
		if (!ensure(!OwnerTable->Private_IsItemSelected(*MyItemPtr) || IsItemSelectable()))
		{
			OwnerTable->Private_SetItemSelection(*MyItemPtr, false, false);
		}
	}
}