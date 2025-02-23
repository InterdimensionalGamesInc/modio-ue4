/*
 *  Copyright (C) 2021 mod.io Pty Ltd. <https://mod.io>
 *
 *  This file is part of the mod.io UE4 Plugin.
 *
 *  Distributed under the MIT License. (See accompanying file LICENSE or
 *   view online at <https://github.com/modio/modio-ue4/blob/main/LICENSE>)
 *
 */

#include "UI/CommonComponents/ModioSelectableTag.h"
#include "Components/ListView.h"
#include "Components/ListViewBase.h"
#include "UI/CommonComponents/ModioListViewString.h"

void UModioSelectableTag::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (TagSelectedCheckbox)
	{
		TagSelectedCheckbox->OnCheckStateChanged.AddDynamic(this, &UModioSelectableTag::OnCheckboxStateChanged);
	}
}

void UModioSelectableTag::OnCheckboxStateChanged(bool bIsChecked)
{
	if (UListViewBase* BaseListView = GetOwningListView())
	{
		if (UListView* MyListView = Cast<UListView>(BaseListView))
		{
			MyListView->SetItemSelection(*MyListView->ItemFromEntryWidget(*this), bIsChecked,
										 ESelectInfo::OnMouseClick);
		}
		else if (UModioListViewString* MyListViewString = Cast<UModioListViewString>(BaseListView))
		{
			MyListViewString->SetItemSelection(*MyListViewString->ItemFromEntryWidget(*this), bIsChecked,
											   ESelectInfo::OnMouseClick);
		}
	}
}
