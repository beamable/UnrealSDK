
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GetManifestsResponse.h"

#include "BasicContentGetManifestsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicContentGetManifestsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBasicContentGetManifestsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make BasicContentGetManifests",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicContentGetManifestsRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicContentGetManifestsSuccess, FBeamRequestContext, Context, UBasicContentGetManifestsRequest*, Request, UGetManifestsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicContentGetManifestsError, FBeamRequestContext, Context, UBasicContentGetManifestsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicContentGetManifestsComplete, FBeamRequestContext, Context, UBasicContentGetManifestsRequest*, Request);

using FBasicContentGetManifestsFullResponse = FBeamFullResponse<UBasicContentGetManifestsRequest*, UGetManifestsResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicContentGetManifestsFullResponse, FBasicContentGetManifestsFullResponse);
