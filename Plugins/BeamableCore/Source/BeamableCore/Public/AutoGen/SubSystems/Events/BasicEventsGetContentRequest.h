
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/EventContentResponse.h"

#include "BasicEventsGetContentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicEventsGetContentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBasicEventsGetContentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", DisplayName="Make BasicEventsGetContent",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicEventsGetContentRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicEventsGetContentSuccess, FBeamRequestContext, Context, UBasicEventsGetContentRequest*, Request, UEventContentResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicEventsGetContentError, FBeamRequestContext, Context, UBasicEventsGetContentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicEventsGetContentComplete, FBeamRequestContext, Context, UBasicEventsGetContentRequest*, Request);

using FBasicEventsGetContentFullResponse = FBeamFullResponse<UBasicEventsGetContentRequest*, UEventContentResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicEventsGetContentFullResponse, FBasicEventsGetContentFullResponse);
