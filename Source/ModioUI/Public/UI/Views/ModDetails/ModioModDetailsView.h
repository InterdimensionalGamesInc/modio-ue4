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

#include "Components/TextBlock.h"
#include "Core/ModioModInfoUI.h"
#include "CoreMinimal.h"
#include "Types/ModioRating.h"
#include "UI/BaseWidgets/ModioButton.h"
#include "UI/BaseWidgets/ModioRichTextBlock.h"
#include "UI/CommonComponents/ModioModManagementWidgetBase.h"
#include "UI/CommonComponents/ModioRichTextButton.h"
#include "UI/CommonComponents/ModioSubscriptionBadge.h"
#include "UI/CommonComponents/ModioTagList.h"
#include "UI/EventHandlers/IModioUIAuthenticationChangedReceiver.h"
#include "UI/EventHandlers/IModioUIModInfoReceiver.h"
#include "UI/Interfaces/IModioUIAsyncOperationWidget.h"
#include "UI/Interfaces/IModioUIModDetailsDisplay.h"
#include "UI/Views/ModDetails/ModioAsyncOpWrapperWidget.h"
#include "UI/Views/ModDetails/ModioModDetailsImageGallery.h"
#include "UI/Views/ModioMenuView.h"

#include "ModioModDetailsView.generated.h"

/**
* Base class that displays a mod details, like title, summary, and images. It
* also includes buttons to provide feedback to the system
**/
UCLASS()
class MODIOUI_API UModioModDetailsView : public UModioMenuView,
										 public IModioUIModInfoReceiver,
										 public IModioUIModDetailsDisplay,
										 public IModioUIAsyncOperationWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void SynchronizeProperties() override;
	virtual void NativeDisplayModDetails(const TScriptInterface<class IModioModInfoUIDetails>& Details) override;
	virtual void NativeDisplayModDetailsForId(const FModioModID& ModID) override;
	virtual void NativeRequestOperationRetry() override;
	UFUNCTION()
	void RateUpClicked();
	UFUNCTION()
	void RateDownClicked();
	UFUNCTION()
	void ReportClicked();
	UFUNCTION()
	void OnRatingSubmissionComplete(FModioErrorCode ec, EModioRating SubmittedRating);

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets",
			  meta = (BindWidgetOptional, MustImplement = "ModioUIAsyncHandlerWidget"))
	UWidget* DetailsLoader;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioAsyncOpWrapperWidget* DetailsViewContent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioRichTextButton* SubscribeButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioRichTextButton* RateUpButton;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioRichTextButton* RateDownButton;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioRichTextButton* ReportButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioUserWidgetBase* ModPropertiesInspector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioModManagementWidgetBase* ProgressWidget;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ModioModDetailsView")
	FText SubscribeButtonFormat;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ModioModDetailsView")
	FText RateUpTextFormat;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ModioModDetailsView")
	FText RateDownTextFormat;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ModioModDetailsView")
	FText ReportTextFormat;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioRichTextBlock* ModTitleTextBlock;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioRichTextBlock* ModSummaryTextBlock;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioRichTextBlock* ModFullDescriptionTextBlock;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioTagList* ModTags;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioRichTextBlock* ModChangelog;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Localization")
	FText SubscribeLabel;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Localization")
	FText UnsubscribeLabel;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioModDetailsImageGallery* ImageGallery;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioSubscriptionBadge* SubscriptionBadge;

#if WITH_EDITORONLY_DATA

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Editor Preview Data")
	UModioModInfoUI* EditorPreviewDataSource;
#endif

	bool bCachedSubscriptionState;

	UFUNCTION()
	virtual void OnModSubscriptionStatusChanged(FModioModID ID, bool Subscribed);

	UFUNCTION()
	void NativeSubscribeClicked();

	void NativeOnSetDataSource() override;

	FModioModID CurrentModID;
	void NativeOnModInfoRequestCompleted(FModioModID ModID, FModioErrorCode ec, TOptional<FModioModInfo> Info);

	
	FTimerHandle SetFocusTimerHandle;

	UFUNCTION()
	void SetInitialFocus();


public:
	/**
	* Display the mod details for a corresponding ModID
	* @param ID The ModID to bring forward
	**/
	void ShowDetailsForMod(FModioModID ID);
};
