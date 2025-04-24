#include "UK2BeamEventRegisterCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"

TSharedRef<IDetailCustomization> UK2BeamEventRegisterCustomization::MakeInstance()
{
	return MakeShareable(new UK2BeamEventRegisterCustomization);
}

void UK2BeamEventRegisterCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);

	// Prevent to multiple objects edition 
	if (Objects.Num() == 1)
	{
		if (UK2BeamNode_EventRegister* Node = Cast<UK2BeamNode_EventRegister>(Objects[0].Get()))
		{
			GenerateDelegateCheckboxes(DetailBuilder, Node);
		}
	}
}

void UK2BeamEventRegisterCustomization::GenerateDelegateCheckboxes(IDetailLayoutBuilder& DetailBuilder, UK2BeamNode_EventRegister* Node)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Available Events");

	const auto ReferenceClass = Node->GetRuntimeSubsystemClass();

	for (TFieldIterator<FMulticastDelegateProperty> It(ReferenceClass); It; ++It)
	{
		FName DelegateName = It->GetFName();

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
					Node->ReconstructNode(); // Optional: auto-refresh
				})
			];
	}
}
