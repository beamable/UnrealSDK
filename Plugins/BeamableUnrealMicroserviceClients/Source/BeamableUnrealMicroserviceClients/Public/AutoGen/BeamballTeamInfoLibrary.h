#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballTeamInfo.h"

#include "BeamballTeamInfoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamballTeamInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Json", DisplayName="BeamballTeamInfo To JSON String")
	static FString BeamballTeamInfoToJsonString(const UBeamballTeamInfo* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make BeamballTeamInfo", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamballTeamInfo* Make(FString TeamName, TArray<UBeamballPlayerInfo*> Players, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Break BeamballTeamInfo", meta=(NativeBreakFunc))
	static void Break(const UBeamballTeamInfo* Serializable, FString& TeamName, TArray<UBeamballPlayerInfo*>& Players);
};