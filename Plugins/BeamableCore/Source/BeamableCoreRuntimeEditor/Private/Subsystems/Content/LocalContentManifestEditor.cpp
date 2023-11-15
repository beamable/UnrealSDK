#include "Subsystems/Content/LocalContentManifestEditor.h"

#include "BeamableCoreEditorCommands.h"
#include "BeamEditorSettings.h"
#include "SNameComboBox.h"
#include "SSimpleButton.h"
#include "Dialog/SCustomDialog.h"
#include "Subsystems/Content/BeamEditorContent.h"
#include "EditorScriptingUtilities/Public/EditorDialogLibrary.h"
#include "Subsystems/BeamEditor.h"

#define LOCTEXT_NAMESPACE "ULocalContentManifestEditorState"


void ULocalContentManifestEditorState::PrepareEditingUI()
{
	auto DataTableEditorCommands = MakeShared<FUICommandList>();
	// TODO: Map actions for publish and download all (revert all).
	DataTableEditorCommands->MapAction(
		FBeamableCoreEditorCommands::Get().CreateContentObjectInLocalManifest,
		FExecuteAction::CreateUObject(this, &ULocalContentManifestEditorState::AddContentButtonClicked),
		FCanExecuteAction());

	DataTableEditorCommands->MapAction(
		FBeamableCoreEditorCommands::Get().EditContentObjectInLocalManifest,
		FExecuteAction::CreateUObject(this, &ULocalContentManifestEditorState::EditContentButtonClicked),
		FCanExecuteAction());

	DataTableEditorCommands->MapAction(
		FBeamableCoreEditorCommands::Get().PublishManifest,
		FExecuteAction::CreateUObject(this, &ULocalContentManifestEditorState::PublishButtonClicked),
		FCanExecuteAction());

	DataTableEditorCommands->MapAction(
		FBeamableCoreEditorCommands::Get().DownloadManifest,
		FExecuteAction::CreateUObject(this, &ULocalContentManifestEditorState::DownloadButtonClicked),
		FCanExecuteAction());

	// Extend the UV section of the toolbar:	
	auto ToolbarExtender = MakeShared<FExtender>();
	ToolbarExtender->AddToolBarExtension("DataTableCommands", EExtensionHook::After, DataTableEditorCommands,
	                                     FToolBarExtensionDelegate::CreateUObject(
		                                     this, &ULocalContentManifestEditorState::AddDataTableToolbarExtension));
	Editor->AddToolbarExtender(ToolbarExtender);
	Editor->RegenerateMenusAndToolbars();

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>(
		"PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::ENameAreaSettings::HideNameArea;
	DetailsViewArgs.bHideSelectionTip = true;

	EditingObjectDetailsPanel = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	EditingObjectDetailsPanel->SetObject(nullptr);
}


void ULocalContentManifestEditorState::PreChange(const UDataTable* Changed,
                                                 FDataTableEditorUtils::EDataTableChangeInfo ChangedType)
{
	// Things that implement FDataTableEditorUtils::FDataTableEditorManager::ListenerType get instantiated automagically by
	// UE's listener system. This means we'll have one instance of this listener that is never set up properly by our DataTable Asset Opened Handler.
	// So... we early out in that case.
	if (!EditorContentSystem) return;

	// We also early out if the selection was changed in a data table that is not the one being managed by this editor.
	FBeamContentManifestId ContentManifestId;
	UDataTable* Table;
	if (!EditorContentSystem->GetChangingManifest(Changed, ContentManifestId, Table)) return;
}

void ULocalContentManifestEditorState::PostChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo ChangedType)
{
	// Things that implement FDataTableEditorUtils::FDataTableEditorManager::ListenerType get instantiated automagically by
	// UE's listener system. This means we'll have one instance of this listener that is never set up properly by our DataTable Asset Opened Handler.
	// So... we early out in that case.
	if (!EditorContentSystem) return;

	// We also early out if the selection was changed in a data table that is not the one being managed by this editor.
	FBeamContentManifestId ContentManifestId;
	UDataTable* Table;
	if (!EditorContentSystem->GetChangingManifest(Changed, ContentManifestId, Table)) return;

	// INFO: For now, we'll rebuild and revalidate the entire table on each change to it... This won't scale, but we'll need epic to trigger the callbacks correctly so that we can avoid this.	
	RebuildContentNamesForTable();
	SelectedContentIdx = FMath::Clamp(SelectedContentIdx, 0, EditingTableContentNames.Num() - 1);
	SelectedContentComboBox->SetSelectedItem(EditingTableContentNames[SelectedContentIdx]);
	SelectedContentComboBox->Invalidate(EInvalidateWidgetReason::Paint);
}


