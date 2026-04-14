
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/InFlightFailureResponse.h"

#include "GetInflightFailuresRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetInflightFailuresRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FOptionalString ServiceName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Object Id", Category="Beam")
	FOptionalString ServiceObjectId = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetInflightFailuresRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Admin|Utils|Make/Break", DisplayName="Make GetInflightFailures",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ServiceName,_ServiceObjectId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetInflightFailuresRequest* Make(FOptionalString _ServiceName, FOptionalString _ServiceObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetInflightFailuresSuccess, FBeamRequestContext, Context, UGetInflightFailuresRequest*, Request, UInFlightFailureResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetInflightFailuresError, FBeamRequestContext, Context, UGetInflightFailuresRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetInflightFailuresComplete, FBeamRequestContext, Context, UGetInflightFailuresRequest*, Request);

using FGetInflightFailuresFullResponse = FBeamFullResponse<UGetInflightFailuresRequest*, UInFlightFailureResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetInflightFailuresFullResponse, FGetInflightFailuresFullResponse);
