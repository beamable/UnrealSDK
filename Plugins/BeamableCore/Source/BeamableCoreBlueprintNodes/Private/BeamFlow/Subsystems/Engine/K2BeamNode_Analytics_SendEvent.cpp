#include "BeamFlow/Subsystems/Engine/K2BeamNode_Analytics_SendEvent.h"

#include "BeamK2.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "EdGraphSchema_K2.h"
#include "EdGraph/EdGraph.h"
#include "K2Node_CallFunction.h"
#include "K2Node_MakeStruct.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "KismetCompiler.h"
#include "UObject/UObjectIterator.h"

#include "Analytics/BeamAnalyticsEvent.h"
#include "Analytics/BeamAnalyticsSubsystem.h"
#include "UserSlots/UserSlot.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_Analytics_SendEvent"

const FName UK2BeamNode_Analytics_SendEvent::PN_ContextObject = FName(TEXT("ContextObject"));
const FName UK2BeamNode_Analytics_SendEvent::PN_UserSlot = FName(TEXT("UserSlot"));
const FName UK2BeamNode_Analytics_SendEvent::PN_Result = FName(TEXT("Success"));

FText UK2BeamNode_Analytics_SendEvent::GetNodeTitle(ENodeTitleType::Type /*TitleType*/) const
{
	if (SelectedEventType)
	{
		return FText::Format(LOCTEXT("TitleFmt", "Send Beam Analytics Event ({0})"),
			FText::FromString(SelectedEventType->GetName()));
	}
	return LOCTEXT("Title", "Send Beam Analytics Event");
}

FText UK2BeamNode_Analytics_SendEvent::GetTooltipText() const
{
	return LOCTEXT("Tooltip",
		"Enqueue a typed analytics event into UBeamAnalyticsSubsystem. Pick the event "
		"type from the Details panel; the node exposes a pin for each field of the chosen struct.");
}

FText UK2BeamNode_Analytics_SendEvent::GetMenuCategory() const
{
	return LOCTEXT("Category", "Beam|Analytics");
}

FSlateIcon UK2BeamNode_Analytics_SendEvent::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = FLinearColor::FromSRGBColor(FColor::FromHex("#826CCF"));
	return FSlateIcon(TEXT("BeamableCore"), "BeamIconSmall");
}

FLinearColor UK2BeamNode_Analytics_SendEvent::GetNodeTitleColor() const
{
	return FLinearColor::FromSRGBColor(FColor::FromHex("#674CC5"));
}

void UK2BeamNode_Analytics_SendEvent::AllocateDefaultPins()
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Exec / Then.
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	// Result bool.
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Boolean, PN_Result);

	// ContextObject (defaults to self via DefaultToSelf on the underlying function meta).
	UEdGraphPin* ContextPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObject::StaticClass(), PN_ContextObject);
	ContextPin->bAdvancedView = true;

	// UserSlot — advanced display, defaults to empty (= owner slot at runtime).
	UEdGraphPin* UserSlotPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FUserSlot::StaticStruct(), PN_UserSlot);
	UserSlotPin->bAdvancedView = true;

	if (AdvancedPinDisplay == ENodeAdvancedPins::NoPins)
	{
		AdvancedPinDisplay = ENodeAdvancedPins::Hidden;
	}

	CreatePinsForEventType();
}

void UK2BeamNode_Analytics_SendEvent::CreatePinsForEventType()
{
	if (!SelectedEventType) return;

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// One input pin per UPROPERTY on the struct (parent fields included).
	// Skip the Version field — it is set by the struct's default value at construction time.
	for (TFieldIterator<FProperty> It(SelectedEventType); It; ++It)
	{
		const FProperty* Prop = *It;
		if (!Prop) continue;
		if (Prop->GetFName() == TEXT("Version")) continue;
		if (Prop->HasAnyPropertyFlags(CPF_Transient)) continue;

		FEdGraphPinType PinType;
		if (!K2Schema->ConvertPropertyToPinType(Prop, /*out*/ PinType)) continue;

		UEdGraphPin* Pin = CreatePin(EGPD_Input, PinType, Prop->GetFName());
		if (Pin && Prop->HasMetaData(TEXT("ToolTip")))
		{
			Pin->PinToolTip = Prop->GetMetaData(TEXT("ToolTip"));
		}
	}
}

void UK2BeamNode_Analytics_SendEvent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.Property &&
	    PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UK2BeamNode_Analytics_SendEvent, SelectedEventType))
	{
		ReconstructNode();
		if (UBlueprint* BP = FBlueprintEditorUtils::FindBlueprintForNode(this))
		{
			FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(BP);
		}
	}
}

void UK2BeamNode_Analytics_SendEvent::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		// A single generic spawner. The user picks the event type via the Details panel
		// after dropping the node. Dropdown discovery happens through the property
		// editor for SelectedEventType (TObjectPtr<UScriptStruct>).
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);
		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

void UK2BeamNode_Analytics_SendEvent::BuildCallsiteLiterals(FString& OutFile, int32& OutLine, FString& OutFunction) const
{
	OutFile = FString();
	if (UEdGraph* Graph = GetGraph())
	{
		OutFile = Graph->GetPathName();
	}
	if (!OutFile.IsEmpty())
	{
		OutFile += TEXT(":") + NodeGuid.ToString();
	}
	else
	{
		OutFile = NodeGuid.ToString();
	}

	OutLine = 0;

	OutFunction = FString();
	if (UEdGraph* Graph = GetGraph())
	{
		OutFunction = Graph->GetName();
	}
}

