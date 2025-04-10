#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/NetworkSerializable.h"

#include "NetworkSerializableLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UNetworkSerializableLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Json", DisplayName="NetworkSerializable To JSON String")
	static FString NetworkSerializableToJsonString(const UNetworkSerializable* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make NetworkSerializable", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UNetworkSerializable* Make(UObject* Outer);

	
};