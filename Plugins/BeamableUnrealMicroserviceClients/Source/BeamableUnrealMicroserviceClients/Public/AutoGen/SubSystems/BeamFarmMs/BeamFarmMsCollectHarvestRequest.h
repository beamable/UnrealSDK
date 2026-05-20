
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectHarvestRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectResult.h"

#include "BeamFarmMsCollectHarvestRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsCollectHarvestRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCollectHarvestRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsCollectHarvestRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsCollectHarvest",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsCollectHarvestRequest* Make(FString _SlotId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsCollectHarvestSuccess, FBeamRequestContext, Context, UBeamFarmMsCollectHarvestRequest*, Request, UCollectResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsCollectHarvestError, FBeamRequestContext, Context, UBeamFarmMsCollectHarvestRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsCollectHarvestComplete, FBeamRequestContext, Context, UBeamFarmMsCollectHarvestRequest*, Request);

using FBeamFarmMsCollectHarvestFullResponse = FBeamFullResponse<UBeamFarmMsCollectHarvestRequest*, UCollectResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsCollectHarvestFullResponse, FBeamFarmMsCollectHarvestFullResponse);
