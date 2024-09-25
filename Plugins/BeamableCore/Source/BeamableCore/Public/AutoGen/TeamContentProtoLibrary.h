#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/TeamContentProto.h"

#include "TeamContentProtoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTeamContentProtoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - TeamContentProto To JSON String")
	static FString TeamContentProtoToJsonString(const UTeamContentProto* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make TeamContentProto", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, MaxPlayers, MinPlayers, Outer", NativeMakeFunc))
	static UTeamContentProto* Make(FOptionalString Name, FOptionalInt32 MaxPlayers, FOptionalInt32 MinPlayers, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break TeamContentProto", meta=(NativeBreakFunc))
	static void Break(const UTeamContentProto* Serializable, FOptionalString& Name, FOptionalInt32& MaxPlayers, FOptionalInt32& MinPlayers);
};