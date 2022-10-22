#pragma once

#include "CoreMinimal.h"
#include "KismetNodes/SGraphNodeK2Base.h"
#include "KismetNodes/SGraphNodeK2Default.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class BEAMABLECOREEDITOR_API SGraphNodeBaseBeam : public SGraphNodeK2Default
{
public:
	SLATE_BEGIN_ARGS(SGraphNodeBaseBeam)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, class UEdGraphNode* InNode);

protected:
	// SGraphNode interface	
	virtual void GetOverlayBrushes(bool bSelected, const FVector2D WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const override;	
	// End of SGraphNode interface
};
