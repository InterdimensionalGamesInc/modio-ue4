/*
 *  Copyright (C) 2021 mod.io Pty Ltd. <https://mod.io>
 *
 *  This file is part of the mod.io UE4 Plugin.
 *
 *  Distributed under the MIT License. (See accompanying file LICENSE or
 *   view online at <https://github.com/modio/modio-ue4/blob/main/LICENSE>)
 *
 */

#include "UI/BaseWidgets/Slate/SModioNotificationList.h"
#include "UI/BaseWidgets/Slate/SModioNotificationItem.h"
#include "Widgets/SBoxPanel.h"

// SModioNotificationItem -> SModioNotificationObjectWidget -> SWidget root from uwidget

void SModioNotificationList::NotificationItemFadedOut(const TSharedRef<SNotificationItem>& NotificationItem)
{
	SNotificationList::NotificationItemFadedOut(NotificationItem);
}

void SModioNotificationList::Construct(const FArguments& InArgs)
{
	OnGenerateNotificationWidget = InArgs._OnGenerateNotificationWidget;
}

// Might not need the notification info?
TSharedRef<SNotificationItem> SModioNotificationList::AddNotification(const FNotificationInfo& Info)
{
	/*auto NewItem = SNew(SModioNotificationItem).Content()[OnGenerateNotificationWidget.Execute()];

	NewItem->SetList(SharedThis(this));
	MessageItemBoxPtr->AddSlot().AutoHeight().HAlign(HAlign_Right)[NewItem];

	if (Info.bFireAndForget)
	{
		NewItem->ExpireAndFadeout();
	}

	return NewItem;*/
	return SNew(SModioNotificationItem);
}
