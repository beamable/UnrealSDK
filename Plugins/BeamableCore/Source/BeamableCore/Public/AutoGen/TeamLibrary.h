#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/Team.h"

#include "TeamLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTeamLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Team To JSON String")
	static FString TeamToJsonString(const UTeam* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Team", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, Players, Outer", NativeMakeFunc))
	static UTeam* Make(FOptionalString Name, FOptionalArrayOfBeamGamerTag Players, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Team", meta=(NativeBreakFunc))
	static void Break(const UTeam* Serializable, FOptionalString& Name, FOptionalArrayOfBeamGamerTag& Players);
};