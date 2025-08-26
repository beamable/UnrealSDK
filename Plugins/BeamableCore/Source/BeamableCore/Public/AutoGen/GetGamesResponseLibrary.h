#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetGamesResponse.h"

#include "GetGamesResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetGamesResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="GetGamesResponse To JSON String")
	static FString GetGamesResponseToJsonString(const UGetGamesResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make GetGamesResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Realms, Outer", NativeMakeFunc))
	static UGetGamesResponse* Make(FOptionalArrayOfRealmView Realms, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break GetGamesResponse", meta=(NativeBreakFunc))
	static void Break(const UGetGamesResponse* Serializable, FOptionalArrayOfRealmView& Realms);
};