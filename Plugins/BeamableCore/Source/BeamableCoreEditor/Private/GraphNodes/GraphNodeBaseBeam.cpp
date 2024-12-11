#include "GraphNodes/GraphNodeBaseBeam.h"

#include "BeamableCoreStyle.h"
#include "BeamK2.h"
#include "EditorStyleSet.h"
#include "K2Node_AddPinInterface.h"
#include "K2Node_Timeline.h"
#include "BeamFlow/K2BeamNode_BeamFlow.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/Breakpoint.h"
#include "ScopedTransaction.h"
#include "Kismet2/KismetDebugUtilities.h"


void SGraphNodeBaseBeam::Construct(const FArguments& InArgs, UEdGraphNode* InNode)
{
	bImplementsAddPinInterface = InNode->GetClass()->ImplementsInterface(UK2Node_AddPinInterface::StaticClass());
	this->GraphNode = InNode;

	this->SetCursor(EMouseCursor::CardinalCross);

	this->UpdateGraphNode();
}

inline void SGraphNodeBaseBeam::CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox)
{
	if (!bImplementsAddPinInterface)
		return;

	TSharedRef<SWidget> AddPinButton = AddPinButtonContent(
		NSLOCTEXT("SequencerNode", "SequencerNodeAddPinButton", "Add pin"),
		NSLOCTEXT("SequencerNode", "SequencerNodeAddPinButton_ToolTip", "Add new pin"));

	FMargin AddPinPadding = Settings->GetOutputPinPadding();
	AddPinPadding.Top += 6.0f;

	OutputBox->AddSlot()
	         .AutoHeight()
	         .VAlign(VAlign_Center)
	         .HAlign(HAlign_Right)
	         .Padding(AddPinPadding)
	[
		AddPinButton
	];
}

FReply SGraphNodeBaseBeam::OnAddPin()
{
	if (!bImplementsAddPinInterface)
		return FReply::Handled();

	IK2Node_AddPinInterface* AddPinNode = Cast<IK2Node_AddPinInterface>(GraphNode);
	ensure(AddPinNode);
	if (AddPinNode && AddPinNode->CanAddPin())
	{
		FScopedTransaction Transaction(NSLOCTEXT("SequencerNode", "AddPinTransaction", "Add Pin"));

		AddPinNode->AddInputPin();
		UpdateGraphNode();
		GraphNode->GetGraph()->NotifyGraphChanged();
	}

	return FReply::Handled();
}

EVisibility SGraphNodeBaseBeam::IsAddPinButtonVisible() const
{
	if (!bImplementsAddPinInterface) return EVisibility::Collapsed;

	IK2Node_AddPinInterface* AddPinNode = Cast<IK2Node_AddPinInterface>(GraphNode);
	ensure(AddPinNode);
	return ((AddPinNode && AddPinNode->CanAddPin()) ? EVisibility::Visible : EVisibility::Collapsed);
}

