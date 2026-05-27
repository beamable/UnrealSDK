
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/StartResearchRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/StartResearchResult.h"

#include "BeamFarmMsStartResearchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsStartResearchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStartResearchRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsStartResearchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsStartResearch",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsStartResearchRequest* Make(int64 _ItemInstanceId, FString _ItemContentId, FString _ProjectContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsStartResearchSuccess, FBeamRequestContext, Context, UBeamFarmMsStartResearchRequest*, Request, UStartResearchResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsStartResearchError, FBeamRequestContext, Context, UBeamFarmMsStartResearchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsStartResearchComplete, FBeamRequestContext, Context, UBeamFarmMsStartResearchRequest*, Request);

using FBeamFarmMsStartResearchFullResponse = FBeamFullResponse<UBeamFarmMsStartResearchRequest*, UStartResearchResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsStartResearchFullResponse, FBeamFarmMsStartResearchFullResponse);
