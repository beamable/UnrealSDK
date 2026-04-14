#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballPlayerInfo.h"

#include "BeamballPlayerInfoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamballPlayerInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Json", DisplayName="BeamballPlayerInfo To JSON String")
	static FString BeamballPlayerInfoToJsonString(const UBeamballPlayerInfo* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make BeamballPlayerInfo", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamballPlayerInfo* Make(FString GamerTag, int32 Life, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Break BeamballPlayerInfo", meta=(NativeBreakFunc))
	static void Break(const UBeamballPlayerInfo* Serializable, FString& GamerTag, int32& Life);
};