void SGraphNodeBaseBeam::GetOverlayBrushes(bool bSelected, const FVector2D WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const
{
	UBlueprint* OwnerBlueprint = FBlueprintEditorUtils::FindBlueprintForNode(GraphNode);

	// Search for an enabled or disabled breakpoint on this node
	FBlueprintBreakpoint* Breakpoint = OwnerBlueprint ? FKismetDebugUtilities::FindBreakpointForNode(GraphNode, OwnerBlueprint) : nullptr;
	if (Breakpoint != NULL)
	{
		FOverlayBrushInfo BreakpointOverlayInfo;

		if (Breakpoint->IsEnabledByUser())
		{
			BreakpointOverlayInfo.Brush = FAppStyle::GetBrush(FKismetDebugUtilities::IsBreakpointValid(*Breakpoint)
				                                                     ? TEXT("Kismet.DebuggerOverlay.Breakpoint.EnabledAndValid")
				                                                     : TEXT("Kismet.DebuggerOverlay.Breakpoint.EnabledAndInvalid"));
		}
		else
		{
			BreakpointOverlayInfo.Brush = FAppStyle::GetBrush(TEXT("Kismet.DebuggerOverlay.Breakpoint.Disabled"));
		}

		if (BreakpointOverlayInfo.Brush != NULL)
		{
			BreakpointOverlayInfo.OverlayOffset -= BreakpointOverlayInfo.Brush->ImageSize / 2.f;
		}

		Brushes.Add(BreakpointOverlayInfo);
	}

	// Is this the current instruction?
	if (FKismetDebugUtilities::GetCurrentInstruction() == GraphNode)
	{
		FOverlayBrushInfo IPOverlayInfo;

		// Pick icon depending on whether we are on a hit breakpoint
		const bool bIsOnHitBreakpoint = FKismetDebugUtilities::GetMostRecentBreakpointHit() == GraphNode;

		IPOverlayInfo.Brush = FAppStyle::GetBrush(bIsOnHitBreakpoint ? TEXT("Kismet.DebuggerOverlay.InstructionPointerBreakpoint") : TEXT("Kismet.DebuggerOverlay.InstructionPointer"));

		if (IPOverlayInfo.Brush != NULL)
		{
			float Overlap = 10.f;
			IPOverlayInfo.OverlayOffset.X = (WidgetSize.X / 2.f) - (IPOverlayInfo.Brush->ImageSize.X / 2.f);
			IPOverlayInfo.OverlayOffset.Y = (Overlap - IPOverlayInfo.Brush->ImageSize.Y);
		}

		IPOverlayInfo.AnimationEnvelope = FVector2D(0.f, 10.f);

		Brushes.Add(IPOverlayInfo);
	}

	// @todo remove if Timeline nodes are rendered in their own slate widget
	if (const UK2Node_Timeline* Timeline = Cast<const UK2Node_Timeline>(GraphNode))
	{
		float Offset = 0.0f;
		if (Timeline && Timeline->bAutoPlay)
		{
			FOverlayBrushInfo IPOverlayInfo;
			IPOverlayInfo.Brush = FAppStyle::GetBrush(TEXT("Graph.Node.Autoplay"));

			if (IPOverlayInfo.Brush != NULL)
			{
				const float Padding = 2.5f;
				IPOverlayInfo.OverlayOffset.X = WidgetSize.X - IPOverlayInfo.Brush->ImageSize.X - Padding;
				IPOverlayInfo.OverlayOffset.Y = Padding;
				Offset = IPOverlayInfo.Brush->ImageSize.X;
			}
			Brushes.Add(IPOverlayInfo);
		}
		if (Timeline && Timeline->bLoop)
		{
			FOverlayBrushInfo IPOverlayInfo;
			IPOverlayInfo.Brush = FAppStyle::GetBrush(TEXT("Graph.Node.Loop"));

			if (IPOverlayInfo.Brush != NULL)
			{
				const float Padding = 2.5f;
				IPOverlayInfo.OverlayOffset.X = WidgetSize.X - IPOverlayInfo.Brush->ImageSize.X - Padding - Offset;
				IPOverlayInfo.OverlayOffset.Y = Padding;
			}
			Brushes.Add(IPOverlayInfo);
		}
	}

	// Display an  icon depending on the type of node and it's settings
	if (const UK2Node* K2Node = Cast<const UK2Node>(GraphNode))
	{
		if (Cast<UK2BeamNode_BeamFlow>(K2Node) || K2Node->GetClass()->HasMetaData(BeamK2::MD_BeamFlowNode))
		{
			auto ClientIcon = K2Node->GetCornerIcon();
			auto Brush = FBeamableCoreStyle::Get().GetBrush(ClientIcon);
			// If they gave us back a default brush "../../../Engine/Content/Slate/Checkerboard.png", go find it in our style
			if (Brush->GetResourceName().ToString().Contains("../../../Engine/Content/Slate/Checkerboard.png"))
				Brush = FAppStyle::GetBrush(ClientIcon);

			// If we failed to fallback onto the editor ones, we'll simply not render any ico 
			if (Brush->GetResourceName().ToString().Contains("../../../Engine/Content/Slate/Checkerboard.png"))
				ClientIcon = NAME_None;

			if (ClientIcon != NAME_None)
			{
				FOverlayBrushInfo IPOverlayInfo;
				IPOverlayInfo.Brush = Brush;

				if (IPOverlayInfo.Brush != NULL)
				{
					IPOverlayInfo.OverlayOffset.X = (WidgetSize.X - (IPOverlayInfo.Brush->ImageSize.X / 2.f)) - 3.f;
					IPOverlayInfo.OverlayOffset.Y = (IPOverlayInfo.Brush->ImageSize.Y / -2.f) + 2.f;
				}

				Brushes.Add(IPOverlayInfo);
			}
		}
	}
}
