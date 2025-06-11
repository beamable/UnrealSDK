#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamContentType.h"
#include "Serialization/BeamJsonUtils.h"
#include "Serialization/BeamJsonUtils.h"
#include "Serialization/BeamJsonUtils.h"


#include "ClientContentInfoTableRow.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FClientContentInfoTableRow : public FTableRowBase
{
	GENERATED_BODY()

	const static FString KeyField;
	const static TArray<FString> HeaderFields;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EBeamContentType Type = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="ContentId", Category="Beam")
	FString ContentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Version", Category="Beam")
	FString Version = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Uri", Category="Beam")
	FString Uri = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tags", Category="Beam")
	TArray<FString> Tags = {};		
};