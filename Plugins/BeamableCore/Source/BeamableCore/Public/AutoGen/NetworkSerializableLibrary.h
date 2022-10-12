
#pragma once

#include "CoreMinimal.h"
#include "NetworkSerializable.h"

#include "NetworkSerializableLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UNetworkSerializableLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize NetworkSerializable To JSON String")
	static FString NetworkSerializableToJsonString(const UNetworkSerializable* Serializable, const bool Pretty);		
};