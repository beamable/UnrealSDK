#include "BeamableCoreEditor.h"

#include "BeamableCoreEditorCommands.h"
#include "BeamEditorSettings.h"
#include "BeamableCoreGraphWidgetFactory.h"
#include "BeamableEditorBlueprintLibrary.h"
#include "BlueprintActionDatabase.h"
#include "DataTableEditorModule.h"
#include "EdGraphSchema_K2_Actions.h"
#include "IDataTableEditor.h"
#include "K2Node_GetSubsystem.h"
#include "LevelEditor.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetTypeActions/AssetTypeActions_DataAsset.h"
#include "AutoGen/Optionals/OptionalArrayOfBeamGamerTag.h"
#include "AutoGen/Optionals/OptionalArrayOfBeamTag.h"
#include "BeamBackend/ReplacementTypes/BeamClientPermission.h"
#include "BeamFlow/K2BeamNode_EventUnregister.h"
#include "Content/BeamContentTypes/BeamListingContent.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "PropertyType/BeamClientPermissionCustomization.h"
#include "PropertyType/BeamContentIdCustomization.h"
#include "PropertyType/FBeamOptionalCustomization.h"
#include "PropertyType/FDocsPageItemCustomization.h"
#include "PropertyType/RequestTypeCustomization.h"
#include "PropertyType/UK2BeamEventRegisterCustomization.h"
#include "PropertyType/UK2BeamEventUnregisterCustomization.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/Content/BeamEditorContent.h"
#include "Toolkits/AssetEditorToolkit.h"

#if WITH_EDITOR

#define LOCTEXT_NAMESPACE "FBeamableCoreEditorModule"

class FAssetTypeActions_BeamRuntimeSubsystem : public FAssetTypeActions_DataAsset
{
public:
	virtual FText GetName() const override { return LOCTEXT("AssetTypeActions_BeamRuntimeSubsystem", "Beamable Runtime Subsystem"); }
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Blueprint; }
	virtual FColor GetTypeColor() const override { return FColor(63, 126, 255); }
	virtual UClass* GetSupportedClass() const override { return UBeamRuntimeSubsystem::StaticClass(); }
};

#endif