void ULocalContentManifestEditorState::SelectionChange(const UDataTable* DataTable, FName RowName)
{
	// Things that implement FDataTableEditorUtils::FDataTableEditorManager::ListenerType get instantiated automagically by
	// UE's listener system. This means we'll have one instance of this listener that is never set up properly by our DataTable Asset Opened Handler.
	// So... we early out in that case.
	if (!EditorContentSystem) return;

	// We also early out if the selection was changed in a data table that is not the one being managed by this editor.
	FBeamContentManifestId ContentManifestId;
	UDataTable* Table;
	if (!EditorContentSystem->GetChangingManifest(DataTable, ContentManifestId, Table)) return;

	const auto Selected = EditingTableContentNames.FindLastByPredicate([RowName](TSharedPtr<FName> R)
	{
		return R->IsEqual(RowName);
	});
	SelectedContentComboBox->SetSelectedItem(Selected != -1 ? EditingTableContentNames[Selected] : nullptr);
	SelectedContentComboBox->Invalidate(EInvalidateWidgetReason::Paint);
}

void ULocalContentManifestEditorState::RebuildContentNamesForTable()
{
	EditingTableContentNames.Reset();
	EditingTableContentNames.Add(MakeShared<FName>(TEXT("No content selected!")));
	for (const auto& RowName : EditingTable->GetRowNames())
		EditingTableContentNames.Add(MakeShared<FName>(RowName));
}

void ULocalContentManifestEditorState::AddDataTableToolbarExtension(FToolBarBuilder& Builder)
{
	SAssignNew(SelectedTypeComboBox, SNameComboBox)
	.InitiallySelectedItem(EditorContentSystem->AllContentTypeNames[SelectedTypeIdx])
	.OptionsSource(&EditorContentSystem->AllContentTypeNames)
	.OnSelectionChanged_Lambda([this](TSharedPtr<FName, ESPMode::ThreadSafe> Name, ESelectInfo::Type T)
	                                               {
		                                               SelectedTypeIdx = EditorContentSystem->AllContentTypeNames.
		                                                                                      FindLast(Name);
	                                               });

	Builder.AddSeparator();
	Builder.AddToolBarButton(FBeamableCoreEditorCommands::Get().CreateContentObjectInLocalManifest, NAME_None,
	                         LOCTEXT("CreateContentButtonTxt", "Create Content of Type: "));
	Builder.AddWidget(SelectedTypeComboBox.ToSharedRef());


	// Add Edit / Select Content Dropdown / Remove Buttons
	Builder.AddToolBarButton(FBeamableCoreEditorCommands::Get().EditContentObjectInLocalManifest, NAME_None,
	                         LOCTEXT("EditContentButtonTxt", "Edit Content: "));

	// Fill out the content names for the current editing table
	RebuildContentNamesForTable();

	// Prepare the content combo box TODO: Change this once UE fixes/exposes callbacks so that we can hook into the DataTable's own select/rename/duplicate row callbacks.
	SAssignNew(SelectedContentComboBox, SNameComboBox)
	.InitiallySelectedItem(SelectedContentIdx >= 0 ? EditingTableContentNames[SelectedContentIdx] : nullptr)
	.OptionsSource(&EditingTableContentNames)
	.OnSelectionChanged_Lambda([this](TSharedPtr<FName, ESPMode::ThreadSafe> Name, ESelectInfo::Type T)
	                                                  {
		                                                  SelectedContentIdx = EditingTableContentNames.FindLast(Name);
	                                                  });

	Builder.AddWidget(SelectedContentComboBox.ToSharedRef());

	Builder.AddToolBarButton(FBeamableCoreEditorCommands::Get().PublishManifest, NAME_None,
	                         LOCTEXT("PublishButtonTxt", "Publish"));

	Builder.AddToolBarButton(FBeamableCoreEditorCommands::Get().DownloadManifest, NAME_None,
	                         LOCTEXT("DownloadButtonTxt", "Download"));
}


