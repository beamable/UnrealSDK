
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/TournamentGroupEntry.h"
#include "AutoGen/Optionals/OptionalTournamentGroupEntry.h"

#include "GetGroupsResponse.generated.h"

UCLASS(BlueprintType)
class UGetGroupsResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Entries")
	TArray<UTournamentGroupEntry*> Entries;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Focus")
	FOptionalTournamentGroupEntry Focus;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};