void UK2BeamNode_Analytics_SendEvent::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UK2Node::ExpandNode(CompilerContext, SourceGraph);

	if (!SelectedEventType)
	{
		CompilerContext.MessageLog.Error(
			*LOCTEXT("MissingType", "@@: Select an event type in the Details panel.").ToString(), this);
		return;
	}
	if (!SelectedEventType->IsChildOf(FBeamAnalyticsEvent::StaticStruct()))
	{
		CompilerContext.MessageLog.Error(
			*LOCTEXT("WrongType", "@@: Selected struct does not derive from FBeamAnalyticsEvent.").ToString(), this);
		return;
	}

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// 1) Spawn a MakeStruct for the chosen type.
	UK2Node_MakeStruct* MakeStruct = CompilerContext.SpawnIntermediateNode<UK2Node_MakeStruct>(this, SourceGraph);
	MakeStruct->StructType = SelectedEventType;
	MakeStruct->AllocateDefaultPins();

	// 2) Spawn GetSelf to resolve the subsystem instance. GetSelf takes a
	//    UObject* CallingContext that we wire from our node's ContextObject
	//    pin (defaulted to self at the call site).
	UK2Node_CallFunction* CallGetSelf = BeamK2::CreateCallFunctionNode(
		this, CompilerContext, SourceGraph,
		GET_FUNCTION_NAME_CHECKED(UBeamAnalyticsSubsystem, GetSelf),
		UBeamAnalyticsSubsystem::StaticClass());

	if (UEdGraphPin* GetSelfCtxPin = CallGetSelf->FindPin(TEXT("CallingContext")))
	{
		CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(PN_ContextObject), *GetSelfCtxPin);
	}

	// 3) Spawn the K2 enqueue thunk call. Self target = result of GetSelf.
	UK2Node_CallFunction* CallEnqueue = BeamK2::CreateCallFunctionNode(
		this, CompilerContext, SourceGraph,
		GET_FUNCTION_NAME_CHECKED(UBeamAnalyticsSubsystem, K2_EnqueueAnalyticsEvent),
		UBeamAnalyticsSubsystem::StaticClass());

	UEdGraphPin* GetSelfReturn = CallGetSelf->GetReturnValuePin();
	UEdGraphPin* EnqueueSelf = CallEnqueue->FindPin(UEdGraphSchema_K2::PN_Self);
	if (GetSelfReturn && EnqueueSelf)
	{
		K2Schema->TryCreateConnection(GetSelfReturn, EnqueueSelf);
	}

	// Move our exec to CallEnqueue exec; CallEnqueue then -> our then.
	CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *CallEnqueue->GetExecPin());
	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(UEdGraphSchema_K2::PN_Then), *CallEnqueue->GetThenPin());

	// Wire result.
	if (UEdGraphPin* CallReturn = CallEnqueue->GetReturnValuePin())
	{
		CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(PN_Result), *CallReturn);
	}

	// Wire UserSlot. (No more ContextObject param on K2_EnqueueAnalyticsEvent —
	// the subsystem instance is already resolved via GetSelf.)
	if (UEdGraphPin* SlotIn = CallEnqueue->FindPin(TEXT("Slot")))
	{
		CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(PN_UserSlot), *SlotIn);
	}

	// Inject literal callsite strings.
	FString CallsiteFile, CallsiteFunction;
	int32 CallsiteLine = 0;
	BuildCallsiteLiterals(CallsiteFile, CallsiteLine, CallsiteFunction);

	if (UEdGraphPin* P = CallEnqueue->FindPin(TEXT("BlueprintCallsiteFile"))) P->DefaultValue = CallsiteFile;
	if (UEdGraphPin* P = CallEnqueue->FindPin(TEXT("BlueprintCallsiteLine"))) P->DefaultValue = FString::FromInt(CallsiteLine);
	if (UEdGraphPin* P = CallEnqueue->FindPin(TEXT("BlueprintCallsiteFunction"))) P->DefaultValue = CallsiteFunction;

	// 4) Wire each user-supplied input pin to the corresponding MakeStruct member pin.
	for (TFieldIterator<FProperty> It(SelectedEventType); It; ++It)
	{
		const FProperty* Prop = *It;
		if (!Prop) continue;
		if (Prop->GetFName() == TEXT("Version")) continue;
		if (Prop->HasAnyPropertyFlags(CPF_Transient)) continue;

		UEdGraphPin* MyPin = FindPin(Prop->GetFName());
		UEdGraphPin* MakePin = MakeStruct->FindPin(Prop->GetFName());
		if (MyPin && MakePin)
		{
			CompilerContext.MovePinLinksToIntermediate(*MyPin, *MakePin);
		}
	}

	// 5) Connect MakeStruct output to the wildcard EventStruct pin on CallEnqueue.
	UEdGraphPin* MakeOut = nullptr;
	for (UEdGraphPin* P : MakeStruct->Pins)
	{
		if (P && P->Direction == EGPD_Output && P->PinType.PinSubCategoryObject == SelectedEventType)
		{
			MakeOut = P;
			break;
		}
	}
	UEdGraphPin* EventStructPin = CallEnqueue->FindPin(TEXT("EventStruct"));
	if (MakeOut && EventStructPin)
	{
		// The wildcard pin's type may need to be set from the source struct so the
		// connection is accepted by the schema.
		EventStructPin->PinType.PinCategory = UEdGraphSchema_K2::PC_Struct;
		EventStructPin->PinType.PinSubCategoryObject = SelectedEventType;
		K2Schema->TryCreateConnection(MakeOut, EventStructPin);
	}
	else
	{
		CompilerContext.MessageLog.Error(
			*LOCTEXT("WireFail", "@@: Failed to wire MakeStruct output to enqueue call.").ToString(), this);
	}

	BreakAllNodeLinks();
}

#undef LOCTEXT_NAMESPACE