void ULocalContentManifestEditorState::AddContentButtonClicked()
{
	check(SelectedTypeIdx != -1)
	if (FString ErrMsg; !EditorContentSystem->CreateNewContentInManifest(ManifestId, TEXT(""), SelectedTypeIdx, EditingObject, ErrMsg))
	{
		const auto ErrTitle = FText::FromString(TEXT("Error - Failed Saving Content Object"));
		UEditorDialogLibrary::ShowMessage(ErrTitle, FText::FromString(ErrMsg), EAppMsgType::Ok, EAppReturnType::Ok);
	}
}

void ULocalContentManifestEditorState::EditContentButtonClicked()
{
	if (SelectedContentIdx == 0)
	{
		const auto ErrTitle = LOCTEXT("NonExistentContentObject", "Error - Non-Existent Content Object");
		const auto ErrMsg = FText::FromString(TEXT(
			"Trying to load a content object that doesn't exist.\nPlease select a valid content from the dropdown."));
		UEditorDialogLibrary::ShowMessage(ErrTitle, ErrMsg, EAppMsgType::Ok, EAppReturnType::Ok);
		return;
	}

	const auto SelectedRow = EditingTable->GetRowNames()[SelectedContentIdx - 1];
	EditingObjectId = SelectedRow;

	// Prepare and show the editing window.
	if (FString ErrMsg; !EditorContentSystem->GetContentForEditing(ManifestId, EditingObjectId, EditingObject, ErrMsg))
	{
		const auto ErrTitle = FText::FromString(TEXT("Error"));
		UEditorDialogLibrary::ShowMessage(ErrTitle, FText::FromString(ErrMsg), EAppMsgType::Ok, EAppReturnType::Ok);
	}

	EditingObjectDetailsPanel->SetObject(EditingObject);
	EditingWindow = SNew(SWindow)
		.ClientSize({512.0f, 768.0f})
		.Content()
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().FillHeight(1)[
			EditingObjectDetailsPanel.ToSharedRef()
		]
		+ SVerticalBox::Slot().FillHeight(0.1).MaxHeight(75)[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()[
				SNew(SButton).Text(LOCTEXT("Save", "Save"))
				             .HAlign(HAlign_Center)
				             .VAlign(VAlign_Center)
				             .OnClicked_Lambda([this, &SelectedRow]
				             {
					             if (FString ErrMsg; EditorContentSystem->SaveContentObject(ManifestId, EditingObject, ErrMsg))
					             {
						             EditingWindow->RequestDestroyWindow();
					             }
					             else
					             {
						             const auto ErrTitle = FText::FromString(TEXT("Error - Failed Saving Content Object"));
						             UEditorDialogLibrary::ShowMessage(ErrTitle, FText::FromString(ErrMsg), EAppMsgType::Ok, EAppReturnType::Ok);
					             }

					             return FReply::Handled();
				             })
			]
		]

	];
	FSlateApplication::Get().AddModalWindow(EditingWindow.ToSharedRef(), FSlateApplication::Get().GetActiveTopLevelWindow());
}

