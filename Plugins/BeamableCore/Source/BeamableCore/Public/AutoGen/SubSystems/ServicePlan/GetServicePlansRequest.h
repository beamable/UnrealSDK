
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ServicePlansResponse.h"

#include "GetServicePlansRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetServicePlansRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetServicePlansRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Make GetServicePlans",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetServicePlansRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetServicePlansSuccess, FBeamRequestContext, Context, UGetServicePlansRequest*, Request, UServicePlansResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetServicePlansError, FBeamRequestContext, Context, UGetServicePlansRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetServicePlansComplete, FBeamRequestContext, Context, UGetServicePlansRequest*, Request);

using FGetServicePlansFullResponse = FBeamFullResponse<UGetServicePlansRequest*, UServicePlansResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetServicePlansFullResponse, FGetServicePlansFullResponse);