void FBeamableCoreEditorModule::StartupModule()
{
	// create your factories and shared pointer to them.
	TSharedPtr<FBeamableCorePinFactory> PinFactory = MakeShareable(new FBeamableCorePinFactory());
	TSharedPtr<FBeamableCoreGraphNodeFactory> NodeFactory = MakeShareable(new FBeamableCoreGraphNodeFactory());

	// and now register them.
	FEdGraphUtilities::RegisterVisualPinFactory(PinFactory);
	FEdGraphUtilities::RegisterVisualNodeFactory(NodeFactory);

	FBeamableCoreEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FBeamableCoreEditorCommands::Get().OpenBeamableWindowCommand,
		FExecuteAction::CreateRaw(this, &FBeamableCoreEditorModule::OpenMainBeamableWindow)
	);

	auto& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedPtr<FExtender> NewToolbarExtender = MakeShareable<FExtender>(new FExtender());
	NewToolbarExtender->AddToolBarExtension("ProjectSettings", EExtensionHook::Before,
	                                        PluginCommands, FToolBarExtensionDelegate::CreateStatic(&FBeamableCoreEditorModule::AddBeamableButtons));

	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(NewToolbarExtender);

	// Set up PropertyCustomizations
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

		// to register our custom property
		PropertyModule.RegisterCustomClassLayout(
			// This is the name of the Struct this tells the property editor which is the struct property our customization will applied on.
			UK2BeamNode_EventRegister::StaticClass()->GetFName(),
			// this is where our MakeInstance() method is useful
			FOnGetDetailCustomizationInstance::CreateStatic(&UK2BeamEventRegisterCustomization::MakeInstance));

		// to register our custom property
		PropertyModule.RegisterCustomClassLayout(
			// This is the name of the Struct this tells the property editor which is the struct property our customization will applied on.
			UK2BeamNode_EventUnregister::StaticClass()->GetFName(),
			// this is where our MakeInstance() method is useful
			FOnGetDetailCustomizationInstance::CreateStatic(&UK2BeamEventUnregisterCustomization::MakeInstance));

		// to register our custom property
		PropertyModule.RegisterCustomPropertyTypeLayout(
			// This is the name of the Struct this tells the property editor which is the struct property our customization will applied on.
			FRequestType::StaticStruct()->GetFName(),
			// this is where our MakeInstance() method is useful
			FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FRequestTypeCustomization::MakeInstance));

		PropertyModule.RegisterCustomPropertyTypeLayout(
			// This is the name of the Struct this tells the property editor which is the struct property our customization will applied on.
			FBeamClientPermission::StaticStruct()->GetFName(),
			// this is where our MakeInstance() method is useful
			FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FBeamClientPermissionCustomization::MakeInstance));

		// to register our custom property
		PropertyModule.RegisterCustomPropertyTypeLayout(
			// This is the name of the Struct this tells the property editor which is the struct property our customization will applied on.
			FBeamContentId::StaticStruct()->GetFName(),
			// this is where our MakeInstance() method is useful
			FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FBeamContentIdCustomization::MakeInstance));

		// to register our custom property
		PropertyModule.RegisterCustomPropertyTypeLayout(
			// This is the name of the Struct this tells the property editor which is the struct property our customization will applied on.
			FDocsPageItem::StaticStruct()->GetFName(),
			// this is where our MakeInstance() method is useful
			FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDocsPageItemCustomization::MakeInstance));

		// to register our custom property
		PropertyModule.RegisterCustomPropertyTypeLayout(
			// This is the name of the Struct this tells the property editor which is the struct property our customization will applied on.
			FBeamContentLink::StaticStruct()->GetFName(),
			// this is where our MakeInstance() method is useful
			FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FBeamContentIdCustomization::MakeInstance));

		// To register the FOptional properties
		for (TObjectIterator<UStruct> It; It; ++It)
		{
			UStruct* Struct = *It;

			// Make sure it's a child of FBeamOptional, not the base struct itself
			if (Struct->IsChildOf(FBeamOptional::StaticStruct()) &&
				Struct != FBeamOptional::StaticStruct())
			{
				PropertyModule.RegisterCustomPropertyTypeLayout(
					// This is the name of the Struct this tells the property editor which is the struct property our customization will applied on.
					Struct->GetFName(),
					// this is where our MakeInstance() method is useful
					FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FBeamOptionalCustomization::MakeInstance));
			}
		}

		PropertyModule.NotifyCustomizationModuleChanged();
	}

	// Set up Custom Asset Types
	{
		if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
		{
			BeamRuntimeContentCacheAssetTypeActions = MakeShared<FBeamRuntimeContentCacheAssetTypeActions>();
			FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(BeamRuntimeContentCacheAssetTypeActions.ToSharedRef());
		}
	}

	// 
	{
#if WITH_EDITOR
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		//AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Beamable")), LOCTEXT("BeamableCategory", "Beamable"));
		RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_BeamRuntimeSubsystem()));
#endif
	}
}


void FBeamableCoreEditorModule::ShutdownModule()
{
	FBeamableCoreEditorCommands::Unregister();

	// Clean up PropertyCustomizations
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		// unregister properties when the module is shutdown
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomPropertyTypeLayout(FRequestType::StaticStruct()->GetFName());
		PropertyModule.UnregisterCustomPropertyTypeLayout(FBeamClientPermission::StaticStruct()->GetFName());
		PropertyModule.UnregisterCustomPropertyTypeLayout(FBeamContentId::StaticStruct()->GetFName());


		PropertyModule.NotifyCustomizationModuleChanged();
	}

	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(BeamRuntimeContentCacheAssetTypeActions.ToSharedRef());
	}

