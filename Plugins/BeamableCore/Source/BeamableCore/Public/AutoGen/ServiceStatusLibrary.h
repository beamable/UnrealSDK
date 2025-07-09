#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceStatus.h"

#include "ServiceStatusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ServiceStatus To JSON String")
	static FString ServiceStatusToJsonString(const UServiceStatus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ServiceStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsCurrent, bRunning, ServiceName, ImageId, ServiceDependencyReferences, Outer", NativeMakeFunc))
	static UServiceStatus* Make(FOptionalBool bIsCurrent, FOptionalBool bRunning, FOptionalString ServiceName, FOptionalString ImageId, FOptionalArrayOfServiceDependencyReference ServiceDependencyReferences, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ServiceStatus", meta=(NativeBreakFunc))
	static void Break(const UServiceStatus* Serializable, FOptionalBool& bIsCurrent, FOptionalBool& bRunning, FOptionalString& ServiceName, FOptionalString& ImageId, FOptionalArrayOfServiceDependencyReference& ServiceDependencyReferences);
};