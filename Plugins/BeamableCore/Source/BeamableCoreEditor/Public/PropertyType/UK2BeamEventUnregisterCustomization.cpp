#include "UK2BeamEventUnregisterCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "BeamFlow/K2BeamNode_EventUnregister.h"

TSharedRef<IDetailCustomization> UK2BeamEventUnregisterCustomization::MakeInstance()
{
	return MakeShareable(new UK2BeamEventUnregisterCustomization);
}

void UK2BeamEventUnregisterCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);

	// Prevent to multiple objects edition 
	if (Objects.Num() == 1)
	{
		if (UK2BeamNode_EventUnregister* Node = Cast<UK2BeamNode_EventUnregister>(Objects[0].Get()))
		{
			GenerateHiddenDelegateCheckboxes(DetailBuilder, Node);
		}
	}
}

void UK2BeamEventUnregisterCustomization::GenerateHiddenDelegateCheckboxes(IDetailLayoutBuilder& DetailBuilder, UK2BeamNode_EventUnregister* Node)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Available Events");

	const auto ReferenceClass = Node->GetRuntimeSubsystemClass();

	for (TFieldIterator<FMulticastDelegateProperty> It(ReferenceClass); It; ++It)
	{
		FName DelegateName = It->GetFName();

		if (!It->HasAnyPropertyFlags(CPF_BlueprintAssignable))
		{
			continue;
		}
		// Ensure entry exists
		if (!Node->EventPins.Contains(DelegateName))
		{
			Node->EventPins.Add(DelegateName, false);
		}

		Category.AddCustomRow(FText::FromName(DelegateName))
		        .NameContent()
			[
				SNew(STextBlock)
				.Text(FText::FromName(DelegateName))
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
			.ValueContent()
			[
				SNew(SCheckBox)
				.IsChecked_Lambda([Node, DelegateName]()
				{
					return Node->EventPins[DelegateName] ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
				})
				.OnCheckStateChanged_Lambda([Node, DelegateName](ECheckBoxState NewState)
				{
					Node->Modify();
					Node->EventPins[DelegateName] = (NewState == ECheckBoxState::Checked);

					FPropertyChangedEvent PropertyChangedEvent(Node->GetClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UK2BeamNode_EventUnregister, EventPins)));
					Node->PostEditChangeProperty(PropertyChangedEvent);
				})
			];
	}
}
