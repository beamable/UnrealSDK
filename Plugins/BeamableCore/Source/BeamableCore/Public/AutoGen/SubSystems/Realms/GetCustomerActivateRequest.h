
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "Serialization/BeamJsonUtils.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#include "GetCustomerActivateRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCustomerActivateRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token", Category="Beam")
	FString Token = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid", Category="Beam")
	int64 Cid = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetCustomerActivateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make GetCustomerActivate",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetCustomerActivateRequest* Make(FString _Token, int64 _Cid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCustomerActivateSuccess, FBeamRequestContext, Context, UGetCustomerActivateRequest*, Request, UBeamPlainTextResponseBody*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCustomerActivateError, FBeamRequestContext, Context, UGetCustomerActivateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCustomerActivateComplete, FBeamRequestContext, Context, UGetCustomerActivateRequest*, Request);

using FGetCustomerActivateFullResponse = FBeamFullResponse<UGetCustomerActivateRequest*, UBeamPlainTextResponseBody*>;
DECLARE_DELEGATE_OneParam(FOnGetCustomerActivateFullResponse, FGetCustomerActivateFullResponse);
