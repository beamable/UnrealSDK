#pragma once

#include "CoreMinimal.h"
#include "BeamMicroserviceClientSubsystem.generated.h"

UCLASS(Abstract, BlueprintType)
class BEAMABLECORE_API UBeamMicroserviceClientSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	/**
	 * @brief Expose all private properties of this class to the MS Editor subsystem (so that the editor can do things to these subsystems as needed).
	 */
	friend class UBeamMicroservicesEditor;

protected:
	/**
	 * @brief Used to uniquely identify a Microservice instance (separately from any deployed version). This is primarily used to make sure the Beamable
	 * Backend knows how to route traffic to your locally deployed Microservice. It is blank all times except while you have this MS deployed locally.
	 */
	UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="This is always blank now and will be removed in newer versions since it is no longer used (replaced by RoutingKeyMap)."))
	FString Prefix;

	/**
	 * @brief Used to uniquely identify a Microservice. This is the name given to the C#MS via it's annotation. This is filled out  
	 */
	UPROPERTY(BlueprintReadOnly)
	FString MicroserviceName;
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	FString GetMicroserviceName() const { return MicroserviceName;}
};

inline void UBeamMicroserviceClientSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Prefix = TEXT("");
	MicroserviceName = TEXT("");
}

inline void UBeamMicroserviceClientSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
