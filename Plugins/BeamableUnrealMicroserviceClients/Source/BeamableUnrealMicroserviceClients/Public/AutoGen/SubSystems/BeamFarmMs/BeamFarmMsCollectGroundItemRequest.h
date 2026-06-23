
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectGroundItemRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectGroundItemResult.h"

#include "BeamFarmMsCollectGroundItemRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsCollectGroundItemRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCollectGroundItemRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsCollectGroundItemRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsCollectGroundItem",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsCollectGroundItemRequest* Make(FString _GroundItemId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsCollectGroundItemSuccess, FBeamRequestContext, Context, UBeamFarmMsCollectGroundItemRequest*, Request, UCollectGroundItemResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsCollectGroundItemError, FBeamRequestContext, Context, UBeamFarmMsCollectGroundItemRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsCollectGroundItemComplete, FBeamRequestContext, Context, UBeamFarmMsCollectGroundItemRequest*, Request);

using FBeamFarmMsCollectGroundItemFullResponse = FBeamFullResponse<UBeamFarmMsCollectGroundItemRequest*, UCollectGroundItemResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsCollectGroundItemFullResponse, FBeamFarmMsCollectGroundItemFullResponse);
