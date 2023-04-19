
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnreal/AutoGen/StandaloneMicroserviceJoinNumbersAsStringRequestArgs.h"
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsJoinNumbersAsStringResponse.h"

#include "StandaloneMicroserviceMsJoinNumbersAsStringRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREAL_API UStandaloneMicroserviceMsJoinNumbersAsStringRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStandaloneMicroserviceJoinNumbersAsStringRequestArgs* Body;

	// Beam Base Request Declaration
	UStandaloneMicroserviceMsJoinNumbersAsStringRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|StandaloneMicroserviceMs", DisplayName="Beam - Make StandaloneMicroserviceMsJoinNumbersAsString",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UStandaloneMicroserviceMsJoinNumbersAsStringRequest* Make(int32 _A, int32 _B, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnStandaloneMicroserviceMsJoinNumbersAsStringSuccess, FBeamRequestContext, Context, UStandaloneMicroserviceMsJoinNumbersAsStringRequest*, Request, UStandaloneMicroserviceMsJoinNumbersAsStringResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnStandaloneMicroserviceMsJoinNumbersAsStringError, FBeamRequestContext, Context, UStandaloneMicroserviceMsJoinNumbersAsStringRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnStandaloneMicroserviceMsJoinNumbersAsStringComplete, FBeamRequestContext, Context, UStandaloneMicroserviceMsJoinNumbersAsStringRequest*, Request);

using FStandaloneMicroserviceMsJoinNumbersAsStringFullResponse = FBeamFullResponse<UStandaloneMicroserviceMsJoinNumbersAsStringRequest*, UStandaloneMicroserviceMsJoinNumbersAsStringResponse*>;
DECLARE_DELEGATE_OneParam(FOnStandaloneMicroserviceMsJoinNumbersAsStringFullResponse, FStandaloneMicroserviceMsJoinNumbersAsStringFullResponse);
