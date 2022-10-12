
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/TournamentEntry.h"
#include "AutoGen/Optionals/OptionalTournamentEntry.h"

#include "GetStandingsResponse.generated.h"

UCLASS(BlueprintType)
class UGetStandingsResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Entries")
	TArray<UTournamentEntry*> Entries;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Me")
	FOptionalTournamentEntry Me;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};