#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Team.h"

#include "TeamLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTeamLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Matchmaking|Utils|Json", DisplayName="Team To JSON String")
	static FString TeamToJsonString(const UTeam* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Matchmaking|Utils|Make/Break", DisplayName="Make Team", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, Players, Outer", NativeMakeFunc))
	static UTeam* Make(FOptionalString Name, FOptionalArrayOfBeamGamerTag Players, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Matchmaking|Utils|Make/Break", DisplayName="Break Team", meta=(NativeBreakFunc))
	static void Break(const UTeam* Serializable, FOptionalString& Name, FOptionalArrayOfBeamGamerTag& Players);
};