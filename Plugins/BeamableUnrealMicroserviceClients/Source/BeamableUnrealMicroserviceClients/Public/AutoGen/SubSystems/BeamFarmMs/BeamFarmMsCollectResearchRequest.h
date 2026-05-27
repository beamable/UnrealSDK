
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectResearchRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectResearchResult.h"

#include "BeamFarmMsCollectResearchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsCollectResearchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCollectResearchRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsCollectResearchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsCollectResearch",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsCollectResearchRequest* Make(int64 _ItemInstanceId, FString _ItemContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsCollectResearchSuccess, FBeamRequestContext, Context, UBeamFarmMsCollectResearchRequest*, Request, UCollectResearchResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsCollectResearchError, FBeamRequestContext, Context, UBeamFarmMsCollectResearchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsCollectResearchComplete, FBeamRequestContext, Context, UBeamFarmMsCollectResearchRequest*, Request);

using FBeamFarmMsCollectResearchFullResponse = FBeamFullResponse<UBeamFarmMsCollectResearchRequest*, UCollectResearchResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsCollectResearchFullResponse, FBeamFarmMsCollectResearchFullResponse);
