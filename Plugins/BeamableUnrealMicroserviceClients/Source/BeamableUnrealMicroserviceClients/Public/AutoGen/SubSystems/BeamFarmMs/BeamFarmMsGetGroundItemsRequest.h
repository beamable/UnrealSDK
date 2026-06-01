
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetGroundItemsRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetGroundItemsResult.h"

#include "BeamFarmMsGetGroundItemsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsGetGroundItemsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGetGroundItemsRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsGetGroundItemsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsGetGroundItems",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsGetGroundItemsRequest* Make(FString _SpawnerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsGetGroundItemsSuccess, FBeamRequestContext, Context, UBeamFarmMsGetGroundItemsRequest*, Request, UGetGroundItemsResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsGetGroundItemsError, FBeamRequestContext, Context, UBeamFarmMsGetGroundItemsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsGetGroundItemsComplete, FBeamRequestContext, Context, UBeamFarmMsGetGroundItemsRequest*, Request);

using FBeamFarmMsGetGroundItemsFullResponse = FBeamFullResponse<UBeamFarmMsGetGroundItemsRequest*, UGetGroundItemsResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsGetGroundItemsFullResponse, FBeamFarmMsGetGroundItemsFullResponse);
