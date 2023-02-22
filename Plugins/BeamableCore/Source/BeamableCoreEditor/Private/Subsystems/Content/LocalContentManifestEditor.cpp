#include "Subsystems/Content/LocalContentManifestEditor.h"

#include "BeamableCoreEditorCommands.h"
#include "IDataTableEditor.h"
#include "Dialog/SCustomDialog.h"
#include "Subsystems/Content/BeamEditorContent.h"
#include "EditorScriptingUtilities/Public/EditorDialogLibrary.h"

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

	// Extend the UV section of the toolbar:	
	auto ToolbarExtender = MakeShared<FExtender>();
	ToolbarExtender->AddToolBarExtension("DataTableCommands", EExtensionHook::After, DataTableEditorCommands,
	                                     FToolBarExtensionDelegate::CreateUObject(this, &ULocalContentManifestEditorState::AddDataTableToolbarExtension));
	Editor->AddToolbarExtender(ToolbarExtender);
	Editor->RegenerateMenusAndToolbars();

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::ENameAreaSettings::HideNameArea;
	DetailsViewArgs.bHideSelectionTip = true;

	EditingObjectDetailsPanel = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	EditingObjectDetailsPanel->SetObject(nullptr);
}


void ULocalContentManifestEditorState::PreChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo ChangedType)
{
}

void ULocalContentManifestEditorState::PostChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo ChangedType)
{
	// Things that implement FDataTableEditorUtils::FDataTableEditorManager::ListenerType get instantiated automagically by
	// UE's listener system. This means we'll have one instance of this listener that is never set up properly by our DataTable Asset Opened Handler.
	// So... we early out in that case.
	if (!EditorContentSystem) return;

	// We also early out if the selection was changed in a data table that is not the one being managed by this editor.
	if (Changed != EditingTable) return;

	if (ChangedType == FDataTableEditorUtils::EDataTableChangeInfo::RowList)
	{
		RebuildContentNamesForTable();
		SelectedContentIdx = FMath::Clamp(SelectedContentIdx, 0, EditingTableContentNames.Num());

		const auto Rows = Changed->GetRowNames();
		TArray<FString> MissingTypeTags;
		for (const auto& Row : Rows)
		{
			const auto SelectedRow = Row;
			const auto EntryInManifest = EditingTable->FindRow<FLocalContentManifestRow>(SelectedRow, TEXT("Validating Manifest"));

			const auto TypeTag = EntryInManifest->Tags.FindByPredicate([](FString Tag) { return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type); });
			if (!TypeTag)
			{
				MissingTypeTags.Add(SelectedRow.ToString());
			}
			else
			{
				const auto TypeName = UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag);
				UBeamContentObject* Obj;
				if (!EditorContentSystem->TryLoadContentObject(ManifestId, SelectedRow, TypeName, Obj))
				{
					const auto ErrTitle = LOCTEXT("NonExistentContentObject", "Error - Non-Existent Content Object");
					const auto ErrMsg = FText::FromString(FString::Format(TEXT("Trying to load a content object that doesn't exist {0}"), {SelectedRow.ToString()}));
					UEditorDialogLibrary::ShowMessage(ErrTitle, ErrMsg, EAppMsgType::Ok, EAppReturnType::Ok);
				}
				else
				{
					if (const auto ValidationErrorCode = Obj->IsValidRowForType(*TypeTag, EntryInManifest); ValidationErrorCode)
					{
						Obj->FixManifestRowForType(ValidationErrorCode, EntryInManifest);
					}
				}
			}
		}

		if (MissingTypeTags.Num() > 0)
		{
			const auto ErrTitle = LOCTEXT("UntypedContentObject", "Error - Untyped Content Object");
			const auto ErrMsg = FText::FromString(
				FString::Format(
					TEXT("Found a content object that doesn't have a type tag. Please add a type tag in the format of \"{0}ConcreteContentTypeName\" to the manifest row: {1}."),
					{UBeamContentObject::Beam_Tag_Type, FString::Join(MissingTypeTags, TEXT(", "))}
				)
			);
			UEditorDialogLibrary::ShowMessage(ErrTitle, ErrMsg, EAppMsgType::Ok, EAppReturnType::Ok);
		}
	}
}


