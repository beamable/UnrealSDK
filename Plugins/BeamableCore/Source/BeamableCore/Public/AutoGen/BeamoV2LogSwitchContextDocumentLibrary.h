#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2LogSwitchContextDocument.h"

#include "BeamoV2LogSwitchContextDocumentLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2LogSwitchContextDocumentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2LogSwitchContextDocument To JSON String")
	static FString BeamoV2LogSwitchContextDocumentToJsonString(const UBeamoV2LogSwitchContextDocument* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2LogSwitchContextDocument", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Rules, Outer", NativeMakeFunc))
	static UBeamoV2LogSwitchContextDocument* Make(FString ServiceName, FString RoutingKey, EBeamBeamoV2LogLevel DefaultLogLevel, FOptionalBeamoV2ObjectId Id, FOptionalArrayOfBeamoV2LogContextRule Rules, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2LogSwitchContextDocument", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2LogSwitchContextDocument* Serializable, FString& ServiceName, FString& RoutingKey, EBeamBeamoV2LogLevel& DefaultLogLevel, FOptionalBeamoV2ObjectId& Id, FOptionalArrayOfBeamoV2LogContextRule& Rules);
};