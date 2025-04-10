
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/AccountAvailableResponse.h"

#include "GetAvailableExternalIdentityRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAvailableExternalIdentityRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Service", Category="Beam")
	FString ProviderService = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Id", Category="Beam")
	FString UserId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Namespace", Category="Beam")
	FOptionalString ProviderNamespace = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetAvailableExternalIdentityRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make GetAvailableExternalIdentity",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ProviderNamespace,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetAvailableExternalIdentityRequest* Make(FString _ProviderService, FString _UserId, FOptionalString _ProviderNamespace, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableExternalIdentitySuccess, FBeamRequestContext, Context, UGetAvailableExternalIdentityRequest*, Request, UAccountAvailableResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableExternalIdentityError, FBeamRequestContext, Context, UGetAvailableExternalIdentityRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAvailableExternalIdentityComplete, FBeamRequestContext, Context, UGetAvailableExternalIdentityRequest*, Request);

using FGetAvailableExternalIdentityFullResponse = FBeamFullResponse<UGetAvailableExternalIdentityRequest*, UAccountAvailableResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAvailableExternalIdentityFullResponse, FGetAvailableExternalIdentityFullResponse);
