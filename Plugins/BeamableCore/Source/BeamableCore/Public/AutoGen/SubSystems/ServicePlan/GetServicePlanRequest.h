
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ServicePlanActorServicePlan.h"

#include "GetServicePlanRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetServicePlanRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetServicePlanRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Make GetServicePlan",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetServicePlanRequest* Make(FString _Name, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetServicePlanSuccess, FBeamRequestContext, Context, UGetServicePlanRequest*, Request, UServicePlanActorServicePlan*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetServicePlanError, FBeamRequestContext, Context, UGetServicePlanRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetServicePlanComplete, FBeamRequestContext, Context, UGetServicePlanRequest*, Request);

using FGetServicePlanFullResponse = FBeamFullResponse<UGetServicePlanRequest*, UServicePlanActorServicePlan*>;
DECLARE_DELEGATE_OneParam(FOnGetServicePlanFullResponse, FGetServicePlanFullResponse);
