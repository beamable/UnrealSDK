#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterGroundItemRequestArgs.h"

#include "RegisterGroundItemRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API URegisterGroundItemRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="RegisterGroundItemRequestArgs To JSON String")
	static FString RegisterGroundItemRequestArgsToJsonString(const URegisterGroundItemRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make RegisterGroundItemRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URegisterGroundItemRequestArgs* Make(FString GroundItemId, FString ContentId, int32 Quantity, FString ItemType, float PosX, float PosY, float PosZ, FString SpawnerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break RegisterGroundItemRequestArgs", meta=(NativeBreakFunc))
	static void Break(const URegisterGroundItemRequestArgs* Serializable, FString& GroundItemId, FString& ContentId, int32& Quantity, FString& ItemType, float& PosX, float& PosY, float& PosZ, FString& SpawnerId);
};