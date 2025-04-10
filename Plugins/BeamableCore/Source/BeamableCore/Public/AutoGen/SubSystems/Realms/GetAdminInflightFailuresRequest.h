
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/InFlightFailureResponse.h"

#include "GetAdminInflightFailuresRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAdminInflightFailuresRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Object Id", Category="Beam")
	FOptionalString ServiceObjectId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FString ServiceName = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetAdminInflightFailuresRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make GetAdminInflightFailures",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ServiceObjectId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetAdminInflightFailuresRequest* Make(FOptionalString _ServiceObjectId, FString _ServiceName, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAdminInflightFailuresSuccess, FBeamRequestContext, Context, UGetAdminInflightFailuresRequest*, Request, UInFlightFailureResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAdminInflightFailuresError, FBeamRequestContext, Context, UGetAdminInflightFailuresRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAdminInflightFailuresComplete, FBeamRequestContext, Context, UGetAdminInflightFailuresRequest*, Request);

using FGetAdminInflightFailuresFullResponse = FBeamFullResponse<UGetAdminInflightFailuresRequest*, UInFlightFailureResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAdminInflightFailuresFullResponse, FGetAdminInflightFailuresFullResponse);
