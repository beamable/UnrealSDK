#include "Subsystems/Content/LocalContentManifestEditor.h"

#include "BeamableCoreEditorCommands.h"
#include "BeamEditorSettings.h"
#include "IDataTableEditor.h"
#include "SSimpleButton.h"
#include "Dialog/SCustomDialog.h"
#include "Subsystems/Content/BeamEditorContent.h"
#include "EditorScriptingUtilities/Public/EditorDialogLibrary.h"
#include "Slate/Private/Widgets/Views/SListPanel.h"
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
	if (Changed != EditingTable) return;
}

void ULocalContentManifestEditorState::PostChange(const UDataTable* Changed,
                                                  FDataTableEditorUtils::EDataTableChangeInfo ChangedType)
{
	// Things that implement FDataTableEditorUtils::FDataTableEditorManager::ListenerType get instantiated automagically by
	// UE's listener system. This means we'll have one instance of this listener that is never set up properly by our DataTable Asset Opened Handler.
	// So... we early out in that case.
	if (!EditorContentSystem) return;

	// We also early out if the selection was changed in a data table that is not the one being managed by this editor.
	if (Changed != EditingTable) return;

	TArray<FString> JsonBlobFileNames;
	IFileManager::Get().FindFiles(JsonBlobFileNames,
	                              *(EditorContentSystem->DefaultBeamableProjectContentObjects / ManifestId.AsString));

	auto Rows = Changed->GetRowNames();
	Rows.Sort();
	JsonBlobFileNames.Sort();

	// Handle deletion case
	TArray<FString> RemovedRows;
	if (Rows.Num() < JsonBlobFileNames.Num())
	{
		for (int i = JsonBlobFileNames.Num() - 1; i >= 0; --i)
		{
			const auto JsonBlobFileName = JsonBlobFileNames[i];
			FString JsonRowName, Extension;
			JsonBlobFileName.Split(".", &JsonRowName, &Extension, ESearchCase::CaseSensitive, ESearchDir::FromEnd);
			// If we are not in sync, it means we deleted this row so let's delete the file for it.
			if (!Rows.Contains(FName(JsonRowName)))
			{
				const auto FullPath = EditorContentSystem->DefaultBeamableProjectContentObjects / ManifestId.AsString /
					JsonBlobFileName;
				IFileManager::Get().Delete(*FullPath);
				Rows.Remove(FName(JsonRowName));
			}
		}
	}

	TArray<FString> MissingTypeTags;
	for (int i = 0; i < Rows.Num(); i++)
	{
		FString Row = Rows[i].ToString();
		auto EntryInManifest = EditingTable->FindRow<FLocalContentManifestRow>(FName(Row),
		                                                                       TEXT("Validating Manifest"));

		// Handle case where we are missing the type tag value (which is what tells us what type to deserialize into)
		auto TypeTag = EntryInManifest->Tags.FindByPredicate([](FString Tag)
		{
			return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type);
		});
		if (!TypeTag)
		{
			MissingTypeTags.Add(Row);
		}
		else
		{
			// Handle rename case (if the row name no longer matches the json file name)
			bool bWasRenamed = !EntryInManifest->JsonBlobPath.EndsWith(TEXT("/") + Row + TEXT(".json"));
			if (bWasRenamed)
			{
				FString OldName, Discard;
				EntryInManifest->JsonBlobPath.Split("/", &Discard, &OldName, ESearchCase::CaseSensitive,
				                                    ESearchDir::FromEnd);
				OldName.Split(".", &OldName, &Discard, ESearchCase::CaseSensitive, ESearchDir::FromEnd);

				const auto TypeName = UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag);
				UBeamContentObject* Obj;
				if (EditorContentSystem->TryLoadContentObject(ManifestId, OldName, TypeName, Obj) ||
					EditorContentSystem->TryLoadContentObject(ManifestId, Row, TypeName, Obj))
				{
					const auto TypePrefix = Obj->BuildContentTypeString();
					if (!Row.StartsWith(TypePrefix))
					{
						if (Row.Contains("."))
						{
							const auto ErrTitle = LOCTEXT("InvalidContentName", "Error - Invalid Content Name");
							const auto ErrMsg = FText::FromString(FString::Format(
								TEXT("Content Ids (Row Names) must be in the format <ContentType>.<Name>. If you just type in the Name, we guarantee the prefix is added correctly."),
								{Row}));

							UEditorDialogLibrary::ShowMessage(ErrTitle, ErrMsg, EAppMsgType::Ok, EAppReturnType::Ok);

							// We need to delay as we can't use FDataTableEditorUtils functions without triggering another PostChange call.
							// This does not loop infinitely, but it causes a problem that gets the DataTable UI in a bad state and requires closing/opening again to fix.
							// Basically, because the call to PostChange inside RenameRow runs before the rest of this first chain of PostChange invocations, the UI's PostChange
							// callback for the RenameRow chain gets run before the one for the original change here. This causes all sorts of problems.
							FTimerDelegate DelayedRename;
							DelayedRename.BindLambda([this, Row, OldName]()
							{
								FDataTableEditorUtils::RenameRow(EditingTable, FName(Row), FName(OldName));
								EditorContentSystem->EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
							});
							GEditor->GetEditorWorldContext().World()->GetTimerManager().SetTimerForNextTick(DelayedRename);

							bWasRenamed = false;
							//EditorContentSystem->EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
						}
						else
						{
							FName FixedName = FName(Obj->BuildContentTypeString() + TEXT(".") + Row);
							if (EditingTable->FindRow<FLocalContentManifestRow>(FixedName, ""))
							{
								const auto ErrTitle = LOCTEXT("InvalidContentName", "Error - Content Already Exists");
								const auto ErrMsg = FText::FromString(FString::Format(TEXT("Content Id {0} already exists."), {FixedName.ToString()}));
								UEditorDialogLibrary::ShowMessage(ErrTitle, ErrMsg, EAppMsgType::Ok, EAppReturnType::Ok);

								// We need to delay as we can't use FDataTableEditorUtils functions without triggering another PostChange call.
								// This does not loop infinitely, but it causes a problem that gets the DataTable UI in a bad state and requires closing/opening again to fix.
								// Basically, because the call to PostChange inside RenameRow runs before the rest of this first chain of PostChange invocations, the UI's PostChange
								// callback for the RenameRow chain gets run before the one for the original change here. This causes all sorts of problems.
								FTimerDelegate DelayedRename;
								DelayedRename.BindLambda([this, Row, OldName]()
								{
									FDataTableEditorUtils::RenameRow(EditingTable, FName(Row), FName(OldName));
									EditorContentSystem->EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
								});
								GEditor->GetEditorWorldContext().World()->GetTimerManager().SetTimerForNextTick(DelayedRename);
								bWasRenamed = false;
							}
							else
							{
								const auto UserInputNewNameRow = EditingTable->FindRow<FLocalContentManifestRow>(FName(Row), "");
								EditingTable->AddRow(FixedName, *UserInputNewNameRow);
								EditingTable->RemoveRow(FName(Row));
								Row = FixedName.ToString();
								EntryInManifest = EditingTable->FindRow<FLocalContentManifestRow>(FixedName, "");
								TypeTag = EntryInManifest->Tags.FindByPredicate([](FString Tag) { return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type); });
								EditorContentSystem->EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
								bWasRenamed = true;
							}
						}
					}
				}


				if (bWasRenamed)
				{
					const auto OldPath = EntryInManifest->JsonBlobPath;
					const auto NewPath = GetJsonBlobPath(Row);
					if (IFileManager::Get().Move(*NewPath, *OldPath))
					{
						EntryInManifest->JsonBlobPath = NewPath;
						UE_LOG(LogBeamContent, Display, TEXT("Content Renamed. Moving JsonBlob from %s to %s."),
						       *OldPath,
						       *EntryInManifest->JsonBlobPath);
					}
				}
			}

			// Handle custom validation case
			const auto TypeName = UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag);
			UBeamContentObject* Obj;
			if (!EditorContentSystem->TryLoadContentObject(ManifestId, Row, TypeName, Obj))
			{
				const auto ErrTitle = LOCTEXT("NonExistentContentObject", "Error - Non-Existent Content Object");
				const auto ErrMsg = FText::FromString(
					FString::Format(TEXT("Trying to load a content object that doesn't exist {0}"), {Row}));

				UEditorDialogLibrary::ShowMessage(ErrTitle, ErrMsg, EAppMsgType::Ok, EAppReturnType::Ok);
			}
			else
			{
				// If the object was renamed, let's make sure it's in memory representation is also updated with the new Id
				if (bWasRenamed)
				{
					Obj->Id = Row;
					FString JsonContent;
					Obj->ToBasicJson(JsonContent);
					if (FFileHelper::SaveStringToFile(JsonContent, *EntryInManifest->JsonBlobPath))
					{
						EntryInManifest->Checksum = Obj->CreatePropertiesMD5Hash();
						EditorContentSystem->EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
					}
				}

				if (const auto ValidationErrorCode = Obj->IsValidRowForType(*TypeTag, *EntryInManifest);
					ValidationErrorCode)
				{
					Obj->FixManifestRowForType(ValidationErrorCode, *EntryInManifest);
				}
			}
		}
	}

	if (MissingTypeTags.Num() > 0)
	{
		const auto ErrTitle = LOCTEXT("UntypedContentObject", "Error - Untyped Content Object");
		const auto ErrMsg = FText::FromString(
			FString::Format(
				TEXT(
					"Found a content object that doesn't have a type tag. Please add a type tag in the format of \"{0}ConcreteContentTypeName\" to the manifest row: {1}."),
				{UBeamContentObject::Beam_Tag_Type, FString::Join(MissingTypeTags, TEXT(", "))}
			)
		);
		UEditorDialogLibrary::ShowMessage(ErrTitle, ErrMsg, EAppMsgType::Ok, EAppReturnType::Ok);
	}

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
	if (DataTable != EditingTable) return;

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
	const TSubclassOf<UBeamContentObject> ContentObjectSubType = EditorContentSystem->AllContentTypes[SelectedTypeIdx];
	EditingObject = NewObject<UBeamContentObject>(this, ContentObjectSubType.Get());


	// We add it to the object and to the local manifest.
	const auto TypeName = EditingObject->GetClass()->GetFName().ToString();
	const auto TypeTagVal = FString::Format(*UBeamContentObject::Beam_Tag_TypeFmt, {TypeName});

	auto RepeatedNameCount = 0;
	auto RowName = FString::Format(TEXT("{0}.New_{1}_{2}"), {
		                               EditingObject->BuildContentTypeString(), TypeName, RepeatedNameCount
	                               });
	while (EditingTable->FindRow<FLocalContentManifestRow>(FName(RowName), TEXT("Ensure Name is Unique")))
	{
		RepeatedNameCount += 1;
		RowName = FString::Format(TEXT("{0}.New_{1}_{2}"), {
			                          EditingObject->BuildContentTypeString(), TypeName, RepeatedNameCount
		                          });
	}

	// Initialize the editing Object
	FLocalContentManifestRow EntryInManifest;
	EntryInManifest.OwnerManifestId = ManifestId;
	EntryInManifest.Tags.Add(TypeTagVal);
	EntryInManifest.JsonBlobPath = GetJsonBlobPath(RowName);

	// Sets the ID and Tags based on the manifest row.
	EditingObject->Id = RowName;
	EditingObject->Tags.Append(EntryInManifest.Tags);

	FString JsonContent;
	EditingObject->ToBasicJson(JsonContent);

	const auto FilePath = GetJsonBlobPath(RowName);

	if (FFileHelper::SaveStringToFile(JsonContent, *FilePath))
	{
		EntryInManifest.Checksum = EditingObject->CreatePropertiesMD5Hash();
		EditorContentSystem->EditorAssetSubsystem->SaveLoadedAsset(EditingTable);

		// Stores the created row struct into the data table
		// We do it this way, instead of FDataTableEditorUtils::AddRow(), so that the change callback is aware of the Row data when we create a new one.
		FDataTableEditorUtils::BroadcastPreChange(EditingTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
		EditingTable->AddRow(FName(RowName), EntryInManifest);
		FDataTableEditorUtils::BroadcastPostChange(EditingTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);


		// Adds the editing object to the list of cached content objects (so that we don't need to keep deserializing it all the time).
		EditorContentSystem->LoadedContentObjects.Add(EditingObject->Id, EditingObject);

		// Saves the data-table with the new content object in it.
		EditorContentSystem->EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
	}
	else
	{
		const auto ErrTitle = LOCTEXT("NonExistentContentObject",
		                              "Error - Failed Saving Content Object");
		const auto ErrMsg = FText::FromString(
			FString::Format(TEXT("Failed to save the content object"),
			                {RowName}));

		UEditorDialogLibrary::ShowMessage(ErrTitle, ErrMsg, EAppMsgType::Ok,
		                                  EAppReturnType::Ok);
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
	auto& EntryInManifest = *EditingTable->FindRow<FLocalContentManifestRow>(SelectedRow, TEXT("Edit Content Start"));

	EditingObjectId = SelectedRow;
	const auto TypeTag = EntryInManifest.Tags.FindByPredicate([](FString Tag)
	{
		return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type);
	});
	if (!TypeTag)
	{
		const auto ErrTitle = LOCTEXT("UntypedContentObject", "Error - Untyped Content Object");
		const auto ErrMsg = FText::FromString(
			FString::Format(
				TEXT(
					"Trying to load a content object that doesn't have a type tag. Please add a type tag in the format of \"{0}ConcreteContentTypeName\" to the manifest row: {1}."),
				{UBeamContentObject::Beam_Tag_Type, SelectedRow.ToString()}
			)
		);
		UEditorDialogLibrary::ShowMessage(ErrTitle, ErrMsg, EAppMsgType::Ok, EAppReturnType::Ok);
		return;
	}

	const auto TypeName = UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag);
	if (!EditorContentSystem->TryLoadContentObject(ManifestId, EditingObjectId, TypeName, EditingObject))
	{
		const auto ErrTitle = LOCTEXT("NonExistentContentObject", "Error - Non-Existent Content Object");
		const auto ErrMsg = FText::FromString(
			FString::Format(TEXT("Trying to load a content object that doesn't exist {0}"), {SelectedRow.ToString()}));
		UEditorDialogLibrary::ShowMessage(ErrTitle, ErrMsg, EAppMsgType::Ok, EAppReturnType::Ok);
		return;
	}

	// Show the editing window.
	EditingObjectDetailsPanel->SetObject(EditingObject);
	EditingWindow = SNew(SWindow)
		.ClientSize({512, 768})
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
				             .OnClicked_Lambda([this, &SelectedRow, &EntryInManifest]
				             {
					             FString JsonContent;
					             EditingObject->ToBasicJson(JsonContent);

					             const auto FilePath = GetJsonBlobPath(SelectedRow.ToString());
					             if (FFileHelper::SaveStringToFile(JsonContent, *FilePath))
					             {
						             EntryInManifest.Checksum = EditingObject->CreatePropertiesMD5Hash();
						             EditorContentSystem->EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
						             FDataTableEditorUtils::BroadcastPostChange(
							             EditingTable, FDataTableEditorUtils::EDataTableChangeInfo::RowData);

						             // Close the window
						             EditingWindow->RequestDestroyWindow();
						             return FReply::Handled();
					             }

					             const auto ErrTitle = LOCTEXT("NonExistentContentObject",
					                                           "Error - Failed Saving Content Object");
					             const auto ErrMsg = FText::FromString(
						             FString::Format(TEXT("Failed to save the content object"),
						                             {SelectedRow.ToString()}));

					             UEditorDialogLibrary::ShowMessage(ErrTitle, ErrMsg, EAppMsgType::Ok,
					                                               EAppReturnType::Ok);
					             return FReply::Handled();
				             })
			]
		]

	];
	FSlateApplication::Get().AddModalWindow(EditingWindow.ToSharedRef(),
	                                        FSlateApplication::Get().FindBestParentWindowForDialogs(
		                                        SelectedContentComboBox));
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

			SCustomDialog::FButton(LOCTEXT("ConfirmPublish", "Confirm"), FSimpleDelegate::CreateLambda(
				                       [this, RealmName]()
				                       {
					                       FBeamOperationEventHandler Handler;
					                       Handler.BindUFunction(
						                       this, GET_FUNCTION_NAME_CHECKED(
							                       ULocalContentManifestEditorState, OnPublishEvent));
					                       [[maybe_unused]] const auto Operation = EditorContentSystem->PublishManifest(
						                       ManifestId, Handler);
					                       PublishingWindow->DestroyWindowImmediately();

					                       const auto Title = LOCTEXT("PublishingWait", "Waiting for Publish");
					                       const auto Msg = FText::FromString(FString::Format(
						                       TEXT("Uploading content and manifest to Current Target Realm={0}."),
						                       {ManifestId.AsString, RealmName}));

					                       PublishingWindow = SNew(SWindow)
				.Title(Title)
				.ClientSize({512, 128})
				.Content()
					                       [
						                       SNew(SHorizontalBox)
						                       + SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
						                       [
							                       SNew(STextBlock).Text(Msg).Justification(ETextJustify::Center)
						                       ]
					                       ];

					                       // Show it as a modal of the DataTable editor.
					                       FSlateApplication::Get().AddModalWindow(
						                       PublishingWindow.ToSharedRef(),
						                       FSlateApplication::Get().FindBestParentWindowForDialogs(
							                       SelectedContentComboBox), true);
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
			if (OperationEvent.EventType == SUCCESS)
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

					DownloadingWindow = SNew(SWindow).ClientSize({512, 512}).HasCloseButton(false)
					                                 .Content()[Panel];

					// Show it as a modal of the DataTable editor.
					FSlateApplication::Get().AddModalWindow(DownloadingWindow.ToSharedRef(),
					                                        FSlateApplication::Get().FindBestParentWindowForDialogs(
						                                        SelectedContentComboBox), true);
					DownloadingWindow->ShowWindow();
				}
			}

			if (OperationEvent.EventType == ERROR)
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
	EditorContentSystem
		->
		DownloadManifest(ManifestId, EventHandler);
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

	if (OperationEvent.EventType == SUCCESS)
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
	else if (OperationEvent.EventType == ERROR)
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
