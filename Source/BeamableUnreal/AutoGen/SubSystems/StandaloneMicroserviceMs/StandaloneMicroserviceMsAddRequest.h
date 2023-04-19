
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnreal/AutoGen/StandaloneMicroserviceAddRequestArgs.h"
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsAddResponse.h"

#include "StandaloneMicroserviceMsAddRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREAL_API UStandaloneMicroserviceMsAddRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStandaloneMicroserviceAddRequestArgs* Body;

	// Beam Base Request Declaration
	UStandaloneMicroserviceMsAddRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|StandaloneMicroserviceMs", DisplayName="Beam - Make StandaloneMicroserviceMsAdd",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UStandaloneMicroserviceMsAddRequest* Make(int32 _A, int32 _B, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnStandaloneMicroserviceMsAddSuccess, FBeamRequestContext, Context, UStandaloneMicroserviceMsAddRequest*, Request, UStandaloneMicroserviceMsAddResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnStandaloneMicroserviceMsAddError, FBeamRequestContext, Context, UStandaloneMicroserviceMsAddRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnStandaloneMicroserviceMsAddComplete, FBeamRequestContext, Context, UStandaloneMicroserviceMsAddRequest*, Request);

using FStandaloneMicroserviceMsAddFullResponse = FBeamFullResponse<UStandaloneMicroserviceMsAddRequest*, UStandaloneMicroserviceMsAddResponse*>;
DECLARE_DELEGATE_OneParam(FOnStandaloneMicroserviceMsAddFullResponse, FStandaloneMicroserviceMsAddFullResponse);