void ULocalContentManifestEditorState::PublishButtonClicked()
{
	const auto CoreSettings = GetDefault<UBeamCoreSettings>();
	const auto TargetRealmPid = CoreSettings->TargetRealm.Pid;
	const auto Settings = GetDefault<UBeamEditorSettings>();

	// Find the name of the realm we published to.
	FString RealmName;
	{
		const auto EditorSlot = EditorContentSystem->Editor->GetMainEditorSlot();
		TArray<FBeamProjectRealmData> KnownRealms = Settings->PerSlotDeveloperProjectData.FindChecked(EditorSlot.Name).
		                                                      AllRealms;
		for (const auto& Realm : KnownRealms)
		{
			if (Realm.PID == TargetRealmPid) RealmName = Realm.RealmName;
		}
	}

	auto PublishDialog = SNew(SCustomDialog)
		.Content()[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().FillHeight(1)[
				SNew(STextBlock).Text(FText::FromString(FString::Format(
					TEXT("Do you wish to upload content and manifest to the current target realm ({0})?."),
					{RealmName})))
			]
		].Buttons({
			SCustomDialog::FButton(LOCTEXT("CancelPublish", "Cancel"), FSimpleDelegate::CreateLambda([this]()
			{
				PublishingWindow->RequestDestroyWindow();
			})),

			SCustomDialog::FButton(LOCTEXT("ConfirmPublish", "Confirm"), FSimpleDelegate::CreateLambda([this, RealmName]()
			{
				FBeamOperationEventHandler Handler;
				Handler.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ULocalContentManifestEditorState, OnPublishEvent));
				[[maybe_unused]] const auto Operation = EditorContentSystem->PublishManifest(ManifestId, Handler);
				PublishingWindow->DestroyWindowImmediately();

				const auto Title = LOCTEXT("PublishingWait", "Waiting for Publish");
				const auto Msg = FText::FromString(FString::Format(TEXT("Uploading content and manifest to Current Target Realm={0}."), {ManifestId.AsString, RealmName}));
				PublishingWindow = SNew(SWindow)
				.Title(Title)
				.ClientSize({512.0f, 128.0f})
				.Content()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
					[
						SNew(STextBlock).Text(Msg).Justification(ETextJustify::Center)
					]
				];

				// Show it as a modal of the DataTable editor.
				FSlateApplication::Get().AddModalWindow(PublishingWindow.ToSharedRef(),
					FSlateApplication::Get().GetActiveTopLevelWindow(),
					true);
				PublishingWindow->ShowWindow();
			}))
		});

	PublishingWindow = PublishDialog;
	PublishDialog->ShowModal();
}

