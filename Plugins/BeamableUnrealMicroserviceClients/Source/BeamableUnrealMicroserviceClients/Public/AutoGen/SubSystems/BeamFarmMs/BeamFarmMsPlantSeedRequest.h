
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PlantSeedRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PlantResult.h"

#include "BeamFarmMsPlantSeedRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsPlantSeedRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPlantSeedRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsPlantSeedRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsPlantSeed",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsPlantSeedRequest* Make(FString _SeedContentId, FString _SlotId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsPlantSeedSuccess, FBeamRequestContext, Context, UBeamFarmMsPlantSeedRequest*, Request, UPlantResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsPlantSeedError, FBeamRequestContext, Context, UBeamFarmMsPlantSeedRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsPlantSeedComplete, FBeamRequestContext, Context, UBeamFarmMsPlantSeedRequest*, Request);

using FBeamFarmMsPlantSeedFullResponse = FBeamFullResponse<UBeamFarmMsPlantSeedRequest*, UPlantResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsPlantSeedFullResponse, FBeamFarmMsPlantSeedFullResponse);