void ULocalContentManifestEditorState::SelectionChange(const UDataTable* DataTable, FName RowName)
{
	// Things that implement FDataTableEditorUtils::FDataTableEditorManager::ListenerType get instantiated automagically by
	// UE's listener system. This means we'll have one instance of this listener that is never set up properly by our DataTable Asset Opened Handler.
	// So... we early out in that case.
	if (!EditorContentSystem) return;

	// We also early out if the selection was changed in a data table that is not the one being managed by this editor.
	if (DataTable != EditingTable) return;

	const auto Asd = EditingTableContentNames.FindLastByPredicate([RowName](TSharedPtr<FName> R) { return R->IsEqual(RowName); });
	SelectedContentComboBox->SetSelectedItem(EditingTableContentNames[Asd]);
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
		                                               SelectedTypeIdx = EditorContentSystem->AllContentTypeNames.FindLast(Name);
	                                               });

	Builder.AddSeparator();
	Builder.AddToolBarButton(FBeamableCoreEditorCommands::Get().CreateContentObjectInLocalManifest, NAME_None, LOCTEXT("CreateContentButtonTxt", "Create Content of Type: "));
	Builder.AddWidget(SelectedTypeComboBox.ToSharedRef());


	// Add Edit / Select Content Dropdown / Remove Buttons
	Builder.AddToolBarButton(FBeamableCoreEditorCommands::Get().EditContentObjectInLocalManifest, NAME_None, LOCTEXT("EditContentButtonTxt", "Edit Content: "));

	// Fill out the content names for the current editing table
	RebuildContentNamesForTable();

	// Prepare the content combo box TODO: Change this once UE fixes/exposes callbacks so that we can hook into the DataTable's own select/rename/duplicate row callbacks.
	SAssignNew(SelectedContentComboBox, SNameComboBox)
	.InitiallySelectedItem(EditingTableContentNames[SelectedContentIdx])
	.OptionsSource(&EditingTableContentNames)
	.OnSelectionChanged_Lambda([this](TSharedPtr<FName, ESPMode::ThreadSafe> Name, ESelectInfo::Type T)
	                                                  {
		                                                  SelectedContentIdx = EditingTableContentNames.FindLast(Name);
	                                                  });

	Builder.AddWidget(SelectedContentComboBox.ToSharedRef());

	Builder.AddToolBarButton(FBeamableCoreEditorCommands::Get().PublishManifest, NAME_None, LOCTEXT("PublishButtonTxt", "Publish"));
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
	auto RowName = FString::Format(TEXT("New_{0}_{1}"), {TypeName, RepeatedNameCount});
	while (EditingTable->FindRow<FLocalContentManifestRow>(FName(RowName), TEXT("Ensure Name is Unique")))
	{
		RepeatedNameCount += 1;
		RowName = FString::Format(TEXT("New_{0}_{1}"), {TypeName, RepeatedNameCount});
	}

	// Initialize the editing Object
	FLocalContentManifestRow Row;
	Row.OwnerManifestId = ManifestId;
	EditingObject->BuildManifestRow(TypeTagVal, RowName, &Row);

	// Sets the ID and Tags based on the manifest row.
	EditingObject->Id = RowName;
	EditingObject->Tags.Append(Row.Tags);

	// Stores the created row struct into the data table
	// We do it this way, instead of FDataTableEditorUtils::AddRow(), so that the change callback is aware of the Row data when we create a new one.
	EditingTable->AddRow(FName(RowName), Row);
	FDataTableEditorUtils::BroadcastPostChange(EditingTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);


	// Adds the editing object to the list of cached content objects (so that we don't need to keep deserializing it all the time).
	EditorContentSystem->LoadedContentObjects.Add(EditingObject->Id, EditingObject);

	// Saves the data-table with the new content object in it.
	EditorContentSystem->EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
}

void ULocalContentManifestEditorState::EditContentButtonClicked()
{
	if (SelectedContentIdx == 0)
	{
		const auto ErrTitle = LOCTEXT("NonExistentContentObject", "Error - Non-Existent Content Object");
		const auto ErrMsg = FText::FromString(TEXT("Trying to load a content object that doesn't exist.\nPlease select a valid content from the dropdown."));
		UEditorDialogLibrary::ShowMessage(ErrTitle, ErrMsg, EAppMsgType::Ok, EAppReturnType::Ok);
		return;
	}

	const auto SelectedRow = EditingTable->GetRowNames()[SelectedContentIdx - 1];
	auto& EntryInManifest = *EditingTable->FindRow<FLocalContentManifestRow>(SelectedRow, TEXT("Edit Content Start"));

	EditingObjectId = SelectedRow;
	const auto TypeTag = EntryInManifest.Tags.FindByPredicate([](FString Tag) { return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type); });
	if (!TypeTag)
	{
		const auto ErrTitle = LOCTEXT("UntypedContentObject", "Error - Untyped Content Object");
		const auto ErrMsg = FText::FromString(
			FString::Format(
				TEXT("Trying to load a content object that doesn't have a type tag. Please add a type tag in the format of \"{0}ConcreteContentTypeName\" to the manifest row: {1}."),
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
		const auto ErrMsg = FText::FromString(FString::Format(TEXT("Trying to load a content object that doesn't exist {0}"), {SelectedRow.ToString()}));
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
				             .OnClicked_Lambda([this, &EntryInManifest]
				             {
					             UE_LOG(LogBeamContent, Display, TEXT("Clicked Save!!!!"))
					             EditingObject->ToBasicJson(EntryInManifest.JsonBlob);
					             EntryInManifest.Checksum = EditingObject->CreatePropertiesMD5Hash();
					             EditorContentSystem->EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
					             FSlateApplication::Get().FindBestParentWindowForDialogs(SelectedContentComboBox)->Invalidate(EInvalidateWidgetReason::Paint);
					             EditingWindow->RequestDestroyWindow();
					             return FReply::Handled();
				             })
			]
		]

	];
	FSlateApplication::Get().AddModalWindow(EditingWindow.ToSharedRef(), FSlateApplication::Get().FindBestParentWindowForDialogs(SelectedContentComboBox));
}

void ULocalContentManifestEditorState::PublishButtonClicked()
{
	FBeamOperationEventHandler Handler;
	Handler.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ULocalContentManifestEditorState, OnPublishEvent));
	const auto Operation = EditorContentSystem->PublishManifest(ManifestId, Handler);
}

void ULocalContentManifestEditorState::OnPublishEvent(const TArray<FUserSlot>& UserSlots, FBeamOperationEvent OperationEvent)
{
	if (OperationEvent.EventType == SUCCESS)
	{
		UE_LOG(LogBeamContent, Display, TEXT("Content Publish sucessfull!\n%s"), *OperationEvent.EventData);		
	}
	else if (OperationEvent.EventType == ERROR)
	{
		UE_LOG(LogBeamContent, Error, TEXT("Content Publish Had error %s."), *OperationEvent.EventData);
	}
	else
	{
		UE_LOG(LogBeamContent, Display, TEXT("Content Publish was Cancelled."))
	}
}

#undef LOCTEXT_NAMESPACE