void ULocalContentManifestEditorState::DownloadButtonClicked()
{
	FBeamOperationEventHandlerCode EventHandler;
	EventHandler.BindLambda([this](const TArray<FUserSlot>&, FBeamOperationEvent OperationEvent)
		{
			if (OperationEvent.EventType == OET_SUCCESS)
			{
				// Handle Final Success Event
				if (OperationEvent.EventSubTypeCode == 0)
				{
					// Notify the data table editor that this table has changed (it's the only way to get it to redraw)	
					FDataTableEditorUtils::BroadcastPostChange(
						EditingTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
				}

				// Handle Sub-Event for when the Manifest Changes is ready
				if (OperationEvent.EventSubTypeCode == 1)
				{
					// Show changes in a dialog and ask for confirmation, then call ContentSystem apply.
					const auto WorkingDownloadState = EditorContentSystem->WorkingDownloadStates[ManifestId];
					TSharedRef<SVerticalBox> Panel = SNew(SVerticalBox);

					Panel->AddSlot()[
						SNew(STextBlock).Text(FText::FromString("New Items")).Font(
							FCoreStyle::GetDefaultFontStyle("Bold", 18))
					];
					for (const UBaseContentReference* Add : WorkingDownloadState->RemoteToLocalDiff.ToAdd)
					{
						Panel->AddSlot()[
							SNew(STextBlock).Text(FText::FromString(Add->Content->Id.AsString))
						];
					}

					Panel->AddSlot()[
						SNew(STextBlock).Text(FText::FromString("Modified Items")).Font(
							FCoreStyle::GetDefaultFontStyle("Bold", 18))
					];
					for (const UBaseContentReference* Modified : WorkingDownloadState->RemoteToLocalDiff.ToModify)
					{
						Panel->AddSlot()[
							SNew(STextBlock).Text(FText::FromString(Modified->Content->Id.AsString))
						];
					}
					Panel->AddSlot()[
						SNew(SSimpleButton).Text(FText::FromString("Confirm")).OnClicked_Lambda([this]
						{
							EditorContentSystem->DownloadManifest_ApplyUserInput(ManifestId, true);
							DownloadingWindow->RequestDestroyWindow();
							return FReply::Handled();
						})
					];
					Panel->AddSlot()[
						SNew(SSimpleButton).Text(FText::FromString("Cancel")).OnClicked_Lambda([this]
						{
							EditorContentSystem->DownloadManifest_ApplyUserInput(ManifestId, false);
							DownloadingWindow->RequestDestroyWindow();
							return FReply::Handled();
						})
					];

					DownloadingWindow = SNew(SWindow).ClientSize({512.0f, 512.0f}).HasCloseButton(false)
					                                 .Content()[Panel];

					// Show it as a modal of the DataTable editor.
					FSlateApplication::Get().AddModalWindow(DownloadingWindow.ToSharedRef(), FSlateApplication::Get().GetActiveTopLevelWindow(), true);
					DownloadingWindow->ShowWindow();
				}
			}

			if (OperationEvent.EventType == OET_ERROR)
			{
				const auto Title = LOCTEXT("DownloadFailed", "Download Failed");
				const auto Msg = FText::FromString(FString::Format(
					TEXT("Manifest failed to download content.\nError={1}"),
					{OperationEvent.EventData}));

				UEditorDialogLibrary::ShowMessage(Title, Msg, EAppMsgType::Ok, EAppReturnType::Ok);
				UE_LOG(LogBeamContent, Error, TEXT("Content Download Error - %s."), *OperationEvent.EventData);
			}
		}

	);
	EditorContentSystem->DownloadManifest(ManifestId, EventHandler);
}

void ULocalContentManifestEditorState::OnPublishEvent(const TArray<FUserSlot>& UserSlots,
                                                      FBeamOperationEvent OperationEvent) const
{
	const auto CoreSettings = GetDefault<UBeamCoreSettings>();
	const auto TargetRealmPid = CoreSettings->TargetRealm.Pid;
	const auto Settings = GetDefault<UBeamEditorSettings>();

	// Find the name of the realm we published to.
	FString RealmName;
	{
		const auto EditorSlot = UserSlots[0];
		TArray<FBeamProjectRealmData> KnownRealms = Settings->PerSlotDeveloperProjectData.FindChecked(EditorSlot.Name).
		                                                      AllRealms;
		for (const auto& Realm : KnownRealms)
		{
			if (Realm.PID == TargetRealmPid) RealmName = Realm.RealmName;
		}
	}

	PublishingWindow->RequestDestroyWindow();

	if (OperationEvent.EventType == OET_SUCCESS)
	{
		// If it is the final success event (as in, the operation completed successfully)
		if (OperationEvent.EventSubTypeCode == 0)
		{
			const auto ContentManifestId = OperationEvent.EventData;

			const auto Title = LOCTEXT("PublishSuccessful", "Publish Successful");
			const auto Msg = FText::FromString(FString::Format(
				TEXT("Successfully published manifest with Id={0} to Realm={1}."), {ContentManifestId, RealmName}));
			UEditorDialogLibrary::ShowMessage(Title, Msg, EAppMsgType::Ok, EAppReturnType::Ok);
		}

		UE_LOG(LogBeamContent, Display, TEXT("Content Publish sucessfull!\n%s"), *OperationEvent.EventData);
	}
	else if (OperationEvent.EventType == OET_ERROR)
	{
		const auto Title = LOCTEXT("PublishSuccessful", "Publish Failed");
		const auto Msg = FText::FromString(FString::Format(
			TEXT("Manifest failed to be published manifest Realm={0}.\nError={1}"),
			{RealmName, OperationEvent.EventData}));
		UEditorDialogLibrary::ShowMessage(Title, Msg, EAppMsgType::Ok, EAppReturnType::Ok);
		UE_LOG(LogBeamContent, Error, TEXT("Content Publish Had error %s."), *OperationEvent.EventData);
	}
	else
	{
		UE_LOG(LogBeamContent, Display, TEXT("Content Publish was Cancelled."))
	}
}

FString ULocalContentManifestEditorState::GetJsonBlobPath(FString RowName) const
{
	return UBeamEditorContent::GetJsonBlobPath(RowName, ManifestId);
}


#undef LOCTEXT_NAMESPACE