#if WITH_EDITOR

	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (auto CreatedAssetTypeAction : CreatedAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeAction.ToSharedRef());
		}
	}
	CreatedAssetTypeActions.Empty();

#endif
}

void FBeamableCoreEditorModule::AddBeamableButtons(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FBeamableCoreEditorCommands::Get().OpenBeamableWindowCommand, NAME_None,
	                         LOCTEXT("Beamable", "Beamable"), LOCTEXT("BeamableTooltip", "Opens the Beamable Window"),
	                         FSlateIcon(FName(TEXT("BeamableCore")), FName(TEXT("BeamIcon"))));
}

void FBeamableCoreEditorModule::OpenMainBeamableWindow() const
{
	UBeamableEditorBlueprintLibrary::StartEditorWidget(GetDefault<UBeamEditorSettings>()->BeamableMainWindow.LoadSynchronous());
}


#if WITH_EDITOR

void FBeamableCoreEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

UEdGraphNode* FBeamableCoreEditorModule::CreateNewGraphNodeFromTemplate(UK2Node* NodeTemplate, UEdGraph* InGraph, const FVector2D& GraphLocation, UEdGraphPin* ConnectPin)
{
	TSharedPtr<FEdGraphSchemaAction_K2NewNode> Action = MakeShared<FEdGraphSchemaAction_K2NewNode>(FText::GetEmpty(), FText::GetEmpty(), FText::GetEmpty(), 0);
	Action->NodeTemplate = NodeTemplate;
	return Action->PerformAction(InGraph, ConnectPin, GraphLocation, false);
}

UEdGraphNode* FBeamableCoreEditorModule::CreatePostBeginPlayEvent(UBlueprint* InBlueprint, UEdGraph* InGraph, FName InMemberName, const FVector2D& GraphLocation, TSubclassOf<UObject> InMemberParentClass)
{
	UEdGraph* TempOuter = NewObject<UEdGraph>((UObject*)InBlueprint);
	TempOuter->SetFlags(RF_Transient);

	UK2Node_Event* NewEventNode = NewObject<UK2Node_Event>(TempOuter);
	NewEventNode->EventReference.SetExternalMember(InMemberName, InMemberParentClass);
	NewEventNode->bOverrideFunction = true;

	UK2Node_Event* ExistingEvent = FBlueprintEditorUtils::FindOverrideForFunction(InBlueprint, NewEventNode->EventReference.GetMemberParentClass(NewEventNode->GetBlueprintClassFromNode()),
	                                                                              NewEventNode->EventReference.GetMemberName());

	if (!ExistingEvent)
	{
		return CreateNewGraphNodeFromTemplate(NewEventNode, InGraph, GraphLocation);
	}
	return ExistingEvent;
}

UBeamRuntimeSubsystemAction_Factory::UBeamRuntimeSubsystemAction_Factory(const class FObjectInitializer& OBJ) : Super(OBJ)
{
	SupportedClass = UBeamRuntimeSubsystem::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UBeamRuntimeSubsystemAction_Factory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(UBeamRuntimeSubsystem::StaticClass()));
	UBlueprint* NewBlueprint = FKismetEditorUtilities::CreateBlueprint(Class, InParent, Name, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), NAME_None);
	UEdGraph* EventGraph = FBlueprintEditorUtils::FindEventGraph(NewBlueprint);
	FBeamableCoreEditorModule::CreatePostBeginPlayEvent(NewBlueprint, EventGraph, FName(TEXT("OnBeamableReady")), FVector2D(200, 0), UBeamRuntimeSubsystem::StaticClass());
	FBlueprintActionDatabase::Get().RefreshClassActions(UK2Node_GetSubsystem::StaticClass());
	return NewBlueprint;
}

#endif

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBeamableCoreEditorModule, BeamableCoreEditor)
